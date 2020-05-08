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
#ifdef CONFIG_NET_CLS_ACT
	__u16			tc_verd;	/* traffic control verdict */
#endif
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
		
		unsigned int		len,			// length of actual data(main buff + frag.buf)
							data_len;		// data length(for each fragment)
		__u16				mac_len,		// length of MAC header
		...
		unsigned int		truesize;		// buffer size in total(including sk_buff itself)
		refcount_t			users;			// user count(ref, obj, etc.) - see {datagram, tcp}.c
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
	spinlock_t	lock;     // locking
};
```

# struct net_device
