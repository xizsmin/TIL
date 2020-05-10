# struct sk_buff (include/linux/skbuff.h>
## Overview
- 패킷의 정보를 저장
- 모든 네트워크 계층에서의 헤더, 페이로드, 작업 배분을 위한 정보 등을 저장
- 데이터 송/수신 헤더정보 포함
- 네트워크 계층을 거치며(L2 - L3 - L4) 변수값 변경
- 헤더 붙이고 뗄 때에는 포인터만 옮기는 식으로 구현
  
## Networking Options
- 방화벽, 멀티캐스팅 사용여부 등 상황에 따라 옵션(필드) 유무 결정 -> #ifdef


e.g.,
```c
struct sk_buff {
...
#ifdef CONFIG_NET_SCHED
	__u16			tc_index;	/* traffic control index */
#endif
```
- 커널 컴파일시 make config 단계에서 CONFIG_NET_SCHED / CONFIG_NET_CLS_ACT 옵션 체크해야 코드 타게 됨
- 보통 커널모듈에서 허용하지는 않음
- cf. Kconfig (TBD)
  
## Layout Field
- doublely-linked list
```c
// kernel v5.7-rc4

struct sk_buff {
	union {
		struct {
			/* These two members must be first. */
			struct sk_buff		*next;		// next buffer in list
			struct sk_buff		*prev;		// previous buffer in list

			union {
				struct net_device	*dev;	// device we arrived on/are leaving by
				/* Some protocols might use this space to store information,
				 * while device pointer would be NULL.
				 * UDP receive path is one user.
				 */
				unsigned long		dev_scratch;
			};
		};
		struct rb_node		rbnode; /* used in netem, ip4 defrag, and tcp stack */
		struct list_head	list;		// queue head
		
		union {
			struct sock		*sk;		// sockets we're owned by
			int				ip_defrag_offset;
		};
		union {
			ktime_t		tstamp;			// time we arrived/left
		...
		
		/*
		 * This is the control buffer. It is free to use for every
		 * layer. Please put your private variables there. If you
	 	 * want to keep them across layers you have to do a skb_clone()
	 	 * first. This is owned by whoever has the skb queued ATM.
	 	 */
		char			cb[48] __aligned(8);		// storing ctrl info for each network layer
		
		union {
			struct {
				unsigned long	_skb_refdst;						// used in routing subsystem(CH7)
				void		(*destructor)(struct sk_buff *skb);		// destructor
			};
		...
		
		__be16			protocol;
		__u16			transport_header;			// L4 header
		__u16			network_header;				// L3 header
		__u16			mac_header;					// L2 header

		/* private: */
		__u32			headers_end[0];
		
		unsigned int	len,			// length of actual data(main buff + frag.buf)
						data_len;		// data length(for each fragment)
		__u16			mac_len,		// length of MAC header
		...
		
		__u8			cloned:1,		// Head may be cloned (check refcnt to be sure)
		
		
		// Defined in /linux/if_packet.h
		// to set pkt_type value
		//#define PACKET_HOST		0		/* To us		*/
		//#define PACKET_BROADCAST	1		/* To all		*/
		//#define PACKET_MULTICAST	2		/* To group		*/
		//#define PACKET_OTHERHOST	3		/* To someone else 	*/
		//#define PACKET_OUTGOING		4		/* Outgoing of any type */
		//#define PACKET_LOOPBACK		5		/* MC/BRD frame looped back */
		//#define PACKET_USER		6		/* To user space	*/
		//#define PACKET_KERNEL		7		/* To kernel space	*/
		/* Unused, PACKET_FASTROUTE and PACKET_LOOPBACK are invisible to user space */
		//#define PACKET_FASTROUTE	6		/* Fastrouted frame	*/
		__u8			pkt_type:3;		// 
		__u8			ignore_df:1;
		__u8			nf_trace:1;
		__u8			ip_summed:2;
		...
		
		union {
			__wsum		csum;			//checksum
			struct {
				__u16	csum_start;
				__u16	csum_offset;
			};
		};
		__u32			priority;		// QoS - packet queing  priority
										// can be determined by, for example, the TOS field setting in the IPV4 header.
		...
		// cf. /linux/if_ether.h
		__be16			protocol;		// (unsigned short) must be initialized before netif_rx called
		unsigned int	truesize;		// buffer size in total(including sk_buff itself)
		refcount_t		users;			// user count(ref, obj, etc.) - see {datagram, tcp}.c
	};
  ...
```
- list head
```c
struct sk_buff_head {
	/* These two members must be first. */
	struct sk_buff	*next;
	struct sk_buff	*prev;

	__u32		qlen;         // number of list members
	spinlock_t	lock;    	  // locking
};
```

## 관리 함수
```c
// Add data to a buffer
// A pointer to the first byte of the extra data is returned.
void *skb_put(struct sk_buff *skb, unsigned int len)
{
	void *tmp = skb_tail_pointer(skb);
	SKB_LINEAR_ASSERT(skb);
	skb->tail += len;
	skb->len  += len;
	if (unlikely(skb->tail > skb->end))
		skb_over_panic(skb, len, __builtin_return_address(0));
	return tmp;
}
EXPORT_SYMBOL(skb_put);

// Add data to the start of a buffer
// A pointer to the first byte of the extra data is returned.
void *skb_push(struct sk_buff *skb, unsigned int len)
{
	skb->data -= len;
	skb->len  += len;
	if (unlikely(skb->data < skb->head))
		skb_under_panic(skb, len, __builtin_return_address(0));
	return skb->data;
}
EXPORT_SYMBOL(skb_push);

// remove data from the start of a buffer
// A pointer to the next data in the buffer is returned
void *skb_pull(struct sk_buff *skb, unsigned int len)
{
	return skb_pull_inline(skb, len);
}
EXPORT_SYMBOL(skb_pull);

static inline void *__skb_pull(struct sk_buff *skb, unsigned int len)
{
	skb->len -= len;
	BUG_ON(skb->len < skb->data_len);
	return skb->data += len;
}

static inline void *skb_pull_inline(struct sk_buff *skb, unsigned int len)
{
	return unlikely(len > skb->len) ? NULL : __skb_pull(skb, len);
}

// remove end from a buffer
void skb_trim(struct sk_buff *skb, unsigned int len)
{
	if (skb->len > len)
		__skb_trim(skb, len);
}
EXPORT_SYMBOL(skb_trim);

static inline void __skb_set_length(struct sk_buff *skb, unsigned int len)
{
	if (WARN_ON(skb_is_nonlinear(skb)))
		return;
	skb->len = len;
	skb_set_tail_pointer(skb, len);
}

static inline void __skb_trim(struct sk_buff *skb, unsigned int len)
{
	__skb_set_length(skb, len);
}

// Increase the headrom of an empty &sk_buff by reducing the tailroom
// Only allowed for an empty buffer
static inline void skb_reserve(struct sk_buff *skb, int len)
{
	skb->data += len;
	skb->tail += len;
}

```

## 메모리 할당 관련 함수
- alloc_skb, dev_alloc_skb, kfree_skb, dev_kfree_skb


# struct net_device
