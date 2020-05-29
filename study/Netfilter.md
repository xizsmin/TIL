# Netfilter Hooks
- NF_INET_PRE_ROUTING
- NF_INET_LOCAL_IN
- NF_INET_FORWARD
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
