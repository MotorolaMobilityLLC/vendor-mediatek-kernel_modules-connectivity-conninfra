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

#include <linux/memblock.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>

#include <connectivity_build_in_adapter.h>

#include "consys_reg_mng.h"
#include "mt6885_consys_reg.h"
#include "consys_hw.h"
#include "consys_reg_util.h"

static int consys_reg_init(struct platform_device *pdev);
static int consys_reg_deinit(void);
static int consys_check_reg_readable(void);
static int consys_is_consys_reg(unsigned int addr);

struct consys_reg_mng_ops g_dev_consys_reg_ops = {
	.consys_reg_mng_init = consys_reg_init,
	.consys_reg_mng_deinit = consys_reg_deinit,

	.consys_reg_mng_check_reable = consys_check_reg_readable,
	.consys_reg_mng_is_consys_reg = consys_is_consys_reg
};

const char* consys_base_addr_index_to_str[8] = {
	"CONN_INFRA_RGU_BASE",
	"CONN_INFRA_CFG_BASE",
	"CONN_HOST_CSR_TOP_BASE",
	"INFRACFG_AO_BASE",
	"TOPRGU_BASE",
	"SPM_BASE",
	"INFRACFG_BASE",
	"CONN_WT_SLP_CTL_REG",
};

struct consys_base_addr conn_reg;

struct consys_reg_mng_ops* get_consys_reg_mng_ops(void)
{
	return &g_dev_consys_reg_ops;
}

struct consys_base_addr* get_conn_reg_base_addr()
{
	return &conn_reg;
}

int consys_check_reg_readable(void)
{
	int flag = 0;
#if 0
	UINT32 value = 0;
	P_DEV_WMT pDev = &gDevWmt;

	if (osal_test_bit(WMT_STAT_PWR, &pDev->state)) {
		/*check connsys clock and sleep status*/
		CONSYS_REG_WRITE(conn_reg.mcu_conn_hif_on_base, CONSYS_CLOCK_CHECK_VALUE);
		udelay(1000);
		value = CONSYS_REG_READ(conn_reg.mcu_conn_hif_on_base);
		if ((value & CONSYS_HCLK_CHECK_BIT) &&
		    (value & CONSYS_OSCCLK_CHECK_BIT))
			flag = 1;
	}

	if (!flag)
		pr_err("connsys clock check fail 0x18007000(0x%x)\n", value);
#endif
	return flag;
}


int consys_is_consys_reg(unsigned int addr)
{
	return 0;
}

int consys_reg_init(struct platform_device *pdev)
{
	int iRet = -1;
	struct device_node *node = NULL;
	struct consys_reg_base_addr *base_addr = NULL;
	int flag, i = 0;

	node = pdev->dev.of_node;
	pr_info("[%s] node=[%p]\n", __func__, node);
	if (node) {
		for (i = 0; i < CONSYS_BASE_ADDR_MAX; i++) {
			base_addr = &conn_reg.reg_base_addr[i];

			base_addr->vir_addr =
				(unsigned long) of_iomap(node, i);
			of_get_address(node, i, &(base_addr->size), &flag);

			pr_info("Get Index(%d-%s) baseAddr=(0x%zx) size=(0x%zx)",
				i, consys_base_addr_index_to_str[i],
				base_addr->vir_addr, base_addr->size);
		}

	} else {
		pr_err("[%s] can't find CONSYS compatible node\n", __func__);
		return iRet;
	}
	return 0;

}

static int consys_reg_deinit(void)
{
	return 0;
}
