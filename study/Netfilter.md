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
