# Netfilter Hooks
- NF_INET_PRE_ROUTING (For all incoming packets: `ip_rcv(), ipv6_rcv()`)
- NF_INET_LOCAL_IN    (For incoming packets whose dst is localhost: `ip_local_deliver()`, `ip6_input()`)
- NF_INET_FORWARD     (For packets to be forwarded to somewhere else: `ip_forward(), ip6_forward()`)
- NF_INET_POST_ROUTING(For packets who are ready to be trasmitted, reach as the final point: `ip_output(), ip6_finish_output2()`)
- NF_INET_LOCAL_OUT   (For packets generated in this local machine: `__ip_local_out(), __ip6_local_out()`)

```c
[NIC] --> (0.PREROUTE) --> [ROUTING SUBSYSTEM] ---------(2.FORWARD)-------------(4.POSTROUTE)--->[NIC]
                                 |                                     ^
                                 |                                     |
                            (1.LOCAL_IN)                       [ROUTING SUBSYSTEM]
                                 |                                     |
                                 |                                (3.LOCAL_OUT)
                                 V                                     |  
                          [LOCAL PROCESS]                        [LOCAL_PROCESS]
                          
```

### `NF_HOOK` macro
- Called in some points along the packet traversal
- (Actually in all the functions above, plus whenever needed)
  - pf: Protocol family(defined in /include/linux/netfilter.h e.g., NFPROTO_IPV4, NFPROTO_ARP, etc.)
  - hook: One of the five netfilter hooks above
  - skb: sk_buff (net, sk: TBD)
  - in, out: incoming/outgoing interfaces(net device)
 
```c

static inline int
NF_HOOK(uint8_t pf, unsigned int hook, struct net *net, struct sock *sk, struct sk_buff *skb,
  struct net_device *in, struct net_device *out,
	int (*okfn)(struct net *, struct sock *, struct sk_buff *))
{
	int ret = nf_hook(pf, hook, net, sk, skb, in, out, okfn);
	if (ret == 1)
		ret = okfn(net, sk, skb);
	return ret;
}

```
