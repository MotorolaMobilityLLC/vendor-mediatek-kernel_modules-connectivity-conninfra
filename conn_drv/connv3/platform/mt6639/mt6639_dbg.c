// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2022 MediaTek Inc.
 */

#include "connv3.h"
#include "connv3_hw.h"
#include "connv3_hw_dbg.h"

#include "mt6639_dbg.h"

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
static int connv3_conninfra_bus_dump_mt6639(
	enum connv3_drv_type drv_type, struct connv3_cr_cb *cb, void *data);

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
const struct connv3_platform_dbg_ops g_connv3_hw_dbg_mt6639 = {
	.dbg_bus_dump = connv3_conninfra_bus_dump_mt6639,
};

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

static int connv3_bus_check_ap2conn_on(struct connv3_cr_cb *cb, void *data)
{
	unsigned int trx;
	int ret;

	ret = cb->read(data, MT6639_AP2CONN_INFRA_ON_SLP_PROT, &trx);
	if (ret) {
		pr_err("[%s] check tx/rx error, ret=[%d]", __func__, ret);
		return false;
	}

	if ((trx & (0x1 << 6)) != 0) {
		pr_info("[%s] ap2conn_infra on check tx fail, slp=[0x%08x]", __func__, trx);
		return CONNV3_BUS_AP2CONN_TX_SLP_PROT_ERR;
	}
	if ((trx & (0x1 << 7)) != 0) {
		pr_info("[%s] ap2conn_infra on check rx fail, slp=[0x%08x]", __func__, trx);
		return CONNV3_BUS_AP2CONN_RX_SLP_PROT_ERR;
	}

	return 0;
}

static int connv3_bus_check_ap2conn_off(struct connv3_cr_cb *cb, void *data)
{
	unsigned int value;
	int ret, i;

	/* AP2CONN_INFRA OFF
	 * 1.Check "AP2CONN_INFRA ON step is ok"
	 * 2. Check conn_infra off bus clock
	 *    (Need to polling 4 times to confirm the correctness and polling every 1ms)
	 * - write 0x1 to 0x1802_3000[0], reset clock detect
	 * - 0x1802_3000[1] conn_infra off bus clock (should be 1'b1 if clock exist)
	 * - 0x1802_3000[2] osc clock (should be 1'b1 if clock exist)
	 * 3. Read conn_infra IP version
	 * - Read 0x1801_1000 = 0x03010001
	 * 4. Check conn_infra off domain bus hang irq status
	 * - 0x1802_3400[2:0], should be 3'b000, or means conn_infra off bus might hang
	 */

	/* Clock detect
	 */
	for (i = 0; i < 4; i++) {
		ret = cb->write_mask(data, MT6639_CONN_INFRA_CLK_DETECT, 0x1, 0x1);
		if (ret) {
			pr_notice("[%s] clock detect write fail, ret = %d", __func__, ret);
			break;
		}
		ret = cb->read(data, MT6639_CONN_INFRA_CLK_DETECT, &value);
		if (ret) {
			pr_notice("[%s] clock detect read fail, ret = %d", __func__, ret);
			break;
		}
		if ((value & 0x3) == 0x3)
			break;
	}
	if (ret)
		return CONNV3_BUS_CONN_INFRA_OFF_CLK_ERR;
	if ((value & 0x3) != 0x3) {
		pr_notice("[%s] clock detect fail, get: [0x%08x]", __func__, value);
		return CONNV3_BUS_CONN_INFRA_OFF_CLK_ERR;
	}

	/* Read IP version
	 */
	ret = cb->read(data, MT6639_CONN_INFRA_VERSION_ID_REG, &value);
	if (ret) {
		pr_notice("[%s] get conn_infra version fail, ret=[%d]", __func__, ret);
		return CONNV3_BUS_CONN_INFRA_OFF_CLK_ERR;
	}
	if (value != MT6639_CONN_INFRA_VERSION_ID) {
		pr_notice("[%s] get conn_infra version fail, expect:0x%08x, get:0x%08x",
			__func__, MT6639_CONN_INFRA_VERSION_ID, value);
		return CONNV3_BUS_CONN_INFRA_OFF_CLK_ERR;
	}

	/* Check bus timeout irq
	 */
	ret = cb->read(data, MT6639_CONN_INFRA_OFF_IRQ_REG, &value);
	if (ret) {
		pr_notice("[%s] read irq status fail, ret=[%d]", __func__, ret);
		return CONNV3_BUS_CONN_INFRA_BUS_HANG_IRQ;
	}
	if ((value & 0x7) != 0x0) {
		pr_notice("[%s] bus time out irq detect, get:0x%08x", __func__, value);
		return CONNV3_BUS_CONN_INFRA_BUS_HANG_IRQ;
	}

	return 0;
}

int connv3_conninfra_bus_dump_mt6639(
	enum connv3_drv_type drv_type, struct connv3_cr_cb *cb, void *data)
{
	int ret = 0;

	/* AP2CONN_INFRA ON check */
	if (drv_type == CONNV3_DRV_TYPE_WIFI) {
		ret = connv3_bus_check_ap2conn_on(cb, data);
		if (ret != 0)
			return ret;
	}

	/* Dump after conn_infra_on is ready
	 * - Connsys power debug - dump list
	 * - Conninfra bus debug - status result
	 * - conn_infra_cfg_clk - dump_list
	 */
	ret = connv3_hw_dbg_dump_utility(&mt6639_dmp_list_pwr_b, cb, data);
	if (ret)
		pr_notice("[%s] mt6639_dmp_list_pwr_b dump err=[%d]", __func__, ret);
	ret = connv3_hw_dbg_dump_utility(&mt6639_dmp_list_bus_a, cb, data);
	if (ret)
		pr_notice("[%s] mt6639_dmp_list_bus_a dump err=[%d]", __func__, ret);
	ret = connv3_hw_dbg_dump_utility(&mt6639_dmp_list_cfg_clk_a, cb, data);
	if (ret)
		pr_notice("[%s] mt6639_dmp_list_cfg_clk_a dump err=[%d]", __func__, ret);

	/* AP2CONN_INFRA OFF check */
	ret = connv3_bus_check_ap2conn_off(cb, data);
	if (ret)
		return ret;

	ret = connv3_hw_dbg_dump_utility(&mt6639_dmp_list_pwr_c, cb, data);
	if (ret)
		pr_notice("[%s] mt6639_dmp_list_pwr_c dump err=[%d]", __func__, ret);
	ret = connv3_hw_dbg_dump_utility(&mt6639_dmp_list_bus_b, cb, data);
	if (ret)
		pr_notice("[%s] mt6639_dmp_list_bus_b dump err=[%d]", __func__, ret);
	ret = connv3_hw_dbg_dump_utility(&mt6639_dmp_list_cfg_clk_b, cb, data);
	if (ret)
		pr_notice("[%s] mt6639_dmp_list_cfg_clk_b dump err=[%d]", __func__, ret);

	return 0;
}
