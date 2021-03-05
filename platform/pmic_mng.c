/*
 * Copyright (C) 2016 MediaTek Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 */
/*! \file
*    \brief  Declaration of library functions
*
*    Any definitions in this file will be shared among GLUE Layer and internal Driver Stack.
*/

#include "pmic_mng.h"

#include "osal.h"
#if COMMON_KERNEL_PMIC_SUPPORT
#include <linux/regulator/consumer.h>
#include <linux/mfd/mt6397/core.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/regmap.h>
#endif

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

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/

const struct consys_platform_pmic_ops* consys_platform_pmic_ops = NULL;
#if COMMON_KERNEL_PMIC_SUPPORT
struct regmap *g_regmap;
#endif

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#if COMMON_KERNEL_PMIC_SUPPORT
static void pmic_mng_get_regmap(struct platform_device *pdev)
{
	struct device_node *pmic_node;
	struct platform_device *pmic_pdev;
	struct mt6397_chip *chip;

	pmic_node = of_parse_phandle(pdev->dev.of_node, "pmic", 0);
	if (!pmic_node) {
		pr_info("get pmic_node fail\n");
		return;
	}

	pmic_pdev = of_find_device_by_node(pmic_node);
	if (!pmic_pdev) {
		pr_info("get pmic_pdev fail\n");
		return;
	}

	chip = dev_get_drvdata(&(pmic_pdev->dev));
	if (!chip) {
		pr_info("get chip fail\n");
		return;
	}

	g_regmap = chip->regmap;
	if (IS_ERR_VALUE(g_regmap)) {
		g_regmap = NULL;
		pr_info("get regmap fail\n");
	}
}
#endif

int pmic_mng_init(
	struct platform_device *pdev,
	struct conninfra_dev_cb* dev_cb,
	const struct conninfra_plat_data* plat_data)
{
#if COMMON_KERNEL_PMIC_SUPPORT
	pmic_mng_get_regmap(pdev);
#endif

	if (consys_platform_pmic_ops == NULL)
		consys_platform_pmic_ops =
			(const struct consys_platform_pmic_ops*)plat_data->platform_pmic_ops;

	if (consys_platform_pmic_ops && consys_platform_pmic_ops->consys_pmic_get_from_dts)
		consys_platform_pmic_ops->consys_pmic_get_from_dts(pdev, dev_cb);

	return 0;
}

int pmic_mng_deinit(void)
{
	consys_platform_pmic_ops = NULL;
	return 0;
}

int pmic_mng_common_power_ctrl(unsigned int enable)
{
	int ret = 0;
	if (consys_platform_pmic_ops &&
		consys_platform_pmic_ops->consys_pmic_common_power_ctrl)
		ret = consys_platform_pmic_ops->consys_pmic_common_power_ctrl(enable);
	return ret;
}

int pmic_mng_common_power_low_power_mode(unsigned int enable)
{
	int ret = 0;
	if (consys_platform_pmic_ops &&
		consys_platform_pmic_ops->consys_pmic_common_power_low_power_mode)
		ret = consys_platform_pmic_ops->consys_pmic_common_power_low_power_mode(enable);
	return ret;
}

int pmic_mng_wifi_power_ctrl(unsigned int enable)
{
	int ret = 0;
	if (consys_platform_pmic_ops &&
		consys_platform_pmic_ops->consys_pmic_wifi_power_ctrl)
		ret = consys_platform_pmic_ops->consys_pmic_wifi_power_ctrl(enable);
	return ret;

}

int pmic_mng_bt_power_ctrl(unsigned int enable)
{
	int ret = 0;
	if (consys_platform_pmic_ops &&
		consys_platform_pmic_ops->consys_pmic_bt_power_ctrl)
		ret = consys_platform_pmic_ops->consys_pmic_bt_power_ctrl(enable);
	return ret;
}

int pmic_mng_gps_power_ctrl(unsigned int enable)
{
	int ret = 0;
	if (consys_platform_pmic_ops &&
		consys_platform_pmic_ops->consys_pmic_gps_power_ctrl)
		ret = consys_platform_pmic_ops->consys_pmic_gps_power_ctrl(enable);
	return ret;
}

int pmic_mng_fm_power_ctrl(unsigned int enable)
{
	int ret = 0;
	if (consys_platform_pmic_ops &&
		consys_platform_pmic_ops->consys_pmic_fm_power_ctrl)
		ret = consys_platform_pmic_ops->consys_pmic_fm_power_ctrl(enable);
	return ret;
}


int pmic_mng_event_cb(unsigned int id, unsigned int event)
{
	if (consys_platform_pmic_ops &&
		consys_platform_pmic_ops->consys_pmic_event_notifier)
		consys_platform_pmic_ops->consys_pmic_event_notifier(id, event);
	return 0;
}

int pmic_mng_raise_voltage(unsigned int drv_type, bool raise, bool onoff)
{
	int ret = 0;

	if (consys_platform_pmic_ops &&
		consys_platform_pmic_ops->consys_pmic_raise_voltage)
		ret = consys_platform_pmic_ops->consys_pmic_raise_voltage(drv_type, raise, onoff);
	return ret;
}
