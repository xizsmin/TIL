# Netfilter Hooks
- NF_INET_PRE_ROUTING (For all incoming packets: ip_rcv(), ipv6_rcv())
- NF_INET_LOCAL_IN    (For incoming packets whose dst is localhost: `ip_local_deliver()`, `ip6_input()`)
- NF_INET_FORWARD     (For packets to be forwarded to somewhere else: )
- NF_INET_POST_ROUTING
- NF_INET_LOCAL_OUT

```c
[NIC] --> (0.PREROUTE) --> [ROUTING SUBSYSTEM] ---------(2.FORWARD)-------------(4.LOCAL_OUT)--->[NIC]
                                 |                                     ^
                                 |                                     |
                            (1.LOCAL_IN)                       [ROUTING SUBSYSTEM]
                                 |                                     |
                                 |                                (3.LOCAL_OUT)
                                 V                                     |  
                          [LOCAL PROCESS]                        [LOCAL_PROCESS]
                          
```
