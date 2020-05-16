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

## 데이터 예약 및 정렬
- skb_reserve, skb_put, skb_push, skb_pull

## 버퍼의 복제와 복사
- skb_clone

## 리스트 관리 함수
- skb_queue_head_init, skb_queue_head, skb_queue_tail
- skb_dequeue, skb_dequeue_tail, skb_queue_purge, skb_queue_walk


# struct net_device
- /include/linux/netdevice.h: struct net_device
- 네트워크 장치와 관련된 모든 정보를 저장(장치별로 1개씩 생성)
- NIC 등의 실제 장치 및 가상 장치(VLAN 등)에도 각각 생성
- 장치마다 공통적으로 갖는 값도 있고 다른 필드도 있음

## 식별자
```c
int ifindex;			// interface id
int iflink;				// deprecated
unsigned short dev_id;	// differentiating devices sharing the same link layer address(zSeries NIC?)
```

## 설정 관련 필드
```c
struct net_device {
	char			name[IFNAMSIZ];		// 장치이름(eth0 등)
	unsigned long		mem_end;	
	unsigned long		mem_start;		// 커널과의 통신을 위해 장치가 사용하는 공유 메모리(해당 디바이스 드라이버만 접근)
	unsigned long		base_addr;		// 장치의 메모리에 매핑된 I/O메모리 시작
	int			irq;					// 커널이 장치를 호출하기 위한 인터럽트 번호
	
	...
	netdev_features_t	features;		// 특정 장치의 기능을 저장하기 위한 플래그 비트
	...
	unsigned int		flags;			// 네트워크 장치의 기능, 상태변화 등 표시
	unsigned int		priv_flags;		// VLAN, 브리지 가상장치에서 사용
	unsigned short		gflags;			// 거의 사용X(호환성 목적)
	...
	
	unsigned char		if_port;		// 인터페이스가 사용하는 포트타입
	unsigned char		dma;			// 장치가 사용하는 DMA 채널
	unsigned int		mtu;			// 장치가 처리 가능한 최대 프레임 크기
	
	...
	unsigned char		addr_len;		// MAC addr 길이
	unsigned char		*dev_addr;		// MAX addr
	
	unsigned short		type;			// 장치 타입(이더넷, 프레임딜레이, etc. - cf. /include/linux/if_arp.h)
	unsigned short		hard_header_len;		// 장치 헤더 길이		cf. /include/linux/if_ether.h
	
	...
	unsigned char		broadcast[MAX_ADDR_LEN];	// 브로드캐스트 주소
	
	...
	unsigned int		promiscuity;				// 무차별 모드(여러 클라이언트가 요청 가능, 설정시 1 증가/나갈때 1감소
	
```
- 무차별 모드: 지정된 주소로 오는 패킷 이외의 모든 지나가는 프레임을 받도록 설정

## 장치 상태 필드
```c
	unsigned long		state;		// used by network queing subsystem
	
	...
	enum { NETREG_UNINITIALIZED=0,
	       NETREG_REGISTERED,	/* completed register_netdevice */
	       NETREG_UNREGISTERING,	/* called unregister_netdevice */
	       NETREG_UNREGISTERED,	/* completed unregister todo */
	       NETREG_RELEASED,		/* called free_netdev */
	       NETREG_DUMMY,		/* dummy device for NAPI poll */
	} reg_state:8;

	unsigned long		trans_start;		// *** struct netdev_queue! Time in jiffies of last Tx
	
```

## 리스트 관리
- struct hlist_node	index_hlist;
- /net/core/dev_addr_list.c - Functions for handling net device lists: functions for working with uni/multicast and device addr lists
	
## 트래픽 관리
```c
	struct Qdisc		*qdisc;			// manging tx/rx packet queue
	unsigned int		tx_queue_len;	// tx queue length
```

## 일반 필드
```c
	/* These may be needed for future network-power-down code. */
	struct timer_list	watchdog_timer;
	int			watchdog_timeo;
	
	struct list_head	todo_list;			// 네트워크 장치의 등록/해제
	int __percpu		*pcpu_refcnt;		// 참조카운트
	
```

## 함수 포인터
```c
	const struct ethtool_ops *ethtool_ops;		// 장치의 매개변수 설정/읽을 때
	
```
- struct net_device_ops 로 분리

