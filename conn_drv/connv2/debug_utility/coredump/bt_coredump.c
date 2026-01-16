#include <linux/completion.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/mm.h>
#include <linux/ratelimit.h>
#include <linux/slab.h>
#include <linux/time.h>
#include <linux/timer.h>
#include <linux/vmalloc.h>
#include <linux/string.h>

/* for uevent */
#include <linux/miscdevice.h>   /* for misc_register, and SYNTH_MINOR */
#include <linux/kobject.h>

static struct miscdevice bt_object;


void btdumpUeventInit(void)
{
	int ret = 0;

	/* dev init */
	bt_object.name = "bt_dump";

	bt_object.minor = MISC_DYNAMIC_MINOR;
	ret = misc_register(&bt_object);
	if (ret) {
		pr_info("btdump misc_register error:%d\n", ret);
		return;
	}

	ret = kobject_uevent(
			&bt_object.this_device->kobj, KOBJ_ADD);

	if (ret) {
		misc_deregister(&bt_object);
		pr_info("btdump uevent creat fail:%d\n", ret);
		return;
	}

	pr_info("btdump Uevent init success. \n");
}

void btdumpUeventDeinit(void)
{
	pr_info("btdump Uevent deinit. \n");
	misc_deregister(&bt_object);
}

void btdumpSendUeventHandler(char* subtype)
{
	int ret;
	char *envp[2];
	char event_string[300]= {"BT_PANIC="};

	size_t pos = strlen(event_string);
	snprintf(event_string + pos, strlen(subtype),subtype);

	envp[0] = event_string;
	envp[1] = NULL;
        btdumpUeventInit();
	pr_info("btdump Send BT UEvent. event_string = %s\n",event_string);

	ret = kobject_uevent_env(&bt_object.this_device->kobj,
				 KOBJ_CHANGE, envp);

	if (ret != 0)
		pr_info("btdump uevent failed. \n");

	btdumpUeventDeinit();
}
