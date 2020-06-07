//TBD: get payload length correctly

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>


static struct nf_hook_ops *nfho = NULL;

unsigned int hook_func(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
	struct iphdr *iph;
	struct udphdr *udph;
	struct tcphdr *tcph;

	if (!skb) return NF_ACCEPT;
	iph = ip_hdr(skb);
	if (!iph) return NF_ACCEPT;

	if (iph->protocol==IPPROTO_TCP) {
		tcph = tcp_hdr(skb);
		if (!tcph) return NF_ACCEPT;
		printk("TCP sport: %u, dport: %u\n", ntohs(tcph->source), ntohs(tcph->dest));
		if (ntohs(tcph->dest) == 3333) {
//			printk("***************\n");

			char *data = (char *)((unsigned char *)tcph + 4*(tcph->doff));
		    char *buf = "10248912084510925125";
			printk(KERN_INFO "TCP source: %hu, TCP dest: %hu, data_len: %u\n", \
					ntohs(tcph->source), ntohs(tcph->dest), iph->tot_len - 4*(iph->ihl) - 4*(tcph->doff));
			//print_hex_dump(KERN_INFO, "", DUMP_PREFIX_OFFSET, 16, 1, (char *)data, 128, 1);
			print_hex_dump(KERN_INFO, "", DUMP_PREFIX_OFFSET, 16, 1, (char *)tcph, skb->len, 1);

		}
	}
	return NF_ACCEPT;
}


static int __init test_netfilter_init(void)
{
	nfho = (struct nf_hook_ops *)kzalloc(sizeof(struct nf_hook_ops), GFP_KERNEL);
	nfho->hook = (nf_hookfn *)hook_func;
	nfho->pf = PF_INET;
	nfho->hooknum = NF_INET_PRE_ROUTING;
	nfho->priority = NF_IP_PRI_FIRST;

	nf_register_net_hook(&init_net, nfho);
	return 0;
}

static void __exit test_netfilter_exit(void)
{
	nf_unregister_net_hook(&init_net, nfho);
	kfree(nfho);
	return;
}

MODULE_LICENSE("GPLv2");
module_init(test_netfilter_init);
module_exit(test_netfilter_exit);
