# struct sk_buff (include/linux/skbuff.h>
## Overview
- 패킷의 정보를 저장
- 모든 네트워크 계층에서의 헤더, 페이로드, 작업 배분을 위한 정보 등을 저장
- 데이터 송/수신 헤더정보 포함
- 네트워크 계층을 거치며(L2 - L3 - L4) 변수값 변경
  
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
			int			ip_defrag_offset;
		};
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
