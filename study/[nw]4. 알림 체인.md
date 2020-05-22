# 알림 체인
- 커널의 서브시스템 중 하나에서 (비동기)이벤트가 탐지되거나 발생했을 경우 다른 서브시스템(들)에도 알리는 메커니즘
- 서브시스템을 개발할 때에는 자신의 서브시스템이 다른 시스템과 어떤 관계인지 알고, 어떤 이벤트를 수신하거나 전달할지 알고 있어야 함
- 단순 if-else보다 알림 체인을 활용하는 것이 효율적

## 체인 정의
```c
struct notifier_block;

typedef	int (*notifier_fn_t)(struct notifier_block *nb,
			unsigned long action, void *data);

struct notifier_block {
	notifier_fn_t notifier_call;        // (이벤트 발생시)수행할 함수
	struct notifier_block __rcu *next;  // list 연결용 포인터
	int priority;                       // 함수의 가중치(사실상 안씀)
};

```
## 체인에 등록
- 특정 알림 체인의 이벤트를 받고 싶은 컴포넌트는 notifier_chain_register()로 event subscribe
- 각 서브시스템에서 notifier_chain_register에 대한 wrapper를 제공(즉 직접 호출되지는 않고 wrapper 통해서만 서비스)

## 체인에 이벤트 알림(noti 생성)
- 각 noti chain에 등록된 함수를 우선순위대로 수행
- 실제 priority 값은 안 들어가기 때문에 결국 등록된 시간순서대로 수행
```c
/**
 * notifier_call_chain - Informs the registered notifiers about an event.
 *	@nl:		Pointer to head of the blocking notifier chain
 *	@val:		Value passed unmodified to notifier function
 *	@v:		Pointer passed unmodified to notifier function
 *	@nr_to_call:	Number of notifier functions to be called. Don't care
 *			value of this parameter is -1.
 *	@nr_calls:	Records the number of notifications sent. Don't care
 *			value of this field is NULL.
 *	@returns:	notifier_call_chain returns the value returned by the
 *			last notifier function called.
 */
static int notifier_call_chain(struct notifier_block **nl,
			       unsigned long val, void *v,
			       int nr_to_call, int *nr_calls)
{
	int ret = NOTIFY_DONE;
	struct notifier_block *nb, *next_nb;

	nb = rcu_dereference_raw(*nl);

	while (nb && nr_to_call) {
		next_nb = rcu_dereference_raw(nb->next);

#ifdef CONFIG_DEBUG_NOTIFIERS
		if (unlikely(!func_ptr_is_kernel_text(nb->notifier_call))) {
			WARN(1, "Invalid notifier called!");
			nb = next_nb;
			continue;
		}
#endif
		ret = nb->notifier_call(nb, val, v);

		if (nr_calls)
			(*nr_calls)++;

		if (ret & NOTIFY_STOP_MASK) // 더 이상 콜백 호출하지 말아야 할 경우
			break;
		nb = next_nb;
		nr_to_call--;
	}
	return ret;
}
NOKPROBE_SYMBOL(notifier_call_chain);

```


## 네트워크 서브시스템의 주요 알림 체인
- inetaddr_chain: local interface상에서 IPv4주소의 생성, 제거, 변경 등의 변화 발생시 알림(CH23)
- netdev_chain: 네트워크 장치 등록 상태 변화시 생성(CH8)

