// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2020 MediaTek Inc.
 */

#define pr_fmt(fmt) KBUILD_MODNAME "@(%s:%d) " fmt, __func__, __LINE__

#include <asm/atomic.h>
#include <linux/delay.h>
#include <linux/jiffies.h>
#include <linux/platform_device.h>
#include <linux/regulator/consumer.h>
#include <linux/timer.h>

#include "connv3_hw.h"
#include "connv3_pinctrl_mng.h"

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/


/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

int connv3_plt_pinctrl_setup_pre_mt6983(void);
int connv3_plt_pinctrl_setup_done_mt6983(void);
int connv3_plt_pinctrl_remove_mt6983(void);

const struct connv3_platform_pinctrl_ops g_connv3_platform_pinctrl_ops_mt6983 = {
	.pinctrl_setup_pre = connv3_plt_pinctrl_setup_pre_mt6983,
	.pinctrl_setup_done = connv3_plt_pinctrl_setup_done_mt6983,
	.pinctrl_remove = connv3_plt_pinctrl_remove_mt6983,
};


int connv3_plt_pinctrl_setup_pre_mt6983(void)
{
	pr_info("[%s] =====", __func__);
	return 0;
}

int connv3_plt_pinctrl_setup_done_mt6983(void)
{
	pr_info("[%s] =====", __func__);
	return 0;
}

int connv3_plt_pinctrl_remove_mt6983(void)
{
	pr_info("[%s] =====", __func__);
	return 0;
}

