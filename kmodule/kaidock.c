#include <linux/module.h>
#include <linux/kernel.h>

static int loop = INT_MAX;
module_param(loop, int, 0644);
MODULE_PARM_DESC(loop, "specify the loop count");

static void kaidock_func(struct timer_list *timer);

DEFINE_TIMER(kaidock_timer, kaidock_func);

static void kaidock_func(struct timer_list *timer)
{
	printk(KERN_ERR "[s[2;60H[1;32;44mjiffies:0x%lx[0m[u\n", jiffies);
	if (--loop > 0) {
		do {
			mod_timer(timer, timer->expires + HZ);
		} while ((long)(timer->expires - jiffies) <= 0L);
	}
}

int init_module(void)
{
	kaidock_timer.expires = jiffies + HZ;
	add_timer(&kaidock_timer);
	return 0;
}

void cleanup_module(void) {
	del_timer_sync(&kaidock_timer);
}

MODULE_AUTHOR("taka");
MODULE_LICENSE("GPL");
