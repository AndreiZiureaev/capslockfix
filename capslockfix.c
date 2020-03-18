/**
 * When Ubuntu unsuspends, the CapsLock LED is always on, even though CapsLock itself is off.
 * This "fixes" it by flashing the LED a few times every time the system wakes up.
 * The LED's behavior is extremely strange after a suspend, but flashing it seems to do the job.
 */

#include <linux/module.h>
#include <linux/vt_kern.h>
#include <linux/suspend.h>

MODULE_DESCRIPTION("A workaround for CapsLock being on when waking after suspend");
MODULE_AUTHOR("Andrei Ziureaev");
MODULE_LICENSE("GPL");

#define DELAY HZ/5
#define ALL_LEDS_ON 0x07
#define RESTORE_LEDS 0xFF
#define MAX_SPAM 55

static struct timer_list my_timer;
static char ledstatus = 0;
static int spam_amount = 0;

static void my_timer_func(struct timer_list *unused)
{
    if (ledstatus == ALL_LEDS_ON)
        ledstatus = RESTORE_LEDS;
    else
        ledstatus = ALL_LEDS_ON;

    if (vc_cons[fg_console].d) {
        vc_cons[fg_console].d->port.tty->driver->ops->ioctl(vc_cons[fg_console].d->port.tty, KDSETLED, ledstatus);
    }

    if (spam_amount) {
        spam_amount--;
        mod_timer(&my_timer, jiffies + DELAY);
    }
}

static int resume_event(struct notifier_block *nb, unsigned long action, void *data)
{
    switch (action) {
    case PM_POST_SUSPEND:
        spam_amount = MAX_SPAM;
        mod_timer(&my_timer, jiffies + DELAY);
    }

    return NOTIFY_DONE;
}

static struct notifier_block resume_notifier = {
    .notifier_call = resume_event
};

static int __init init(void)
{
    timer_setup(&my_timer, my_timer_func, 0);
    register_pm_notifier(&resume_notifier);

    return 0;
}

static void __exit cleanup(void)
{
    unregister_pm_notifier(&resume_notifier);
    del_timer(&my_timer);
}

module_init(init);
module_exit(cleanup);
