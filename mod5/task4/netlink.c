#include <linux/module.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>
#include <net/net_namespace.h>
#include <net/sock.h>

#define NETLINK_USER 31

static struct sock *nl_sk = NULL;
static char *msg = "Employee me, Eltex!";

static void hello_nl_recv_msg(struct sk_buff *skb) {
	int msg_size = strlen(msg);

	struct nlmsghdr *nlh = (struct nlmsghdr *)skb->data;
	int pid = nlh->nlmsg_pid; /*pid of sending process */

	struct sk_buff *skb_out = nlmsg_new(msg_size, 0);

	if (!skb_out) {
		printk(KERN_ERR "Failed to allocate new skb\n");
		return;
	}
	nlh = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, msg_size, 0);
	NETLINK_CB(skb_out).dst_group = 0; /* not in mcast group */
	strncpy(nlmsg_data(nlh), msg, msg_size);

	int res = nlmsg_unicast(nl_sk, skb_out, pid);

	if (res < 0) printk(KERN_INFO "Error while sending back to user\n");
}

static struct netlink_kernel_cfg cfg = {
	.groups = 1,
	.input = hello_nl_recv_msg,
};

static int __init netlink_init(void) {
	nl_sk = netlink_kernel_create(&init_net, NETLINK_USER, &cfg);

	if (!nl_sk) {
		printk(KERN_ALERT "Error creating socket.\n");
		return -1;
	}

	return 0;
}

static void __exit netlink_exit(void) { netlink_kernel_release(nl_sk); }

MODULE_LICENSE("GPL");
module_init(netlink_init);
module_exit(netlink_exit);