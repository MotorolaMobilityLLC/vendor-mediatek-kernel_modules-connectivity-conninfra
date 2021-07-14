/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2020 MediaTek Inc.
 */


/* AUTO-GENERATED FILE.  DO NOT MODIFY.
 *
 * This file, mt6983_pos_gen.c was automatically generated
 * by the tool from the POS data DE provided.
 * It should not be modified by hand.
 *
 * Reference POS file,
 * - Lepin_power_on_sequence_20210628.xlsx
 * - Lepin_conn_infra_sub_task_210630.xlsx
 * - conn_infra_cmdbt_instr_autogen_se_20210503.txt
 */


#ifndef CFG_CONNINFRA_ON_CTP
#include <linux/types.h>
#include <linux/clk.h>
#include <linux/io.h>
#endif
#include "consys_hw.h"
#include "consys_reg_util.h"
#include "mt6983_consys_reg_offset.h"
#include "mt6983.h"
#include "mt6983_pos.h"
#include "mt6983_pos_gen.h"
#include "conninfra.h"


const unsigned int g_cmdbt_dwn_value_ary[1024] = {
	0x16000400, 0x16011805, 0x16100A00, 0x16111805, 0x16200045, 0x16210000, 0xCCCCCCCC, 0x16002060,
	0x16011801, 0x1610FFFF, 0x1611FFFF, 0x31000100, 0x16002070, 0x16011801, 0x1610FFFF, 0x16110000,
	0x31000100, 0x1600C000, 0x16011801, 0x16100000, 0x16110000, 0x31000100, 0x1600C008, 0x16011801,
	0x16100000, 0x16110000, 0x31000100, 0x1600D00C, 0x16011801, 0x161000BF, 0x16110000, 0x31000100,
	0x16000660, 0x16011805, 0x16100C60, 0x16111805, 0x1620002D, 0x16210000, 0xCCCCCCCC, 0x1600063C,
	0x16011805, 0x16100C3C, 0x16111805, 0x16200009, 0x16210000, 0xCCCCCCCC, 0x1600051C, 0x16011805,
	0x16100B1C, 0x16111805, 0x1620001B, 0x16210000, 0xCCCCCCCC, 0x1600C0D0, 0x16011801, 0x16100001,
	0x16110000, 0x31000100, 0x16000588, 0x16011805, 0x16100B88, 0x16111805, 0x1620002D, 0x16210000,
	0xCCCCCCCC, 0x16000514, 0x16011805, 0x16100B14, 0x16111805, 0x16200002, 0x16210000, 0xCCCCCCCC,
	0x1600D000, 0x16011804, 0x16100200, 0x16110000, 0x31000100, 0x1600D000, 0x16011804, 0x16100200,
	0x161107F4, 0x31000100, 0x1600D000, 0x16011804, 0x16100204, 0x161107F4, 0x31000100, 0x1600D000,
	0x16011804, 0x1610020C, 0x161107F4, 0x31000100, 0x1600D000, 0x16011804, 0x1610001C, 0x161107F4,
	0x31000100, 0x6000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x16000400, 0x16011805, 0x16100A00, 0x16111805, 0x16200047, 0x16210000, 0xBBBBBBBB, 0x16002060,
	0x16011801, 0x1610FFFF, 0x1611FFFF, 0x31000100, 0x16002070, 0x16011801, 0x1610FFFF, 0x16110000,
	0x31000100, 0x1600051C, 0x16011805, 0x16100B1C, 0x16111805, 0x16200048, 0x16210000, 0xBBBBBBBB,
	0x1600C000, 0x16011801, 0x16100000, 0x16110000, 0x31000100, 0x1600C008, 0x16011801, 0x16100000,
	0x16110000, 0x31000100, 0x1600063C, 0x16011805, 0x16100C3C, 0x16111805, 0x16200009, 0x16210000,
	0xBBBBBBBB, 0x1600D00C, 0x16011801, 0x161000BF, 0x16110000, 0x31000100, 0x16000660, 0x16011805,
	0x16100C60, 0x16111805, 0x1620002D, 0x16210000, 0xBBBBBBBB, 0x6000000, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x18041014, 0x18011050, 0x18011100, 0x18011104, 0x18012000, 0x18012008, 0x18012020, 0x18012050,
	0x1804B000, 0x1804B004, 0x1804B008, 0x1804B010, 0x1804B024, 0x1804B070, 0x1804B074, 0x1804B350,
	0x1804B354, 0x1804B358, 0x1804B35C, 0x1804B360, 0x1804B364, 0x1804B368, 0x1804B36C, 0x1804B370,
	0x1804B374, 0x1804B378, 0x1804B37C, 0x1804B380, 0x1804B384, 0x1804B388, 0x1804B38C, 0x1804B390,
	0x1804B394, 0x1804B398, 0x1804B39C, 0x1804B3A0, 0x1804B3A4, 0x1804B3A8, 0x1804B3AC, 0x1804B3B0,
	0x1804B3B4, 0x1804B3B8, 0x1804B3BC, 0x1804B3C0, 0x1804B3C4, 0x1804B3C8, 0x1804B3CC, 0x1804B3D0,
	0x1804B3D4, 0x1804B3D8, 0x1804B3DC, 0x1804B3E0, 0x1804B3E4, 0x1804B3E8, 0x1804B3EC, 0x18040004,
	0x18040008, 0x1804000C, 0x18040010, 0x18040014, 0x18040018, 0x18040000, 0x1804001C, 0x18040020,
	0x18040024, 0x18040028, 0x18042008, 0x18012030, 0x18012038, 0x18012060, 0x18012070, 0x1801C000,
	0x1801C004, 0x1801C008, 0x1801C0C0, 0x1801C0C8, 0x1801C0D4, 0x1801C0D8, 0x1801C0DC, 0x1801C0E0,
	0x1801C0E4, 0x1801C0E8, 0x1801C0EC, 0x1801C0F0, 0x1801C0F4, 0x1801C0F8, 0x1801C0FC, 0x1801C100,
	0x1801C104, 0x1801C108, 0x1801C10C, 0x1801C110, 0x1801C114, 0x1801C118, 0x1801C11C, 0x1801C120,
	0x1801C124, 0x1801C128, 0x1801C0D0, 0x1801C230, 0x1801C238, 0x1801C23C, 0x1801C2D4, 0x1801C2DC,
	0x1801C400, 0x1801C404, 0x1801C408, 0x1801C464, 0x1801C468, 0x1801C46C, 0x1801C4D0, 0x1801C530,
	0x1801C534, 0x1801C58C, 0x1801C590, 0x1801C594, 0x1801C598, 0x1801C59C, 0x1801C5A0, 0x1801C5A4,
	0x1801C5A8, 0x1801C5AC, 0x1801C5B0, 0x1801C5B4, 0x1801C5B8, 0x1801C5BC, 0x1801C5C0, 0x1801C5C4,
	0x1801C5C8, 0x1801C5CC, 0x1801C5D0, 0x1801C5D4, 0x1801C5D8, 0x1801C5E0, 0x1801C5E4, 0x1801C654,
	0x1801C754, 0x1801C7B0, 0x1801C7B4, 0x1801C7C0, 0x1801C7E0, 0x1801C800, 0x1801C830, 0x1801D00C,
	0x1801D008, 0x1801D024, 0x1801D028, 0x1801D02C, 0x1801D03C, 0x1801D04C, 0x1801D054, 0x1801D058,
	0x1801D000, 0x1801D004, 0x1801B04C, 0x1801B0BC, 0x1801B070, 0x1801B074, 0x1801B500, 0x1801A000,
	0x1801A004, 0x1801A008, 0x1801A00C, 0x1801A018, 0x1801A024, 0x1801A028, 0x1801A02C, 0x1801A110,
	0x1801A200, 0x1801A204, 0x1801A208, 0x1801A20C, 0x1801A210, 0x1801A214, 0x1801A218, 0x1801A21C,
	0x1801A228, 0x1801A22C, 0x1801A230, 0x1801A234, 0x1801A238, 0x1801A23C, 0x1801A240, 0x1801A244,
	0x1801A248, 0x1801A304, 0x1801A30C, 0x1801A310, 0x1801A314, 0x1801A604, 0x1801A608, 0x1801A610,
	0x1801A620, 0x1801A630, 0x1801A640, 0x1801A650, 0x1801A660, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
};


void consys_set_if_pinmux_mt6983_gen(unsigned int enable)
{
	if (GPIO_REG_BASE == 0) {
		pr_err("GPIO_REG_BASE is not defined\n");
		return;
	}

	if (IOCFG_RT_REG_BASE == 0) {
		pr_err("IOCFG_RT_REG_BASE is not defined\n");
		return;
	}

	if (enable == 1) {
		/* set pinmux for the interface between D-die and A-die (Aux1) */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_REG_WRITE_MASK(GPIO_REG_BASE +
				CONSYS_GEN_GPIO_MODE26_OFFSET_ADDR, 0x11111000, 0x77777000);
			CONSYS_REG_WRITE_MASK(GPIO_REG_BASE +
				CONSYS_GEN_GPIO_MODE27_OFFSET_ADDR, 0x111111, 0x777777);
		#endif

		/* set pinmux driving to 4mA setting */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_REG_WRITE_MASK(IOCFG_RT_REG_BASE +
				CONSYS_GEN_DRV_CFG0_OFFSET_ADDR, 0x1248, 0x7FF8);
		#endif

		/* set pinmux PUPD setting */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_REG_WRITE_MASK(IOCFG_RT_REG_BASE +
				CONSYS_GEN_PUPD_CFG0_CLR_OFFSET_ADDR, 0xC, 0xC);
		#endif
	} else {
		/* set pinmux for the interface between D-die and A-die (Aux0) */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_REG_WRITE_MASK(GPIO_REG_BASE +
				CONSYS_GEN_GPIO_MODE26_OFFSET_ADDR, 0x0, 0x77777000);
			CONSYS_REG_WRITE_MASK(GPIO_REG_BASE +
				CONSYS_GEN_GPIO_MODE27_OFFSET_ADDR, 0x0, 0x777777);
		#endif

		/* set pinmux PUPD setting */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_REG_WRITE_MASK(IOCFG_RT_REG_BASE +
				CONSYS_GEN_PUPD_CFG0_SET_OFFSET_ADDR, 0xC, 0xC);
		#endif
	}
}

void consys_set_gpio_tcxo_mode_mt6983_gen(unsigned int tcxo_mode, unsigned int enable)
{
	if (GPIO_REG_BASE == 0) {
		pr_err("GPIO_REG_BASE is not defined\n");
		return;
	}

	if (enable == 1) {
		/* set GPIO159 pinmux for TCXO mode (Aux3) */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			if (tcxo_mode == 1) {
				CONSYS_REG_WRITE(GPIO_REG_BASE +
					CONSYS_GEN_GPIO_MODE19_CLR_OFFSET_ADDR, 0x70000000);
				CONSYS_REG_WRITE(GPIO_REG_BASE +
					CONSYS_GEN_GPIO_MODE19_SET_OFFSET_ADDR, 0x30000000);
			}
		#endif
	} else {
		/* set GPIO159 pinmux for TCXO mode (Aux0) */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			if (tcxo_mode == 1) {
				CONSYS_REG_WRITE(GPIO_REG_BASE +
					CONSYS_GEN_GPIO_MODE19_CLR_OFFSET_ADDR, 0x7000000);
			}
		#endif
	}
}

int consys_conninfra_on_power_ctrl_mt6983_gen(unsigned int enable)
{
	int check = 0;

	if (SPM_REG_BASE == 0) {
		pr_err("SPM_REG_BASE is not defined\n");
		return -1;
	}

	if (INFRACFG_AO_REG_BASE == 0) {
		pr_err("INFRACFG_AO_REG_BASE is not defined\n");
		return -1;
	}

	if (enable == 1) {
		/* turn on SPM clock */
		/* (apply this for SPM's CONNSYS power control related CR accessing) */
		CONSYS_REG_WRITE_MASK(SPM_REG_BASE +
			CONSYS_GEN_POWERON_CONFIG_EN_OFFSET_ADDR, 0xB160001, 0xFFFF0001);

		/* assert "conn_infra_on" primary part power on, set "connsys_on_domain_pwr_on"=1 */
		CONSYS_SET_BIT(SPM_REG_BASE +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR, (0x1 << 2));

		/* check "conn_infra_on" primary part power status, */
		/* check "connsys_on_domain_pwr_ack"=1 */
		/* (polling "10 times" and each polling interval is "0.5ms") */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			check = 0;
			CONSYS_REG_BIT_POLLING(SPM_REG_BASE +
				CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR,
				30, 1, 10, 500, check);
			if (check != 0) {
				pr_err("check conn_infra_on primary part power status fail, Status=0x%08x\n",
					CONSYS_REG_READ(SPM_REG_BASE +
						CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR));
			}
		#endif

		/* assert "conn_infra_on" secondary part power on, */
		/* set "connsys_on_domain_pwr_on_s"=1 */
		CONSYS_SET_BIT(SPM_REG_BASE +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR, (0x1 << 3));

		/* check "conn_infra_on" secondary part power status, */
		/* check "connsys_on_domain_pwr_ack_s"=1 */
		/* (polling "10 times" and each polling interval is "0.5ms") */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			check = 0;
			CONSYS_REG_BIT_POLLING(SPM_REG_BASE +
				CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR,
				31, 1, 10, 500, check);
			if (check != 0) {
				pr_err("check conn_infra_on secondary part power status fail, Status=0x%08x\n",
					CONSYS_REG_READ(SPM_REG_BASE +
						CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR));
			}
		#endif

		/* turn on AP-to-CONNSYS bus clock, */
		/* set "conn_clk_dis"=0 */
		/* (apply this for bus clock toggling) */
		CONSYS_CLR_BIT(SPM_REG_BASE +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR, (0x1 << 4));

		udelay(1);

		/* de-assert "conn_infra_on" isolation, set "connsys_iso_en"=0 */
		CONSYS_CLR_BIT(SPM_REG_BASE +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR, (0x1 << 1));

		/* de-assert CONNSYS S/W reset (SPM CR), set "ap_sw_rst_b"=1 */
		CONSYS_SET_BIT(SPM_REG_BASE +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR, (0x1 << 0));

		udelay(500);

		/* Turn off AP2CONN AHB RX bus sleep protect */
		/* (apply this for INFRA AXI bus accessing when CONNSYS had been turned on) */
		CONSYS_CLR_BIT(INFRACFG_AO_REG_BASE +
			CONSYS_GEN_MCU_CONNSYS_PROTECT_EN_STA_0_OFFSET_ADDR, (0x1 << 0));

		/* check  AP2CONN AHB RX bus sleep protect turn off */
		/* (polling "100 times" and each polling interval is "0.5ms") */
		/* If AP2CONN (TX/RX) protect turn off fail, power on fail. */
		/* (DRV access connsys CR will get 0 ) */
		check = 0;
		CONSYS_REG_BIT_POLLING(INFRACFG_AO_REG_BASE +
			CONSYS_GEN_MCU_CONNSYS_PROTECT_RDY_STA_0_OFFSET_ADDR,
			0, 0, 100, 500, check);
		if (check != 0) {
			pr_err("check  AP2CONN AHB RX bus sleep protect turn off fail, Status=0x%08x\n",
				CONSYS_REG_READ(INFRACFG_AO_REG_BASE +
					CONSYS_GEN_MCU_CONNSYS_PROTECT_RDY_STA_0_OFFSET_ADDR));
		}

		/* Turn off AP2CONN AHB TX bus sleep protect */
		/* (apply this for INFRA AXI bus accessing when CONNSYS had been turned on) */
		CONSYS_CLR_BIT(INFRACFG_AO_REG_BASE +
			CONSYS_GEN_INFRASYS_PROTECT_EN_STA_1_OFFSET_ADDR, (0x1 << 12));

		/* check  AP2CONN AHB TX bus sleep protect turn off */
		/* (polling "100 times" and each polling interval is "0.5ms") */
		/* If AP2CONN (TX/RX) protect turn off fail, power on fail. */
		/* (DRV access connsys CR will get 0 ) */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			check = 0;
			CONSYS_REG_BIT_POLLING(INFRACFG_AO_REG_BASE +
				CONSYS_GEN_INFRASYS_PROTECT_RDY_STA_1_OFFSET_ADDR,
				12, 0, 100, 500, check);
			if (check != 0) {
				pr_err("check  AP2CONN AHB TX bus sleep protect turn off fail, Status=0x%08x\n",
					CONSYS_REG_READ(INFRACFG_AO_REG_BASE +
						CONSYS_GEN_INFRASYS_PROTECT_RDY_STA_1_OFFSET_ADDR));
			}
		#endif

		/* Turn off CONN2AP AXI RX bus sleep protect */
		/* (disable sleep protection when CONNSYS had been turned on) */
		CONSYS_CLR_BIT(INFRACFG_AO_REG_BASE +
			CONSYS_GEN_INFRASYS_PROTECT_EN_STA_0_OFFSET_ADDR, (0x1 << 8));

		/* Turn off CONN2AP AXI TX bus sleep protect */
		/* (disable sleep protection when CONNSYS had been turned on) */
		CONSYS_CLR_BIT(INFRACFG_AO_REG_BASE +
			CONSYS_GEN_MCU_CONNSYS_PROTECT_EN_STA_0_OFFSET_ADDR, (0x1 << 1));

		mdelay(5);
	} else {
		/* Turn on AP2CONN AHB TX bus sleep protect */
		CONSYS_SET_BIT(INFRACFG_AO_REG_BASE +
			CONSYS_GEN_INFRASYS_PROTECT_EN_STA_1_OFFSET_ADDR, (0x1 << 12));

		/* check  AP2CONN AHB TX bus sleep protect turn on */
		/* (polling "100 times" and each polling interval is "0.5ms") */
		/* If AP2CONN (TX/RX) protect turn off fail, power on fail. */
		/* (DRV access connsys CR will get 0 ) */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			check = 0;
			CONSYS_REG_BIT_POLLING(INFRACFG_AO_REG_BASE +
				CONSYS_GEN_INFRASYS_PROTECT_RDY_STA_1_OFFSET_ADDR,
				12, 1, 100, 500, check);
			if (check != 0) {
				pr_err("check  AP2CONN AHB TX bus sleep protect turn on fail, Status=0x%08x\n",
					CONSYS_REG_READ(INFRACFG_AO_REG_BASE +
						CONSYS_GEN_INFRASYS_PROTECT_RDY_STA_1_OFFSET_ADDR));
			}
		#endif

		/* Turn on AP2CONN AHB RX bus sleep protect */
		CONSYS_SET_BIT(INFRACFG_AO_REG_BASE +
			CONSYS_GEN_MCU_CONNSYS_PROTECT_EN_STA_0_OFFSET_ADDR, (0x1 << 0));

		/* check  AP2CONN AHB RX bus sleep protect turn on */
		/* (polling "100 times" and each polling interval is "0.5ms") */
		/* If AP2CONN (TX/RX) protect turn off fail, power on fail. */
		/* (DRV access connsys CR will get 0 ) */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			check = 0;
			CONSYS_REG_BIT_POLLING(INFRACFG_AO_REG_BASE +
				CONSYS_GEN_MCU_CONNSYS_PROTECT_RDY_STA_0_OFFSET_ADDR,
				0, 1, 100, 500, check);
			if (check != 0) {
				pr_err("check  AP2CONN AHB RX bus sleep protect turn on fail, Status=0x%08x\n",
					CONSYS_REG_READ(INFRACFG_AO_REG_BASE +
						CONSYS_GEN_MCU_CONNSYS_PROTECT_RDY_STA_0_OFFSET_ADDR));
			}
		#endif

		/* Turn on CONN2AP AXI TX bus sleep protect */
		/* (disable sleep protection when CONNSYS had been turned on) */
		CONSYS_SET_BIT(INFRACFG_AO_REG_BASE +
			CONSYS_GEN_MCU_CONNSYS_PROTECT_EN_STA_0_OFFSET_ADDR, (0x1 << 1));

		/* check  CONN2AP AXI TX bus sleep protect turn on */
		/* (polling "100 times" and each polling interval is "0.5ms") */
		/* If CONN2AP (TX/RX) protect turn off fail, power on fail. */
		/* (DRV access connsys CR will get 0 ) */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			check = 0;
			CONSYS_REG_BIT_POLLING(INFRACFG_AO_REG_BASE +
				CONSYS_GEN_MCU_CONNSYS_PROTECT_RDY_STA_0_OFFSET_ADDR,
				1, 1, 100, 500, check);
			if (check != 0) {
				pr_err("check  CONN2AP AXI TX bus sleep protect turn on fail, Status=0x%08x\n",
					CONSYS_REG_READ(INFRACFG_AO_REG_BASE +
						CONSYS_GEN_MCU_CONNSYS_PROTECT_RDY_STA_0_OFFSET_ADDR));
			}
		#endif

		/* Turn on CONN2AP AXI RX bus sleep protect */
		/* (disable sleep protection when CONNSYS had been turned on) */
		CONSYS_SET_BIT(INFRACFG_AO_REG_BASE +
			CONSYS_GEN_INFRASYS_PROTECT_EN_STA_0_OFFSET_ADDR, (0x1 << 8));

		/* check  CONN2AP AXI RX bus sleep protect turn on */
		/* (polling "100 times" and each polling interval is "0.5ms") */
		/* If CONN2AP (TX/RX) protect turn off fail, power on fail. */
		/* (DRV access connsys CR will get 0 ) */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			check = 0;
			CONSYS_REG_BIT_POLLING(INFRACFG_AO_REG_BASE +
				CONSYS_GEN_INFRASYS_PROTECT_RDY_STA_0_OFFSET_ADDR,
				8, 1, 100, 500, check);
			if (check != 0) {
				pr_err("check  CONN2AP AXI RX bus sleep protect turn on fail, Status=0x%08x\n",
					CONSYS_REG_READ(INFRACFG_AO_REG_BASE +
						CONSYS_GEN_INFRASYS_PROTECT_RDY_STA_0_OFFSET_ADDR));
			}
		#endif

		/* assert "conn_infra_on" isolation, set "connsys_iso_en"=1 */
		CONSYS_SET_BIT(SPM_REG_BASE +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR, (0x1 << 1));

		/* assert CONNSYS S/W reset (SPM CR), set "ap_sw_rst_b"=0 */
		CONSYS_CLR_BIT(SPM_REG_BASE +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR, (0x1 << 0));

		/* turn off AP-to-CONNSYS bus clock, */
		/* set "conn_clk_dis"=1 */
		/* (apply this for bus clock gating) */
		CONSYS_SET_BIT(SPM_REG_BASE +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR, (0x1 << 4));

		udelay(1);

		/* de-assert "conn_infra_on" primary part power on, */
		/* set "connsys_on_domain_pwr_on"=0 */
		CONSYS_CLR_BIT(SPM_REG_BASE +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR, (0x1 << 2));

		/* de-assert "conn_infra_on" secondary part power on, */
		/* set "connsys_on_domain_pwr_on_s"=0 */
		CONSYS_CLR_BIT(SPM_REG_BASE +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR, (0x1 << 3));
	}

	return 0;
}

int consys_polling_chipid_mt6983_gen(unsigned int *pconsys_ver_id)
{
	int check = 0;
	int retry = 0;
	unsigned int consys_ver_id = 0;

	if (CONN_CFG_BASE == 0) {
		pr_err("CONN_CFG_BASE is not defined\n");
		return -1;
	}

	/* check CONN_INFRA IP Version */
	/* (polling "10 times" for specific project code and each polling interval is "1ms") */
	retry = 11;
	while (retry-- > 0) {
		consys_ver_id = CONSYS_REG_READ(
			CONN_CFG_BASE +
			CONSYS_GEN_IP_VERSION_OFFSET_ADDR);
		if (consys_ver_id == CONSYS_GEN_CONN_HW_VER) {
			check = 0;
			pr_info("Consys HW version id(0x%08x), retry(%d)\n", consys_ver_id, retry);
			if (pconsys_ver_id != NULL)
				*pconsys_ver_id = consys_ver_id;
			break;
		}
		check = -1;
		usleep_range(1000, 2000);
	}

	if (check != 0) {
		pr_err("Read CONSYS version id fail. Expect 0x%08x but get 0x%08x\n",
			CONSYS_GEN_CONN_HW_VER, consys_ver_id);
		return -1;
	}

	return 0;
}

unsigned int consys_emi_set_remapping_reg_mt6983_gen(
		phys_addr_t con_emi_base_addr,
		phys_addr_t md_shared_emi_base_addr,
		unsigned int emi_base_addr_offset)
{
	if (CONN_BUS_CR_BASE == 0) {
		pr_err("CONN_BUS_CR_BASE is not defined\n");
		return -1;
	}

	/* driver should set the following configuration */
	if (con_emi_base_addr) {
		CONSYS_REG_WRITE_OFFSET_RANGE(CONN_BUS_CR_BASE +
			CONSYS_GEN_CONN2AP_REMAP_MCU_EMI_BASE_ADDR_OFFSET_ADDR,
			con_emi_base_addr, 0, emi_base_addr_offset, 20);
	}

	pr_info("connsys_emi_base=[0x%llx] remap cr: connsys=[0x%08x]\n",
		con_emi_base_addr,
		CONSYS_REG_READ(CONN_BUS_CR_BASE +
			CONSYS_GEN_CONN2AP_REMAP_MCU_EMI_BASE_ADDR_OFFSET_ADDR));

	if (md_shared_emi_base_addr) {
		CONSYS_REG_WRITE_OFFSET_RANGE(CONN_BUS_CR_BASE +
			CONSYS_GEN_CONN2AP_REMAP_MD_SHARE_EMI_BASE_ADDR_OFFSET_ADDR,
			md_shared_emi_base_addr, 0, emi_base_addr_offset, 20);
	}

	pr_info("mcif_emi_base=[0x%llx] remap cr: mcif=[0x%08x]\n",
		md_shared_emi_base_addr,
		CONSYS_REG_READ(CONN_BUS_CR_BASE +
			CONSYS_GEN_CONN2AP_REMAP_MD_SHARE_EMI_BASE_ADDR_OFFSET_ADDR));

	CONSYS_REG_WRITE_MASK(CONN_BUS_CR_BASE +
		CONSYS_GEN_CONN2AP_REMAP_WF_PERI_BASE_ADDR_OFFSET_ADDR, 0x1000, 0xFFFFF);
	CONSYS_REG_WRITE_MASK(CONN_BUS_CR_BASE +
		CONSYS_GEN_CONN2AP_REMAP_BT_PERI_BASE_ADDR_OFFSET_ADDR, 0x1000, 0xFFFFF);
	CONSYS_REG_WRITE_MASK(CONN_BUS_CR_BASE +
		CONSYS_GEN_CONN2AP_REMAP_GPS_PERI_BASE_ADDR_OFFSET_ADDR, 0x1000, 0xFFFFF);
	CONSYS_REG_WRITE_MASK(CONN_BUS_CR_BASE +
		CONSYS_GEN_SCPSYS_SRAM_BASE_ADDR_OFFSET_ADDR, 0x1C60, 0xFFFFF);

	return 0;
}

void consys_init_conninfra_sysram_mt6983_gen(void)
{
	#ifndef CONFIG_FPGA_EARLY_PORTING
	void __iomem *addr = NULL;
	#endif

	if (CONN_BUS_CR_BASE == 0) {
		pr_err("CONN_BUS_CR_BASE is not defined\n");
		return;
	}

	/* initial conn_infra_sysram value */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		if (CONN_INFRA_SYSRAM_SIZE == 0) {
			pr_err("CONN_INFRA_SYSRAM_SIZE is 0.\n");
			return;
		}

		#ifdef CFG_CONNINFRA_ON_CTP
			memset_io(CONSYS_GEN_CONN_INFRA_SYSRAM_BASE_OFFSET_ADDR, 0x0, CONN_INFRA_SYSRAM_SIZE);
		#else
			addr = ioremap(CONSYS_GEN_CONN_INFRA_SYSRAM_BASE_OFFSET_ADDR, CONN_INFRA_SYSRAM_SIZE);
			if (addr != NULL) {
				memset_io(addr, 0x0, CONN_INFRA_SYSRAM_SIZE);
				iounmap(addr);
			} else
				pr_err("[%s] remap 0x%08x fail", __func__, CONSYS_GEN_CONN_INFRA_SYSRAM_BASE_OFFSET_ADDR);
		#endif
	#endif

	/* set infra top emi address range */
	CONSYS_REG_WRITE(CONN_BUS_CR_BASE +
		CONSYS_GEN_CONN_INFRA_CONN2AP_EMI_PATH_ADDR_START_OFFSET_ADDR, 0x4000000);
	CONSYS_REG_WRITE(CONN_BUS_CR_BASE +
		CONSYS_GEN_CONN_INFRA_CONN2AP_EMI_PATH_ADDR_END_OFFSET_ADDR, 0x43FFFFFF);
}

void connsys_get_d_die_efuse_mt6983_gen(unsigned int *p_d_die_efuse)
{
	if (CONN_CFG_BASE == 0) {
		pr_err("CONN_CFG_BASE is not defined\n");
		return;
	}

	/* read D-die Efuse */
	if (p_d_die_efuse != NULL) {
		*p_d_die_efuse = CONSYS_REG_READ(CONN_CFG_BASE +
			CONSYS_GEN_EFUSE_OFFSET_ADDR);
	}
}

int connsys_d_die_cfg_mt6983_gen(void)
{
	if (CONN_RGU_ON_BASE == 0) {
		pr_err("CONN_RGU_ON_BASE is not defined\n");
		return -1;
	}

	/* conn_infra sysram hw control setting -> disable hw power dowm */
	CONSYS_REG_WRITE(CONN_RGU_ON_BASE +
		CONSYS_GEN_SYSRAM_HWCTL_PDN_OFFSET_ADDR, 0x0);

	/* conn_infra sysram hw control setting -> enable hw sleep */
	CONSYS_REG_WRITE(CONN_RGU_ON_BASE +
		CONSYS_GEN_SYSRAM_HWCTL_SLP_OFFSET_ADDR, 0x3);

	/* co-ext memory  hw control setting -> disable hw power dowm */
	CONSYS_REG_WRITE(CONN_RGU_ON_BASE +
		CONSYS_GEN_CO_EXT_MEM_HWCTL_PDN_OFFSET_ADDR, 0x0);

	/* co-ext memory  hw control setting -> enable hw sleep */
	CONSYS_REG_WRITE(CONN_RGU_ON_BASE +
		CONSYS_GEN_CO_EXT_MEM_HWCTL_SLP_OFFSET_ADDR, 0x1);

	return 0;
}

void connsys_wt_slp_top_ctrl_adie6635_mt6983_gen(void)
{
	if (CONN_WT_SLP_CTL_REG_BASE == 0) {
		pr_err("CONN_WT_SLP_CTL_REG_BASE is not defined\n");
		return;
	}

	/* wt_slp CR for A-die ck_en/wake_en control (ref. A-die power control) */
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_WF_CK_ADDR_OFFSET_ADDR, 0xAF40A04, 0xFFF0FFF);
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_WF_WAKE_ADDR_OFFSET_ADDR, 0xA00090, 0xFFF0FFF);
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_WF_ZPS_ADDR_OFFSET_ADDR, 0x9C008C, 0xFFF0FFF);
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BT_CK_ADDR_OFFSET_ADDR, 0xA08, 0xFFF);
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BT_WAKE_ADDR_OFFSET_ADDR, 0x94, 0xFFF);
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_TOP_CK_ADDR_OFFSET_ADDR, 0x2C, 0xFFF);
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_GPS_CK_ADDR_OFFSET_ADDR, 0xAFC0A0C, 0xFFF0FFF);
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_WF_B0_CMD_ADDR_OFFSET_ADDR, 0xF0, 0xFFF);
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_WF_B1_CMD_ADDR_OFFSET_ADDR, 0xF4, 0xFFF);
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_GPS_RFBUF_ADR_OFFSET_ADDR, 0xFC, 0xFFF);
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_GPS_L5_EN_ADDR_OFFSET_ADDR, 0xF8, 0xFFF);
}

void connsys_wt_slp_top_ctrl_adie6637_mt6983_gen(void)
{
	if (CONN_WT_SLP_CTL_REG_BASE == 0) {
		pr_err("CONN_WT_SLP_CTL_REG_BASE is not defined\n");
		return;
	}

	/* wt_slp CR for A-die ck_en/wake_en control (ref. A-die power control) */
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_WF_CK_ADDR_OFFSET_ADDR, 0xAF40A04, 0xFFF0FFF);
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_WF_WAKE_ADDR_OFFSET_ADDR, 0xA00090, 0xFFF0FFF);
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_WF_ZPS_ADDR_OFFSET_ADDR, 0x9C008C, 0xFFF0FFF);
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BT_CK_ADDR_OFFSET_ADDR, 0xA08, 0xFFF);
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BT_WAKE_ADDR_OFFSET_ADDR, 0x94, 0xFFF);
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_TOP_CK_ADDR_OFFSET_ADDR, 0xA00, 0xFFF);
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_GPS_CK_ADDR_OFFSET_ADDR, 0xAFC0A0C, 0xFFF0FFF);
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_WF_B0_CMD_ADDR_OFFSET_ADDR, 0xF0, 0xFFF);
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_WF_B1_CMD_ADDR_OFFSET_ADDR, 0xF4, 0xFFF);
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_GPS_RFBUF_ADR_OFFSET_ADDR, 0xFC, 0xFFF);
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_GPS_L5_EN_ADDR_OFFSET_ADDR, 0xF8, 0xFFF);
}

int connsys_a_die_switch_to_gpio_mode_mt6983_gen(void)
{
	if (GPIO_REG_BASE == 0) {
		pr_err("GPIO_REG_BASE is not defined\n");
		return -1;
	}

	if (consys_co_clock_type_mt6983() != CONNSYS_CLOCK_SCHEMATIC_52M_COTMS) {
		/* CONN_WF_CTRL2 swtich to GPIO mode, GPIO output value high */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			if (consys_get_adie_chipid_mt6983() == ADIE_6635) {
				CONSYS_REG_WRITE(GPIO_REG_BASE +
					CONSYS_GEN_GPIO_DIR6_SET_OFFSET_ADDR, 0x100000);
				CONSYS_REG_WRITE(GPIO_REG_BASE +
					CONSYS_GEN_GPIO_DOUT6_SET_OFFSET_ADDR, 0x100000);
				CONSYS_REG_WRITE(GPIO_REG_BASE +
					CONSYS_GEN_GPIO_MODE26_CLR_OFFSET_ADDR, 0x70000);
			}
		#endif

		/* CONN_WF_CTRL2 swtich to GPIO mode, GPIO output value low */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			if (consys_get_adie_chipid_mt6983() == ADIE_6637) {
				CONSYS_REG_WRITE(GPIO_REG_BASE +
					CONSYS_GEN_GPIO_DIR6_SET_OFFSET_ADDR, 0x100000);
				CONSYS_REG_WRITE(GPIO_REG_BASE +
					CONSYS_GEN_GPIO_DOUT6_CLR_OFFSET_ADDR, 0x100000);
				CONSYS_REG_WRITE(GPIO_REG_BASE +
					CONSYS_GEN_GPIO_MODE26_CLR_OFFSET_ADDR, 0x70000);
			}
		#endif
	} else if (consys_co_clock_type_mt6983() == CONNSYS_CLOCK_SCHEMATIC_52M_COTMS) {
		/* CONN_WF_CTRL2 swtich to GPIO mode, GPIO output value low */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			if (consys_get_adie_chipid_mt6983() == ADIE_6635) {
				CONSYS_REG_WRITE(GPIO_REG_BASE +
					CONSYS_GEN_GPIO_DIR6_SET_OFFSET_ADDR, 0x100000);
				CONSYS_REG_WRITE(GPIO_REG_BASE +
					CONSYS_GEN_GPIO_DOUT6_CLR_OFFSET_ADDR, 0x100000);
				CONSYS_REG_WRITE(GPIO_REG_BASE +
					CONSYS_GEN_GPIO_MODE26_CLR_OFFSET_ADDR, 0x70000);
			}
		#endif

		/* CONN_WF_CTRL2 swtich to GPIO mode, GPIO output value high */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			if (consys_get_adie_chipid_mt6983() == ADIE_6637) {
				CONSYS_REG_WRITE(GPIO_REG_BASE +
					CONSYS_GEN_GPIO_DIR6_SET_OFFSET_ADDR, 0x100000);
				CONSYS_REG_WRITE(GPIO_REG_BASE +
					CONSYS_GEN_GPIO_DOUT6_SET_OFFSET_ADDR, 0x100000);
				CONSYS_REG_WRITE(GPIO_REG_BASE +
					CONSYS_GEN_GPIO_MODE26_CLR_OFFSET_ADDR, 0x70000);
			}
		#endif
	}

	return 0;
}

int connsys_adie_top_ck_en_ctl_mt6983_gen(unsigned int enable)
{
	#ifndef CONFIG_FPGA_EARLY_PORTING
	int check = 0;
	#endif

	if (CONN_WT_SLP_CTL_REG_BASE == 0) {
		pr_err("CONN_WT_SLP_CTL_REG_BASE is not defined\n");
		return -1;
	}

	if (enable == 1) {
		/* Eaable dig_top_ck in Adie (Adress in Adie: 12'hA00) */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_SET_BIT(CONN_WT_SLP_CTL_REG_BASE +
				CONSYS_GEN_WB_SLP_TOP_CK_0_OFFSET_ADDR, (0x1 << 0));
		#endif

		/* polling enable A-die top_ck_en_0 */
		/* (polling "100 times" and each polling interval is "5 us") */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			check = 0;
			CONSYS_REG_BIT_POLLING(CONN_WT_SLP_CTL_REG_BASE +
				CONSYS_GEN_WB_SLP_TOP_CK_0_OFFSET_ADDR,
				1, 0, 100, 5, check);
			if (check != 0) {
				pr_err("polling enable A-die top_ck_en_0 fail, Status=0x%08x\n",
					CONSYS_REG_READ(CONN_WT_SLP_CTL_REG_BASE +
						CONSYS_GEN_WB_SLP_TOP_CK_0_OFFSET_ADDR));
				return check;
			}
		#endif
	} else {
		/* Disable dig_top_ck in Adie (Adress in Adie: 12'hA00) */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_CLR_BIT(CONN_WT_SLP_CTL_REG_BASE +
				CONSYS_GEN_WB_SLP_TOP_CK_0_OFFSET_ADDR, (0x1 << 0));
		#endif

		/* polling disable A-die top_ck_en_0 */
		/* (polling "100 times" and each polling interval is "5 us") */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			check = 0;
			CONSYS_REG_BIT_POLLING(CONN_WT_SLP_CTL_REG_BASE +
				CONSYS_GEN_WB_SLP_TOP_CK_0_OFFSET_ADDR,
				1, 0, 100, 5, check);
			if (check != 0) {
				pr_err("polling disable A-die top_ck_en_0 fail, Status=0x%08x\n",
					CONSYS_REG_READ(CONN_WT_SLP_CTL_REG_BASE +
						CONSYS_GEN_WB_SLP_TOP_CK_0_OFFSET_ADDR));
				return check;
			}
		#endif
	}

	return 0;
}

int connsys_a_die_cfg_adie6635_deassert_adie_reset_mt6983_gen(void)
{
	if (CONN_CFG_ON_BASE == 0) {
		pr_err("CONN_CFG_ON_BASE is not defined\n");
		return -1;
	}

	/* de-assert A-die reset */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_CFG_ON_BASE +
			CONSYS_GEN_ADIE_CTL_OFFSET_ADDR, (0x1 << 0));
	#endif

	return 0;
}

int connsys_a_die_cfg_adie6635_read_adie_id_mt6983_gen(
		unsigned int *padie_id,
		unsigned int *phw_ver_id)
{
	#ifndef CONFIG_FPGA_EARLY_PORTING
	unsigned int chip_id = 0;
	int check = 0;
	#endif

	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	/* read MT6635 ID */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		check = consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_CHIP_ID, &chip_id);
		if (check || (chip_id & 0xffff0000) != 0x66350000) {
			pr_err("[%s] get a-die fail, ret=%d, adie_id=0x%x\n", __func__, check, chip_id);
			return -1;
		}

		pr_info("[%s] A-die chip id: 0x%08x\n", __func__, chip_id);
		if (padie_id != NULL)
			*padie_id = chip_id;
		if (phw_ver_id != NULL)
			*phw_ver_id = (chip_id & 0xffff);
	#endif

	return 0;
}

int connsys_a_die_cfg_adie6635_PART1_mt6983_gen(void)
{
	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	if (CONN_RF_SPI_MST_REG_BASE == 0) {
		pr_err("CONN_RF_SPI_MST_REG_BASE is not defined\n");
		return -1;
	}

	if (CONN_THERM_CTL_BASE == 0) {
		pr_err("CONN_THERM_CTL_BASE is not defined\n");
		return -1;
	}

	/* Patch to FW from 7761(WF0_WRI_SX_CAL_MAP/WF1_WRI_SX_CAL_MAP) */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_WRI_CTR2, 0x7700);
	#endif

	/* set WF low power cmd as DBDC mode & legacy interface */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_SMCTK11, 0x21);
	#endif

	/* update spi fm read extra bit setting */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_REG_WRITE_MASK(CONN_RF_SPI_MST_REG_BASE +
			CONSYS_GEN_FM_CTRL_OFFSET_ADDR, 0x0, 0x80FF);
	#endif

	/* Update Thermal addr for 6635 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_REG_WRITE(CONN_THERM_CTL_BASE +
			CONSYS_GEN_THERM_AADDR_OFFSET_ADDR, 0x50305A00);
	#endif

	return 0;
}

int connsys_a_die_efuse_read_adie6635_check_efuse_valid_mt6983_gen(bool *pefuse_valid)
{
	#ifndef CONFIG_FPGA_EARLY_PORTING
	unsigned int efuse_ctrl = 0;
	unsigned int ret = 0;
	int retry = 0;
	bool efuse_valid = false;
	#endif

	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	/* Efuse control clear, clear Status /trigger */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_EFUSE_CTRL, &efuse_ctrl);
		efuse_ctrl &= ~(0x40000000);
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_EFUSE_CTRL, efuse_ctrl);
	#endif

	/* Efuse Read 1st 16byte */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_EFUSE_CTRL, &efuse_ctrl);
		efuse_ctrl &= ~(0x43ff00c0);
		efuse_ctrl |= (0x40000000 & 0x43ff00c0);
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_EFUSE_CTRL, efuse_ctrl);
	#endif

	/* Polling EFUSE busy = low */
	/* (each polling interval is "30us" and polling timeout is 2ms) */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		retry = 0;
		consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_EFUSE_CTRL, &ret);
		while ((ret & (0x1 << 30)) != 0 && retry < 70) {
			retry++;
			udelay(30);
			consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_EFUSE_CTRL, &ret);
		}

		if ((ret & (0x1 << 30)) != 0) {
			pr_err("[%s]Polling EFUSE busy = low, retry fail(%d)\n", __func__, retry);
		}
	#endif

	/* Check efuse_valid & return */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		efuse_valid = false;
		consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_EFUSE_CTRL, &efuse_ctrl);
		if (((efuse_ctrl & (0x1 << 29)) >> 29) == 1)
			efuse_valid = true;
		else
			pr_err("EFUSE is invalid\n");
		if (pefuse_valid != NULL)
			*pefuse_valid = efuse_valid;
	#endif

	return 0;
}

void connsys_a_die_efuse_read_adie6635_get_efuse_count_mt6983_gen(unsigned int *pefuse_count)
{
	if (pefuse_count != NULL)
		*pefuse_count = 4;
}

int connsys_a_die_efuse_read_adie6635_get_efuse0_info_mt6983_gen(
		bool efuse_valid,
		unsigned int *pefuse0)
{
	#ifndef CONFIG_FPGA_EARLY_PORTING
	int check = 0;
	unsigned int efuse_rdata0 = 0;
	#endif

	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	/* Read Efuse Data to global var */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		if (efuse_valid) {
			check = consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_EFUSE_RDATA0, &efuse_rdata0);
			if (check)
				return check;
			if (pefuse0 != NULL)
				*pefuse0 = efuse_rdata0;
		}
	#endif

	return 0;
}

int connsys_a_die_efuse_read_adie6635_get_efuse1_info_mt6983_gen(
		bool efuse_valid,
		unsigned int *pefuse1)
{
	#ifndef CONFIG_FPGA_EARLY_PORTING
	int check = 0;
	unsigned int efuse_rdata1 = 0;
	#endif

	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	/* Read Efuse Data to global var */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		if (efuse_valid) {
			check = consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_EFUSE_RDATA1, &efuse_rdata1);
			if (check)
				return check;
			if (pefuse1 != NULL)
				*pefuse1 = efuse_rdata1;
		}
	#endif

	return 0;
}

int connsys_a_die_efuse_read_adie6635_get_efuse2_info_mt6983_gen(
		bool efuse_valid,
		unsigned int *pefuse2)
{
	#ifndef CONFIG_FPGA_EARLY_PORTING
	int check = 0;
	unsigned int efuse_rdata2 = 0;
	#endif

	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	/* Read Efuse Data to global var */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		if (efuse_valid) {
			check = consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_EFUSE_RDATA2, &efuse_rdata2);
			if (check)
				return check;
			if (pefuse2 != NULL)
				*pefuse2 = efuse_rdata2;
		}
	#endif

	return 0;
}

int connsys_a_die_efuse_read_adie6635_get_efuse3_info_mt6983_gen(
		bool efuse_valid,
		unsigned int *pefuse3)
{
	#ifndef CONFIG_FPGA_EARLY_PORTING
	int check = 0;
	unsigned int efuse_rdata3 = 0;
	#endif

	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	/* Read Efuse Data to global var */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		if (efuse_valid) {
			check = consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_EFUSE_RDATA3, &efuse_rdata3);
			if (check)
				return check;
			if (pefuse3 != NULL)
				*pefuse3 = efuse_rdata3;
		}
	#endif

	return 0;
}

int connsys_a_die_thermal_cal_adie6635_conf_mt6983_gen(
		bool efuse_valid,
		unsigned int *pefuse_list,
		unsigned int efuse_size,
		int *pslop_molecule,
		int *pthermal_b,
		int *poffset)
{
	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	/* replace CR default value by Efuse Value */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		if ((efuse_valid) && ((pefuse_list != NULL) && (efuse_size > 1) && (pefuse_list[1] & (0x1 << 7)))) {
			consys_spi_write_offset_range_nolock_mt6983(
				SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_THADC_BG, pefuse_list[1], 12, 3, 4);
			consys_spi_write_offset_range_nolock_mt6983(
				SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_THADC, pefuse_list[1], 23, 0, 3);
		}
	#endif

	/* replace CR default value by Efuse Value */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		if ((efuse_valid) && ((pefuse_list != NULL) && (efuse_size > 1) && (pefuse_list[1] & (0x1 << 15)))) {
			consys_spi_write_offset_range_nolock_mt6983(
				SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_THADC, pefuse_list[1], 26, 13, 2);
		}
	#endif

	/* efuse_mid_data = EFUSE_RDATA1[12:8] */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		if ((efuse_valid) && ((pefuse_list != NULL) && (efuse_size > 1) && (pefuse_list[1] & (0x1 << 15)))) {
			if (pslop_molecule != NULL)
				*pslop_molecule = (pefuse_list[1] & 0x1f00) >> 8;
		}
	#endif

	/* efuse_mid_data = EFUSE_RDATA1[22:16] */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		if ((efuse_valid) && ((pefuse_list != NULL) && (efuse_size > 1) && (pefuse_list[1] & (0x1 << 23)))) {
			if (pthermal_b != NULL)
				*pthermal_b = (pefuse_list[1] & 0x7f0000) >> 16;
		}
	#endif

	/* efuse_mid_data = EFUSE_RDATA1[30:24] */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		if ((efuse_valid) && ((pefuse_list != NULL) && (efuse_size > 1) && (pefuse_list[1] & (0x1 << 31)))) {
			if (poffset != NULL)
				*poffset = (pefuse_list[1] & 0x7f000000) >> 24;
		}
	#endif

	return 0;
}

int connsys_a_die_cfg_adie6635_PART2_mt6983_gen(unsigned int hw_ver_id)
{
	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	/* set WF_PAD to HighZ */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_ENCAL_WBTAC_IF_SW, 0x80000000);
	#endif

	/* disable CAL LDO */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_WF0_TOP_01, 0xE8002);
	#endif

	/* disable CAL LDO */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_WF1_TOP_01, 0xE8002);
	#endif

	/* increase XOBUF supply-V */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_XTAL_01, 0xF6E8FFF5);
	#endif

	/* increase XOBUF supply-R for MT6635 E1 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		if (hw_ver_id == 0x8a00) {
			consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_XTAL_02, 0xD5555FFF);
		} else {
			consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_XTAL_02, 0x55555FFF);
		}
	#endif

	/* initial IR value for WF0 THADC */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_WF0_BG, 0x2008);
	#endif

	/* initial IR value for WF1 THADC */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_WF1_BG, 0x2008);
	#endif

	return 0;
}

int connsys_a_die_cfg_adie6637_deassert_adie_reset_mt6983_gen(void)
{
	if (CONN_CFG_ON_BASE == 0) {
		pr_err("CONN_CFG_ON_BASE is not defined\n");
		return -1;
	}

	/* de-assert A-die reset */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_CFG_ON_BASE +
			CONSYS_GEN_ADIE_CTL_OFFSET_ADDR, (0x1 << 0));
	#endif

	return 0;
}

int connsys_a_die_cfg_adie6637_read_adie_id_mt6983_gen(
		unsigned int *padie_id,
		unsigned int *phw_ver_id)
{
	#ifndef CONFIG_FPGA_EARLY_PORTING
	unsigned int chip_id = 0;
	int check = 0;
	#endif

	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	/* read MT6637 ID */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		check = consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_CHIP_ID, &chip_id);
		if (check || (chip_id & 0xffff0000) != 0x66370000) {
			pr_err("[%s] get a-die fail, ret=%d, adie_id=0x%x\n", __func__, check, chip_id);
			return -1;
		}

		pr_info("[%s] A-die chip id: 0x%08x\n", __func__, chip_id);
		if (padie_id != NULL)
			*padie_id = chip_id;
		if (phw_ver_id != NULL)
			*phw_ver_id = (chip_id & 0xffff);
	#endif

	return 0;
}

int connsys_a_die_cfg_adie6637_PART1_mt6983_gen(void)
{
	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	if (CONN_RF_SPI_MST_REG_BASE == 0) {
		pr_err("CONN_RF_SPI_MST_REG_BASE is not defined\n");
		return -1;
	}

	if (CONN_THERM_CTL_BASE == 0) {
		pr_err("CONN_THERM_CTL_BASE is not defined\n");
		return -1;
	}

	/* Patch to FW from 7761(WF0_WRI_SX_CAL_MAP/WF1_WRI_SX_CAL_MAP) */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_WRI_CTR2, 0x7700);
	#endif

	/* set WF low power cmd as DBDC mode & legacy interface */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_SMCTK11, 0x21);
	#endif

	/* update spi fm read extra bit setting */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_REG_WRITE_MASK(CONN_RF_SPI_MST_REG_BASE +
			CONSYS_GEN_FM_CTRL_OFFSET_ADDR, 0x0, 0x80FF);
	#endif

	/* Update Thermal addr for 6637 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_REG_WRITE(CONN_THERM_CTL_BASE +
			CONSYS_GEN_THERM_AADDR_OFFSET_ADDR, 0x50305A00);
	#endif

	return 0;
}

int connsys_a_die_efuse_read_adie6637_check_efuse_valid_mt6983_gen(bool *pefuse_valid)
{
	#ifndef CONFIG_FPGA_EARLY_PORTING
	unsigned int efuse_ctrl = 0;
	unsigned int ret = 0;
	int retry = 0;
	bool efuse_valid = false;
	#endif

	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	/* Efuse control clear, clear Status /trigger */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_EFUSE_CTRL, &efuse_ctrl);
		efuse_ctrl &= ~(0x40000000);
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_EFUSE_CTRL, efuse_ctrl);
	#endif

	/* Efuse Read 1st 16byte */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_EFUSE_CTRL, &efuse_ctrl);
		efuse_ctrl &= ~(0x43ff00c0);
		efuse_ctrl |= (0x40000000 & 0x43ff00c0);
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_EFUSE_CTRL, efuse_ctrl);
	#endif

	/* Polling EFUSE busy = low */
	/* (each polling interval is "30us" and polling timeout is 2ms) */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		retry = 0;
		consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_EFUSE_CTRL, &ret);
		while ((ret & (0x1 << 30)) != 0 && retry < 70) {
			retry++;
			udelay(30);
			consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_EFUSE_CTRL, &ret);
		}

		if ((ret & (0x1 << 30)) != 0) {
			pr_err("[%s]Polling EFUSE busy = low, retry fail(%d)\n", __func__, retry);
		}
	#endif

	/* Check efuse_valid & return */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		efuse_valid = false;
		consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_EFUSE_CTRL, &efuse_ctrl);
		if (((efuse_ctrl & (0x1 << 29)) >> 29) == 1)
			efuse_valid = true;
		else
			pr_err("EFUSE is invalid\n");
		if (pefuse_valid != NULL)
			*pefuse_valid = efuse_valid;
	#endif

	return 0;
}

void connsys_a_die_efuse_read_adie6637_get_efuse_count_mt6983_gen(unsigned int *pefuse_count)
{
	if (pefuse_count != NULL)
		*pefuse_count = 4;
}

int connsys_a_die_efuse_read_adie6637_get_efuse0_info_mt6983_gen(
		bool efuse_valid,
		unsigned int *pefuse0)
{
	#ifndef CONFIG_FPGA_EARLY_PORTING
	int check = 0;
	unsigned int efuse_rdata0 = 0;
	#endif

	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	/* Read Efuse Data to global var */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		if (efuse_valid) {
			check = consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_EFUSE_RDATA0, &efuse_rdata0);
			if (check)
				return check;
			if (pefuse0 != NULL)
				*pefuse0 = efuse_rdata0;
		}
	#endif

	return 0;
}

int connsys_a_die_efuse_read_adie6637_get_efuse1_info_mt6983_gen(
		bool efuse_valid,
		unsigned int *pefuse1)
{
	#ifndef CONFIG_FPGA_EARLY_PORTING
	int check = 0;
	unsigned int efuse_rdata1 = 0;
	#endif

	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	/* Read Efuse Data to global var */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		if (efuse_valid) {
			check = consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_EFUSE_RDATA1, &efuse_rdata1);
			if (check)
				return check;
			if (pefuse1 != NULL)
				*pefuse1 = efuse_rdata1;
		}
	#endif

	return 0;
}

int connsys_a_die_efuse_read_adie6637_get_efuse2_info_mt6983_gen(
		bool efuse_valid,
		unsigned int *pefuse2)
{
	#ifndef CONFIG_FPGA_EARLY_PORTING
	int check = 0;
	unsigned int efuse_rdata2 = 0;
	#endif

	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	/* Read Efuse Data to global var */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		if (efuse_valid) {
			check = consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_EFUSE_RDATA2, &efuse_rdata2);
			if (check)
				return check;
			if (pefuse2 != NULL)
				*pefuse2 = efuse_rdata2;
		}
	#endif

	return 0;
}

int connsys_a_die_efuse_read_adie6637_get_efuse3_info_mt6983_gen(
		bool efuse_valid,
		unsigned int *pefuse3)
{
	#ifndef CONFIG_FPGA_EARLY_PORTING
	int check = 0;
	unsigned int efuse_rdata3 = 0;
	#endif

	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	/* Read Efuse Data to global var */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		if (efuse_valid) {
			check = consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_EFUSE_RDATA3, &efuse_rdata3);
			if (check)
				return check;
			if (pefuse3 != NULL)
				*pefuse3 = efuse_rdata3;
		}
	#endif

	return 0;
}

int connsys_a_die_thermal_cal_adie6637_conf_mt6983_gen(
		bool efuse_valid,
		unsigned int *pefuse_list,
		unsigned int efuse_size,
		int *pslop_molecule,
		int *pthermal_b,
		int *poffset)
{
	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	/* replace CR default value by Efuse Value */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		if ((efuse_valid) && ((pefuse_list != NULL) && (efuse_size > 1) && (pefuse_list[1] & (0x1 << 7)))) {
			consys_spi_write_offset_range_nolock_mt6983(
				SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_TOP_THADC_BG, pefuse_list[1], 12, 3, 4);
			consys_spi_write_offset_range_nolock_mt6983(
				SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_TOP_THADC, pefuse_list[1], 23, 0, 3);
		}
	#endif

	/* replace CR default value by Efuse Value */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		if ((efuse_valid) && ((pefuse_list != NULL) && (efuse_size > 1) && (pefuse_list[1] & (0x1 << 15)))) {
			consys_spi_write_offset_range_nolock_mt6983(
				SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_TOP_THADC, pefuse_list[1], 26, 13, 2);
		}
	#endif

	/* efuse_mid_data = EFUSE_RDATA1[12:8] */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		if ((efuse_valid) && ((pefuse_list != NULL) && (efuse_size > 1) && (pefuse_list[1] & (0x1 << 15)))) {
			if (pslop_molecule != NULL)
				*pslop_molecule = (pefuse_list[1] & 0x1f00) >> 8;
		}
	#endif

	/* efuse_mid_data = EFUSE_RDATA1[22:16] */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		if ((efuse_valid) && ((pefuse_list != NULL) && (efuse_size > 1) && (pefuse_list[1] & (0x1 << 23)))) {
			if (pthermal_b != NULL)
				*pthermal_b = (pefuse_list[1] & 0x7f0000) >> 16;
		}
	#endif

	/* efuse_mid_data = EFUSE_RDATA1[30:24] */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		if ((efuse_valid) && ((pefuse_list != NULL) && (efuse_size > 1) && (pefuse_list[1] & (0x1 << 31)))) {
			if (poffset != NULL)
				*poffset = (pefuse_list[1] & 0x7f000000) >> 24;
		}
	#endif

	return 0;
}

int connsys_a_die_cfg_adie6637_PART2_mt6983_gen(unsigned int hw_ver_id)
{
	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	/* disable CAL LDO */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_WF2_POS_01, 0xE8002);
	#endif

	/* disable CAL LDO */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_WF2_POS_02, 0xE8002);
	#endif

	/* initial IR value for WF0 THADC */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_WF2_TIME_COUNT_01, 0x2008);
	#endif

	/* initial IR value for WF1 THADC */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_WF2_TIME_COUNT_02, 0x2008);
	#endif

	/* DA_WF0_SW_RFDIGLDO Wakeup Sleep Sequence Update */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_WF1_RFLDO_TIME, 0xF000B);
	#endif

	/* DA_WF1_SW_RFDIGLDO Wakeup Sleep Sequence Update */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_WF1_RFDIG_OFF_TIME, 0xC000C);
	#endif

	/* set DA_BT0_BG_EN_RFDIG On/Off time counter */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_BT0_BG_TIME, 0x20003);
	#endif

	/* set bt_iso_en time counter */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_BT0_ISO_TIME, 0x1000B);
	#endif

	/* set bt_xobuf_time counter */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_BT0_XOBUF_TIME, 0x10004);
	#endif

	/* set bt_ck_en time counter */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_BT0_CKEN_TIME, 0x20003);
	#endif

	/* set BT_WAKEUPSLEEP_PON_OFF counter Threshold to 8us */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_WAKEUPSLEEP_PON_OFF, 0x150008);
	#endif

	/* Update WF XOBUF disable, WF sys will enable XOBUF when WF Power On */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_TOP_XO_02, 0x8000000);
	#endif

	/* Update WF XOBUF disable, WF sys will enable XOBUF when WF Power On */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_TOP_XO_03, 0x0);
	#endif

	/* Update BT/FM/GPS XOBUF disable, this will use drvier to config in BGF platform */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_TOP_XO_07, 0x0);
	#endif

	/* Update BT AIQ SW to normal mode */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_ENCAL_WFBT_IF_SW_01, 0x5);
	#endif

	/* Update to always Power On FMSYS in ADIE */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_FMCTL4, 0x35);
	#endif

	/* BT/TOP SPI CK PU/PD no pull after hw POS */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_TOP_PULL, 0xA6AAAA44);
	#endif

	if (hw_ver_id == 0x8a01) {
		/* Update CR of VCONST_BG WF0 Only For E2 Update */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_WF0_BG, 0xE008);
		#endif

		/* Update CR of VCONST_BG WF1 Only For E2 Update */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_WF1_BG, 0xE008);
		#endif
	}

	return 0;
}

int connsys_a_die_cfg_deassert_adie_reset_mt6983_gen(void)
{
	if (consys_get_adie_chipid_mt6983() == ADIE_6635)
		connsys_a_die_cfg_adie6635_deassert_adie_reset_mt6983_gen();
	else if (consys_get_adie_chipid_mt6983() == ADIE_6637)
		connsys_a_die_cfg_adie6637_deassert_adie_reset_mt6983_gen();
	else
		return -1;

	return 0;
}

int connsys_a_die_cfg_read_adie_id_mt6983_gen(unsigned int *padie_id, unsigned int *phw_ver_id)
{
	int check = 0;

	if (consys_get_adie_chipid_mt6983() == ADIE_6635)
		check = connsys_a_die_cfg_adie6635_read_adie_id_mt6983_gen(padie_id, phw_ver_id);
	else if (consys_get_adie_chipid_mt6983() == ADIE_6637)
		check = connsys_a_die_cfg_adie6637_read_adie_id_mt6983_gen(padie_id, phw_ver_id);
	else
		return -1;

	if (check)
		return -1;

	return 0;
}

int connsys_a_die_efuse_read_get_efuse_info_mt6983_gen(
		void __iomem **psysram_efuse_list,
		int *pslop_molecule,
		int *pthermal_b,
		int *poffset)
{
	bool efuse_valid = false;
	unsigned int efuse_size = 0;
	unsigned int sysram_efuse_size = 0;
	unsigned int efuse_list[16] = { 0 };
	int ret[16] = { 0 };
	int i = 0;

	if (consys_get_adie_chipid_mt6983() == ADIE_6635) {
		connsys_a_die_cfg_adie6635_PART1_mt6983_gen();
		connsys_a_die_efuse_read_adie6635_check_efuse_valid_mt6983_gen(&efuse_valid);
		connsys_a_die_efuse_read_adie6635_get_efuse_count_mt6983_gen(&efuse_size);

		for (i = 0; i < 16; i++) {
			if (psysram_efuse_list[i] == 0) {
				sysram_efuse_size = i;
				break;
			}
		}

		if (sysram_efuse_size != 4 || efuse_valid == false)
			return -1;

		ret[0] = connsys_a_die_efuse_read_adie6635_get_efuse0_info_mt6983_gen(efuse_valid, &(efuse_list[0]));
		CONSYS_REG_WRITE(psysram_efuse_list[0], efuse_list[0]);

		ret[1] = connsys_a_die_efuse_read_adie6635_get_efuse1_info_mt6983_gen(efuse_valid, &(efuse_list[1]));
		CONSYS_REG_WRITE(psysram_efuse_list[1], efuse_list[1]);

		ret[2] = connsys_a_die_efuse_read_adie6635_get_efuse2_info_mt6983_gen(efuse_valid, &(efuse_list[2]));
		CONSYS_REG_WRITE(psysram_efuse_list[2], efuse_list[2]);

		ret[3] = connsys_a_die_efuse_read_adie6635_get_efuse3_info_mt6983_gen(efuse_valid, &(efuse_list[3]));
		CONSYS_REG_WRITE(psysram_efuse_list[3], efuse_list[3]);

		pr_info("efuse = [0x%08x, 0x%08x, 0x%08x, 0x%08x]", efuse_list[0], efuse_list[1], efuse_list[2], efuse_list[3]);
		if (ret[0] || ret[1] || ret[2] || ret[3])
			pr_err("efuse read error: [%d, %d, %d, %d]", ret[0], ret[1], ret[2], ret[3]);

		connsys_a_die_thermal_cal_adie6635_conf_mt6983_gen(
			efuse_valid, efuse_list, efuse_size, pslop_molecule, pthermal_b, poffset);
	} else if (consys_get_adie_chipid_mt6983() == ADIE_6637) {
		connsys_a_die_cfg_adie6637_PART1_mt6983_gen();
		connsys_a_die_efuse_read_adie6637_check_efuse_valid_mt6983_gen(&efuse_valid);
		connsys_a_die_efuse_read_adie6637_get_efuse_count_mt6983_gen(&efuse_size);

		for (i = 0; i < 16; i++) {
			if (psysram_efuse_list[i] == 0) {
				sysram_efuse_size = i;
				break;
			}
		}

		if (sysram_efuse_size != 4 || efuse_valid == false)
			return -1;

		ret[0] = connsys_a_die_efuse_read_adie6637_get_efuse0_info_mt6983_gen(efuse_valid, &(efuse_list[0]));
		CONSYS_REG_WRITE(psysram_efuse_list[0], efuse_list[0]);

		ret[1] = connsys_a_die_efuse_read_adie6637_get_efuse1_info_mt6983_gen(efuse_valid, &(efuse_list[1]));
		CONSYS_REG_WRITE(psysram_efuse_list[1], efuse_list[1]);

		ret[2] = connsys_a_die_efuse_read_adie6637_get_efuse2_info_mt6983_gen(efuse_valid, &(efuse_list[2]));
		CONSYS_REG_WRITE(psysram_efuse_list[2], efuse_list[2]);

		ret[3] = connsys_a_die_efuse_read_adie6637_get_efuse3_info_mt6983_gen(efuse_valid, &(efuse_list[3]));
		CONSYS_REG_WRITE(psysram_efuse_list[3], efuse_list[3]);

		pr_info("efuse = [0x%08x, 0x%08x, 0x%08x, 0x%08x]", efuse_list[0], efuse_list[1], efuse_list[2], efuse_list[3]);
		if (ret[0] || ret[1] || ret[2] || ret[3])
			pr_err("efuse read error: [%d, %d, %d, %d]", ret[0], ret[1], ret[2], ret[3]);

		connsys_a_die_thermal_cal_adie6637_conf_mt6983_gen(
			efuse_valid, efuse_list, efuse_size, pslop_molecule, pthermal_b, poffset);
	} else
		return -1;

	return 0;
}

int connsys_a_die_cfg_PART2_mt6983_gen(unsigned int hw_ver_id)
{
	if (consys_get_adie_chipid_mt6983() == ADIE_6635)
		connsys_a_die_cfg_adie6635_PART2_mt6983_gen(hw_ver_id);
	else if (consys_get_adie_chipid_mt6983() == ADIE_6637)
		connsys_a_die_cfg_adie6637_PART2_mt6983_gen(hw_ver_id);
	else
		return -1;

	return 0;
}

int connsys_a_die_switch_to_conn_mode_mt6983_gen(void)
{
	if (GPIO_REG_BASE == 0) {
		pr_err("GPIO_REG_BASE is not defined\n");
		return -1;
	}

	/* CONN_WF_CTRL2 swtich to CONN mode (PAD change with CONN_TOP_DATA) */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_REG_WRITE(GPIO_REG_BASE +
			CONSYS_GEN_GPIO_MODE26_SET_OFFSET_ADDR, 0x10000);
		CONSYS_REG_WRITE(GPIO_REG_BASE +
			CONSYS_GEN_GPIO_DIR6_CLR_OFFSET_ADDR, 0x100000);
	#endif

	return 0;
}

void connsys_wt_slp_top_power_saving_ctrl_adie6635_wf_fm_gps_mt6983_gen(void)
{
	if (CONN_WT_SLP_CTL_REG_BASE == 0) {
		pr_err("CONN_WT_SLP_CTL_REG_BASE is not defined\n");
		return;
	}

	/* set wt_slp CR for A-die power saving  (ref. A-die power control) */
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_SLP_CTL_OFFSET_ADDR, 0x8, 0x1F);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR1_OFFSET_ADDR, 0xA03C);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR2_OFFSET_ADDR, 0xA03C);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR3_OFFSET_ADDR, 0xAA18);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR4_OFFSET_ADDR, 0xAA18);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR5_OFFSET_ADDR, 0xA0C8);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR6_OFFSET_ADDR, 0xAA00);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR7_OFFSET_ADDR, 0xA0B4);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR8_OFFSET_ADDR, 0xA34C);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON1_OFFSET_ADDR, 0x0);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON2_OFFSET_ADDR, 0x0);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON3_OFFSET_ADDR, 0x74E0FFF5);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON4_OFFSET_ADDR, 0x76E8FFF5);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON5_OFFSET_ADDR, 0x0);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON6_OFFSET_ADDR, 0xFFFFFFFF);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON7_OFFSET_ADDR, 0x19);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON8_OFFSET_ADDR, 0x10400);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF1_OFFSET_ADDR, 0x57400000);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF2_OFFSET_ADDR, 0x57400000);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF3_OFFSET_ADDR, 0x44E0FFF5);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF4_OFFSET_ADDR, 0x44E0FFF5);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF5_OFFSET_ADDR, 0x1);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF6_OFFSET_ADDR, 0x0);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF7_OFFSET_ADDR, 0x40019);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF8_OFFSET_ADDR, 0x410440);
}

void connsys_wt_slp_top_power_saving_ctrl_adie6635_bt_only_mt6983_gen(void)
{
	if (CONN_WT_SLP_CTL_REG_BASE == 0) {
		pr_err("CONN_WT_SLP_CTL_REG_BASE is not defined\n");
		return;
	}

	/* set wt_slp CR for A-die power saving  (ref. A-die power control) */
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_SLP_CTL_OFFSET_ADDR, 0x8, 0x1F);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR1_OFFSET_ADDR, 0xA03C);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR2_OFFSET_ADDR, 0xA03C);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR3_OFFSET_ADDR, 0xAA18);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR4_OFFSET_ADDR, 0xAA18);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR5_OFFSET_ADDR, 0xA0C8);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR6_OFFSET_ADDR, 0xAA00);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR7_OFFSET_ADDR, 0xA0B4);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR8_OFFSET_ADDR, 0xA34C);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON1_OFFSET_ADDR, 0x0);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON2_OFFSET_ADDR, 0x0);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON3_OFFSET_ADDR, 0x74E03F75);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON4_OFFSET_ADDR, 0x76E83F75);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON5_OFFSET_ADDR, 0x0);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON6_OFFSET_ADDR, 0xFFFFFFFF);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON7_OFFSET_ADDR, 0x19);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON8_OFFSET_ADDR, 0x10400);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF1_OFFSET_ADDR, 0x57400000);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF2_OFFSET_ADDR, 0x57400000);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF3_OFFSET_ADDR, 0x44E03F75);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF4_OFFSET_ADDR, 0x44E03F75);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF5_OFFSET_ADDR, 0x1);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF6_OFFSET_ADDR, 0x0);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF7_OFFSET_ADDR, 0x40019);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF8_OFFSET_ADDR, 0x410440);
}

void connsys_wt_slp_top_power_saving_ctrl_adie6637_sleep_mode_1_mt6983_gen(void)
{
	if (CONN_WT_SLP_CTL_REG_BASE == 0) {
		pr_err("CONN_WT_SLP_CTL_REG_BASE is not defined\n");
		return;
	}

	/* set wt_slp CR for A-die power saving  (ref. A-die power control) */
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_SLP_CTL_OFFSET_ADDR, 0x6, 0x1F);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR1_OFFSET_ADDR, 0xA03C);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR2_OFFSET_ADDR, 0xA03C);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR3_OFFSET_ADDR, 0xAB00);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR4_OFFSET_ADDR, 0xAB00);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR5_OFFSET_ADDR, 0xAB00);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR6_OFFSET_ADDR, 0xA0C8);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON1_OFFSET_ADDR, 0x0);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON2_OFFSET_ADDR, 0x0);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON3_OFFSET_ADDR, 0xC0000000);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON4_OFFSET_ADDR, 0xF8000000);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON5_OFFSET_ADDR, 0xFC000000);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON6_OFFSET_ADDR, 0x0);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF1_OFFSET_ADDR, 0x57400000);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF2_OFFSET_ADDR, 0x57400000);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF3_OFFSET_ADDR, 0x0);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF4_OFFSET_ADDR, 0x0);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF5_OFFSET_ADDR, 0xC4000000);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF6_OFFSET_ADDR, 0x1);
}

void connsys_wt_slp_top_power_saving_ctrl_adie6637_sleep_mode_2_mt6983_gen(void)
{
	if (CONN_WT_SLP_CTL_REG_BASE == 0) {
		pr_err("CONN_WT_SLP_CTL_REG_BASE is not defined\n");
		return;
	}

	/* set wt_slp CR for A-die power saving  (ref. A-die power control) */
	CONSYS_REG_WRITE_MASK(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_SLP_CTL_OFFSET_ADDR, 0x6, 0x1F);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR1_OFFSET_ADDR, 0xA03C);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR2_OFFSET_ADDR, 0xA03C);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR3_OFFSET_ADDR, 0xAB00);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR4_OFFSET_ADDR, 0xAB00);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR5_OFFSET_ADDR, 0xAB00);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ADDR6_OFFSET_ADDR, 0xA0C8);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON1_OFFSET_ADDR, 0x0);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON2_OFFSET_ADDR, 0x0);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON3_OFFSET_ADDR, 0xC0000000);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON4_OFFSET_ADDR, 0xF8000000);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON5_OFFSET_ADDR, 0xFC000000);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_ON6_OFFSET_ADDR, 0x0);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF1_OFFSET_ADDR, 0x57400037);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF2_OFFSET_ADDR, 0x57400037);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF3_OFFSET_ADDR, 0x0);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF4_OFFSET_ADDR, 0x0);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF5_OFFSET_ADDR, 0xC4000000);
	CONSYS_REG_WRITE(CONN_WT_SLP_CTL_REG_BASE +
		CONSYS_GEN_WB_BG_OFF6_OFFSET_ADDR, 0x1);
}

void connsys_wt_slp_top_power_saving_ctrl_adie6637_mt6983_gen(
		unsigned int hw_version,
		unsigned int sleep_mode)
{
	if (sleep_mode == 1)
		connsys_wt_slp_top_power_saving_ctrl_adie6637_sleep_mode_1_mt6983_gen();
	else if (sleep_mode == 2)
		connsys_wt_slp_top_power_saving_ctrl_adie6637_sleep_mode_2_mt6983_gen();
	else {
		if (hw_version == 0x66378A00)
			connsys_wt_slp_top_power_saving_ctrl_adie6637_sleep_mode_1_mt6983_gen();
		else
			connsys_wt_slp_top_power_saving_ctrl_adie6637_sleep_mode_2_mt6983_gen();
	}
}

int connsys_afe_wbg_cal_mt6983_gen(
		unsigned int spi_semaphore_index,
		unsigned int spi_semaphore_timeout_usec)
{
	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	if (CONN_AFE_CTL_BASE == 0) {
		pr_err("CONN_AFE_CTL_BASE is not defined\n");
		return -1;
	}

	if (consys_get_adie_chipid_mt6983() == ADIE_6635) {
		/* set WF_PAD to HighZ */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			/* Get semaphore before read */
			if (consys_sema_acquire_timeout_mt6983(spi_semaphore_index, spi_semaphore_timeout_usec) == CONN_SEMA_GET_FAIL) {
				pr_err("[SPI WRITE] Require semaphore fail\n");
				return CONNINFRA_SPI_OP_FAIL;
			}

			consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_ENCAL_WBTAC_IF_SW, 0x80000000);

			consys_sema_release_mt6983(spi_semaphore_index);
		#endif
	} else if (consys_get_adie_chipid_mt6983() == ADIE_6637) {
		/* set WF_PAD to HighZ */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			/* Get semaphore before read */
			if (consys_sema_acquire_timeout_mt6983(spi_semaphore_index, spi_semaphore_timeout_usec) == CONN_SEMA_GET_FAIL) {
				pr_err("[SPI WRITE] Require semaphore fail\n");
				return CONNINFRA_SPI_OP_FAIL;
			}

			consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_ENCAL_WBTAC_IF_SW, 0x80000000);

			consys_sema_release_mt6983(spi_semaphore_index);
		#endif
	}

	/* AFE WBG RC calibration, set "AFE RG_WBG_EN_RCK" = 1 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_AFE_CTL_BASE +
			CONSYS_GEN_RG_DIG_EN_01_OFFSET_ADDR, (0x1 << 0));
	#endif

	udelay(60);

	/* AFE WBG RC calibration, set "AFE RG_WBG_EN_RCK" = 0 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_CLR_BIT(CONN_AFE_CTL_BASE +
			CONSYS_GEN_RG_DIG_EN_01_OFFSET_ADDR, (0x1 << 0));
	#endif

	/* AFE WBG TX calibration, set "AFE RG_WBG_EN_BPLL_UP" = 1 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_AFE_CTL_BASE +
			CONSYS_GEN_RG_DIG_EN_03_OFFSET_ADDR, (0x1 << 21));
	#endif

	udelay(30);

	/* AFE WBG TX calibration, set "AFE RG_WBG_EN_WPLL_UP" = 1 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_AFE_CTL_BASE +
			CONSYS_GEN_RG_DIG_EN_03_OFFSET_ADDR, (0x1 << 20));
	#endif

	udelay(60);

	/* AFE WBG TX calibration, set "AFE RG_WBG_EN_TXCAL_BT" = 1 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_AFE_CTL_BASE +
			CONSYS_GEN_RG_DIG_EN_01_OFFSET_ADDR, (0x1 << 21));
	#endif

	/* AFE WBG TX calibration, set "AFE RG_WBG_EN_TXCAL_WF0" = 1 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_AFE_CTL_BASE +
			CONSYS_GEN_RG_DIG_EN_01_OFFSET_ADDR, (0x1 << 20));
	#endif

	/* AFE WBG TX calibration, set "AFE RG_WBG_EN_TXCAL_WF1" = 1 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_AFE_CTL_BASE +
			CONSYS_GEN_RG_DIG_EN_01_OFFSET_ADDR, (0x1 << 19));
	#endif

	udelay(800);

	/* AFE WBG TX calibration, set "AFE RG_WBG_EN_TXCAL_BT" = 0 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_CLR_BIT(CONN_AFE_CTL_BASE +
			CONSYS_GEN_RG_DIG_EN_01_OFFSET_ADDR, (0x1 << 21));
	#endif

	/* AFE WBG TX calibration, set "AFE RG_WBG_EN_TXCAL_WF0" = 0 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_CLR_BIT(CONN_AFE_CTL_BASE +
			CONSYS_GEN_RG_DIG_EN_01_OFFSET_ADDR, (0x1 << 20));
	#endif

	/* AFE WBG TX calibration, set "AFE RG_WBG_EN_TXCAL_WF1" = 0 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_CLR_BIT(CONN_AFE_CTL_BASE +
			CONSYS_GEN_RG_DIG_EN_01_OFFSET_ADDR, (0x1 << 19));
	#endif

	/* AFE WBG TX calibration, set "AFE RG_WBG_EN_BPLL_UP" = 0 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_CLR_BIT(CONN_AFE_CTL_BASE +
			CONSYS_GEN_RG_DIG_EN_03_OFFSET_ADDR, (0x1 << 21));
	#endif

	/* AFE WBG TX calibration, set "AFE RG_WBG_EN_WPLL_UP" = 0 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_CLR_BIT(CONN_AFE_CTL_BASE +
			CONSYS_GEN_RG_DIG_EN_03_OFFSET_ADDR, (0x1 << 20));
	#endif

	if (consys_get_adie_chipid_mt6983() == ADIE_6635) {
		/* restore CR initial value */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			/* Get semaphore before read */
			if (consys_sema_acquire_timeout_mt6983(spi_semaphore_index, spi_semaphore_timeout_usec) == CONN_SEMA_GET_FAIL) {
				pr_err("[SPI WRITE] Require semaphore fail\n");
				return CONNINFRA_SPI_OP_FAIL;
			}

			consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_ENCAL_WBTAC_IF_SW, 0x5);

			consys_sema_release_mt6983(spi_semaphore_index);
		#endif
	} else if (consys_get_adie_chipid_mt6983() == ADIE_6637) {
		/* restore CR initial value */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			/* Get semaphore before read */
			if (consys_sema_acquire_timeout_mt6983(spi_semaphore_index, spi_semaphore_timeout_usec) == CONN_SEMA_GET_FAIL) {
				pr_err("[SPI WRITE] Require semaphore fail\n");
				return CONNINFRA_SPI_OP_FAIL;
			}

			consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6637_ATOP_RG_ENCAL_WBTAC_IF_SW, 0x5);

			consys_sema_release_mt6983(spi_semaphore_index);
		#endif
	}

	return 0;
}

int connsys_subsys_pll_initial_xtal_26000k_mt6983_gen(void)
{
	if (CONN_AFE_CTL_BASE == 0) {
		pr_err("CONN_AFE_CTL_BASE is not defined\n");
		return -1;
	}

	/* CASE SYS_XTAL_26000K */
	CONSYS_REG_WRITE_MASK(CONN_AFE_CTL_BASE +
		CONSYS_GEN_RG_PLL_STB_TIME_OFFSET_ADDR, 0x3140521, 0x7FFF7FFF);
	CONSYS_REG_WRITE_MASK(CONN_AFE_CTL_BASE +
		CONSYS_GEN_RG_DIG_EN_02_OFFSET_ADDR, 0x30047, 0x300CF);
	CONSYS_REG_WRITE_MASK(CONN_AFE_CTL_BASE +
		CONSYS_GEN_RG_DIG_TOP_01_OFFSET_ADDR, 0x68000, 0x78000);

	return 0;
}

int connsys_adie_clock_buffer_setting_mt6983_gen(
		unsigned int curr_status,
		unsigned int next_status,
		unsigned int hw_version,
		unsigned int spi_semaphore_index,
		unsigned int spi_semaphore_timeout_usec)
{
	#ifndef CONFIG_FPGA_EARLY_PORTING
	bool bt_only = false;
	unsigned int curr_bt = 0;
	unsigned int curr_fm = 0;
	unsigned int curr_gps = 0;
	unsigned int curr_wifi = 0;
	unsigned int next_bt = 0;
	unsigned int next_fm = 0;
	unsigned int next_gps = 0;
	unsigned int next_wifi = 0;
	unsigned int bt_on = -1;
	unsigned int fm_on = -1;
	unsigned int gps_on = -1;
	unsigned int wifi_on = -1;
	bool bt_gps_fm_off = false;
	#endif

	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	if (consys_get_adie_chipid_mt6983() == ADIE_6635) {
		/* enable A-die top_ck_en_0 */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			connsys_adie_top_ck_en_ctl_mt6983_gen(1);
		#endif

		/* set A-die clock buffer setting and wt_slp_top CR */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			/* Get semaphore before read */
			if (consys_sema_acquire_timeout_mt6983(spi_semaphore_index, spi_semaphore_timeout_usec) == CONN_SEMA_GET_FAIL) {
				pr_err("[EFUSE READ] Require semaphore fail\n");
				connsys_adie_top_ck_en_ctl_mt6983_gen(0);
				return -1;
			}

			if ((next_status & (~(0x1 << CONNDRV_TYPE_BT))) == 0)
				bt_only = true;

			if (bt_only) {
				if (hw_version == 0x66358A00)
					connsys_adie_clock_buffer_setting_mt6635_e1_bt_only_mt6983_gen();
				else if (hw_version == 0x66358A10 || hw_version == 0x66358A11)
					connsys_adie_clock_buffer_setting_mt6635_e2_bt_only_mt6983_gen();
				else
					pr_err("[%s] wrong adie version (0x%08x)\n", __func__, hw_version);
			} else {
				if (hw_version == 0x66358A00)
					connsys_adie_clock_buffer_setting_mt6635_e1_wf_gps_fm_on_mt6983_gen();
				else if (hw_version == 0x66358A10 || hw_version == 0x66358A11)
					connsys_adie_clock_buffer_setting_mt6635_e2_wf_gps_fm_on_mt6983_gen();
				else
					pr_err("[%s] wrong adie version (0x%08x)\n", __func__, hw_version);
			}
			consys_sema_release_mt6983(spi_semaphore_index);
		#endif

		/* Disable A-die top_ck_en_0 */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			connsys_adie_top_ck_en_ctl_mt6983_gen(0);
		#endif
	}

	if (consys_get_adie_chipid_mt6983() == ADIE_6637) {
		/* enable A-die top_ck_en_0 */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			connsys_adie_top_ck_en_ctl_mt6983_gen(1);
		#endif

		/* Get semaphore before read */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			if (consys_sema_acquire_timeout_mt6983(spi_semaphore_index, spi_semaphore_timeout_usec) == CONN_SEMA_GET_FAIL) {
				pr_err("[SPI WRITE] Require semaphore fail\n");
				return CONNINFRA_SPI_OP_FAIL;
			}

			curr_bt = (curr_status & (0x1 << CONNDRV_TYPE_BT)) >> CONNDRV_TYPE_BT;
			curr_fm = (curr_status & (0x1 << CONNDRV_TYPE_FM)) >> CONNDRV_TYPE_FM;
			curr_gps = (curr_status & (0x1 << CONNDRV_TYPE_GPS)) >> CONNDRV_TYPE_GPS;
			curr_wifi = (curr_status & (0x1 << CONNDRV_TYPE_WIFI)) >> CONNDRV_TYPE_WIFI;

			next_bt = (next_status & (0x1 << CONNDRV_TYPE_BT)) >> CONNDRV_TYPE_BT;
			next_fm = (next_status & (0x1 << CONNDRV_TYPE_FM)) >> CONNDRV_TYPE_FM;
			next_gps = (next_status & (0x1 << CONNDRV_TYPE_GPS)) >> CONNDRV_TYPE_GPS;
			next_wifi = (next_status & (0x1 << CONNDRV_TYPE_WIFI)) >> CONNDRV_TYPE_WIFI;

			bt_on = (curr_bt != next_bt) ? next_bt : -1;
			fm_on = (curr_fm != next_fm) ? next_fm : -1;
			gps_on = (curr_gps != next_gps) ? next_gps : -1;
			wifi_on = (curr_wifi != next_wifi) ? next_wifi : -1;

			bt_gps_fm_off = false;
			if (((curr_bt + curr_gps + curr_fm) != 0) && ((next_bt + next_gps + next_fm) == 0))
				bt_gps_fm_off = true;
		#endif

		/* turn on WF XO_BUF */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			if (wifi_on == 1) {
				consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ATOP_RG_TOP_XO_2, 0xFE000000);
				consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ATOP_RG_TOP_XO_3, 0xE0000000);
			}
		#endif

		/* turn on GPS/BT/FM XO_BUF */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			if (bt_on == 1 || gps_on == 1 || fm_on == 1) {
				consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ATOP_RG_TOP_XO_7, 0x7);
			}
		#endif

		/* turn off WF XO_BUF */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			if (wifi_on == 0) {
				consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ATOP_RG_TOP_XO_2, 0x8000000);
				consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ATOP_RG_TOP_XO_3, 0x0);
			}
		#endif

		/* turn off GPS/BT/FM XO_BUF */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			if (bt_gps_fm_off == true) {
				consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ATOP_RG_TOP_XO_7, 0x0);
			}
		#endif

		#ifndef CONFIG_FPGA_EARLY_PORTING
			consys_sema_release_mt6983(spi_semaphore_index);
		#endif

		/* Disable A-die top_ck_en_0 */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			connsys_adie_top_ck_en_ctl_mt6983_gen(0);
		#endif
	}

	return 0;
}

int connsys_adie_clock_buffer_setting_mt6635_e1_wf_gps_fm_on_mt6983_gen(void)
{
	#ifndef CONFIG_FPGA_EARLY_PORTING
	unsigned int rg_top_xtal_01 = 0;
	unsigned int rg_top_xtal_02 = 0;
	#endif

	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	/* MT6635_E1 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_XTAL_01, &rg_top_xtal_01);
		rg_top_xtal_01 &= ~(0xc180);
		rg_top_xtal_01 |= (0xc180 & 0xc180);
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_XTAL_01, rg_top_xtal_01);
		consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_XTAL_02, &rg_top_xtal_02);
		rg_top_xtal_02 &= ~(0xf0ff0080);
		rg_top_xtal_02 |= (0xd0550080 & 0xf0ff0080);
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_XTAL_02, rg_top_xtal_02);
	#endif

	return 0;
}

int connsys_adie_clock_buffer_setting_mt6635_e1_bt_only_mt6983_gen(void)
{
	#ifndef CONFIG_FPGA_EARLY_PORTING
	unsigned int rg_top_xtal_01 = 0;
	unsigned int rg_top_xtal_02 = 0;
	#endif

	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	/* MT6635_E1 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_XTAL_01, &rg_top_xtal_01);
		rg_top_xtal_01 &= ~(0xc180);
		rg_top_xtal_01 |= (0x100 & 0xc180);
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_XTAL_01, rg_top_xtal_01);
		consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_XTAL_02, &rg_top_xtal_02);
		rg_top_xtal_02 &= ~(0xf0ff0080);
		rg_top_xtal_02 |= (0xf0ff0000 & 0xf0ff0080);
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_XTAL_02, rg_top_xtal_02);
	#endif

	return 0;
}

int connsys_adie_clock_buffer_setting_mt6635_e2_wf_gps_fm_on_mt6983_gen(void)
{
	#ifndef CONFIG_FPGA_EARLY_PORTING
	unsigned int rg_top_xtal_01 = 0;
	unsigned int rg_top_xtal_02 = 0;
	#endif

	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	/* MT6635_E2 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_XTAL_01, &rg_top_xtal_01);
		rg_top_xtal_01 &= ~(0xc180);
		rg_top_xtal_01 |= (0xc180 & 0xc180);
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_XTAL_01, rg_top_xtal_01);
		consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_XTAL_02, &rg_top_xtal_02);
		rg_top_xtal_02 &= ~(0xf0ff0080);
		rg_top_xtal_02 |= (0x50550080 & 0xf0ff0080);
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_XTAL_02, rg_top_xtal_02);
	#endif

	return 0;
}

int connsys_adie_clock_buffer_setting_mt6635_e2_bt_only_mt6983_gen(void)
{
	#ifndef CONFIG_FPGA_EARLY_PORTING
	unsigned int rg_top_xtal_01 = 0;
	unsigned int rg_top_xtal_02 = 0;
	#endif

	if (SYS_SPI_TOP == 0) {
		pr_err("SYS_SPI_TOP is not defined\n");
		return -1;
	}

	/* MT6635_E2 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_XTAL_01, &rg_top_xtal_01);
		rg_top_xtal_01 &= ~(0xc180);
		rg_top_xtal_01 |= (0x100 & 0xc180);
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_XTAL_01, rg_top_xtal_01);
		consys_spi_read_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_XTAL_02, &rg_top_xtal_02);
		rg_top_xtal_02 &= ~(0xf0ff0080);
		rg_top_xtal_02 |= (0x70ff0000 & 0xf0ff0080);
		consys_spi_write_nolock_mt6983(SYS_SPI_TOP, CONSYS_GEN_ADIE6635_ATOP_RG_TOP_XTAL_02, rg_top_xtal_02);
	#endif

	return 0;
}

int connsys_low_power_setting_mt6983_gen(void)
{
	void __iomem *vir_addr_consys_gen_disp0_mutex_base = NULL;
	void __iomem *vir_addr_consys_gen_conn_infra_sysram_base_offset = NULL;
	int i = 0;
	unsigned int addr_offset = 0;

	vir_addr_consys_gen_disp0_mutex_base = ioremap(CONSYS_GEN_DISP0_MUTEX_BASE_ADDR, 0x340);
	vir_addr_consys_gen_conn_infra_sysram_base_offset = ioremap(CONSYS_GEN_CONN_INFRA_SYSRAM_BASE_OFFSET_ADDR, 0x10);

	if (!vir_addr_consys_gen_disp0_mutex_base) {
		pr_err("vir_addr_consys_gen_disp0_mutex_base(%x) ioremap fail\n", CONSYS_GEN_DISP0_MUTEX_BASE_ADDR);
		return -1;
	}

	if (!vir_addr_consys_gen_conn_infra_sysram_base_offset) {
		pr_err("vir_addr_consys_gen_conn_infra_sysram_base_offset(%x) ioremap fail\n", CONSYS_GEN_CONN_INFRA_SYSRAM_BASE_OFFSET_ADDR);
		iounmap(vir_addr_consys_gen_disp0_mutex_base);
		return -1;
	}

	if (CONN_CFG_ON_BASE == 0) {
		pr_err("CONN_CFG_ON_BASE is not defined\n");
		return -1;
	}

	if (CONN_RGU_ON_BASE == 0) {
		pr_err("CONN_RGU_ON_BASE is not defined\n");
		return -1;
	}

	if (CONN_CFG_BASE == 0) {
		pr_err("CONN_CFG_BASE is not defined\n");
		return -1;
	}

	if (CONN_BUS_CR_ON_BASE == 0) {
		pr_err("CONN_BUS_CR_ON_BASE is not defined\n");
		return -1;
	}

	if (CONN_BUS_CR_BASE == 0) {
		pr_err("CONN_BUS_CR_BASE is not defined\n");
		return -1;
	}

	if (CONN_OFF_DEBUG_CTRL_AO_BASE == 0) {
		pr_err("CONN_OFF_DEBUG_CTRL_AO_BASE is not defined\n");
		return -1;
	}

	if (CONN_CLKGEN_TOP_BASE == 0) {
		pr_err("CONN_CLKGEN_TOP_BASE is not defined\n");
		return -1;
	}

	if (CONN_HOST_CSR_TOP_BASE == 0) {
		pr_err("CONN_HOST_CSR_TOP_BASE is not defined\n");
		return -1;
	}

	/* Unmask on2off/off2on slpprot_rdy enable checker @conn_infra off power off=> check slpprot_rdy = 1'b1 and go to sleep */
	CONSYS_REG_WRITE_MASK(CONN_CFG_ON_BASE +
		CONSYS_GEN_CONN_INFRA_CFG_PWRCTRL0_OFFSET_ADDR, 0x1000, 0xF000);

	if (!consys_is_rc_mode_enable_mt6983()) {
		/* disable conn_top rc osc_ctrl_top */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_CLR_BIT(CONN_CFG_ON_BASE +
				CONSYS_GEN_CONN_INFRA_CFG_RC_CTL_0_OFFSET_ADDR, (0x1 << 7));
		#endif

		/* Legacy OSC control stable time */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_REG_WRITE_MASK(CONN_CFG_ON_BASE +
				CONSYS_GEN_OSC_CTL_0_OFFSET_ADDR, 0x80706, 0xFFFFFF);
		#endif

		/* Legacy OSC control unmask conn_srcclkena_ack */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_CLR_BIT(CONN_CFG_ON_BASE +
				CONSYS_GEN_OSC_CTL_1_OFFSET_ADDR, (0x1 << 16));
		#endif
	} else {
		/* GPS RC OSC control stable time */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_REG_WRITE(CONN_CFG_ON_BASE +
				CONSYS_GEN_CONN_INFRA_CFG_RC_CTL_1_GPS_OFFSET_ADDR, 0x2080706);
		#endif

		/* GPS RC OSC control unmask conn_srcclkena_ack */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_CLR_BIT(CONN_CFG_ON_BASE +
				CONSYS_GEN_CONN_INFRA_CFG_RC_CTL_0_GPS_OFFSET_ADDR, (0x1 << 15));
		#endif

		/* BT RC OSC control stable time */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_REG_WRITE(CONN_CFG_ON_BASE +
				CONSYS_GEN_CONN_INFRA_CFG_RC_CTL_1_BT_OFFSET_ADDR, 0x2080706);
		#endif

		/* BT RC OSC control unmask conn_srcclkena_ack */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_CLR_BIT(CONN_CFG_ON_BASE +
				CONSYS_GEN_CONN_INFRA_CFG_RC_CTL_0_BT_OFFSET_ADDR, (0x1 << 15));
		#endif

		/* WF RC OSC control stable time */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_REG_WRITE(CONN_CFG_ON_BASE +
				CONSYS_GEN_CONN_INFRA_CFG_RC_CTL_1_WF_OFFSET_ADDR, 0x2080706);
		#endif

		/* WF RC OSC control unmask conn_srcclkena_ack */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_CLR_BIT(CONN_CFG_ON_BASE +
				CONSYS_GEN_CONN_INFRA_CFG_RC_CTL_0_WF_OFFSET_ADDR, (0x1 << 15));
		#endif

		/* TOP RC OSC control stable time */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_REG_WRITE(CONN_CFG_ON_BASE +
				CONSYS_GEN_CONN_INFRA_CFG_RC_CTL_1_TOP_OFFSET_ADDR, 0x2080706);
		#endif

		/* TOP RC OSC control unmask conn_srcclkena_ack */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_CLR_BIT(CONN_CFG_ON_BASE +
				CONSYS_GEN_CONN_INFRA_CFG_RC_CTL_0_TOP_OFFSET_ADDR, (0x1 << 15));
		#endif

		/* enable conn_infra rc osc_ctl_top output */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_SET_BIT(CONN_CFG_ON_BASE +
				CONSYS_GEN_CONN_INFRA_CFG_RC_CTL_1_OFFSET_ADDR, (0x1 << 3));
		#endif

		udelay(30);

		/* enable conn_top rc osc_ctrl_gps output */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_SET_BIT(CONN_CFG_ON_BASE +
				CONSYS_GEN_CONN_INFRA_CFG_RC_CTL_1_OFFSET_ADDR, (0x1 << 0));
		#endif

		/* enable conn_top rc osc_ctrl_bt output */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_SET_BIT(CONN_CFG_ON_BASE +
				CONSYS_GEN_CONN_INFRA_CFG_RC_CTL_1_OFFSET_ADDR, (0x1 << 1));
		#endif

		/* enable conn_top rc osc_ctrl_wf output */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_SET_BIT(CONN_CFG_ON_BASE +
				CONSYS_GEN_CONN_INFRA_CFG_RC_CTL_1_OFFSET_ADDR, (0x1 << 2));
		#endif

		/* enable conn_top rc osc_ctrl_gps */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_SET_BIT(vir_addr_consys_gen_disp0_mutex_base +
				0x340, (0x1 << 4));
		#endif

		/* enable conn_top rc osc_ctrl_bt */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_SET_BIT(vir_addr_consys_gen_disp0_mutex_base +
				0x340, (0x1 << 5));
		#endif

		/* enable conn_top rc osc_ctrl_wf */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_SET_BIT(vir_addr_consys_gen_disp0_mutex_base +
				0x340, (0x1 << 6));
		#endif

		/* set conn_srcclkena control by conn_infra_emi_ctl */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_SET_BIT(CONN_CFG_ON_BASE +
				CONSYS_GEN_CONN_INFRA_CFG_RC_CTL_1_OFFSET_ADDR, (0x1 << 20));
		#endif

		/* disable legacy osc control output */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_CLR_BIT(CONN_CFG_ON_BASE +
				CONSYS_GEN_CONN_INFRA_CFG_RC_CTL_0_OFFSET_ADDR, (0x1 << 31));
		#endif

		/* disable legacy osc control */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_CLR_BIT(CONN_CFG_ON_BASE +
				CONSYS_GEN_CONN_INFRA_CFG_RC_CTL_0_OFFSET_ADDR, (0x1 << 0));
		#endif

		/* Legacy OSC control stable time */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_REG_WRITE_MASK(CONN_CFG_ON_BASE +
				CONSYS_GEN_OSC_CTL_0_OFFSET_ADDR, 0x80706, 0xFFFFFF);
		#endif

		/* Legacy OSC control unmask conn_srcclkena_ack */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_CLR_BIT(CONN_CFG_ON_BASE +
				CONSYS_GEN_OSC_CTL_1_OFFSET_ADDR, (0x1 << 16));
		#endif

		/* enable osc_rc_en_bk */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_SET_BIT(CONN_CFG_ON_BASE +
				CONSYS_GEN_CONN_INFRA_CFG_RC_CTL_0_OFFSET_ADDR, (0x1 << 30));
		#endif

		/* unmask osc_en for osc_en_rc */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_REG_WRITE_MASK(CONN_CFG_ON_BASE +
				CONSYS_GEN_CONN_INFRA_CFG_RC_CTL_1_OFFSET_ADDR, 0xD0, 0xF0);
		#endif

		/* enable conn_emi_bt_only_rc_en => conn_srcclkena = conn_srcclkena_cfg || conn_srcclkena_emi */
		#ifndef CONFIG_FPGA_EARLY_PORTING
			CONSYS_SET_BIT(CONN_CFG_ON_BASE +
				CONSYS_GEN_CONN_INFRA_CFG_RC_CTL_1_OFFSET_ADDR, (0x1 << 21));
		#endif
	}

	/* prevent subsys from power on/of in a short time interval */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_REG_WRITE_MASK(CONN_RGU_ON_BASE +
			CONSYS_GEN_BGFYS_ON_TOP_PWR_CTL_OFFSET_ADDR, 0x42540000, 0xFFFF0040);
		CONSYS_REG_WRITE_MASK(CONN_RGU_ON_BASE +
			CONSYS_GEN_WFSYS_ON_TOP_PWR_CTL_OFFSET_ADDR, 0x57460000, 0xFFFF0040);
	#endif

	/* conn2ap sleep protect release bypass ddr_en_ack check */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_CFG_BASE +
			CONSYS_GEN_EMI_CTL_0_OFFSET_ADDR, (0x1 << 18));
	#endif

	/* enable ddr_en timeout, timeout value = 1023 T (Bus clock) */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_REG_WRITE_MASK(CONN_CFG_BASE +
			CONSYS_GEN_EMI_CTL_0_OFFSET_ADDR, 0x10230, 0x7FF0);
	#endif

	/* update ddr_en timeout value enable */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_CFG_BASE +
			CONSYS_GEN_EMI_CTL_0_OFFSET_ADDR, (0x1 << 15));
	#endif

	/* conn_infra off domain bus dcm mode setting to off mode */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_BUS_CR_ON_BASE +
			CONSYS_GEN_CONN_OFF_BUS_DCM_CTL_1_OFFSET_ADDR, (0x1 << 14));
	#endif

	/* conn_infra off domain bus dcm enable */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_BUS_CR_ON_BASE +
			CONSYS_GEN_CONN_OFF_BUS_DCM_CTL_1_OFFSET_ADDR, (0x1 << 16));
	#endif

	/* conn_infra von domain bus dcm mode setting to off mode */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_BUS_CR_ON_BASE +
			CONSYS_GEN_CONN_VON_BUS_DCM_CTL_1_OFFSET_ADDR, (0x1 << 14));
	#endif

	/* conn_infra von domain bus dcm enable */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_BUS_CR_ON_BASE +
			CONSYS_GEN_CONN_VON_BUS_DCM_CTL_1_OFFSET_ADDR, (0x1 << 16));
	#endif

	/* conn_infra bus host ck request hw mode */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_BUS_CR_ON_BASE +
			CONSYS_GEN_CONN_INFRA_CKSYS_CTRL_OFFSET_ADDR, (0x1 << 0));
	#endif

	/* bus access protector (to aviod BT/WF/GPS access each other) */
	CONSYS_REG_WRITE_MASK(CONN_BUS_CR_BASE +
		CONSYS_GEN_LIGHT_SECURITY_CTRL_OFFSET_ADDR, 0xC63, 0xC63);

	/* set conn_infra_off bus apb/ahb/axi layer timeout - step 1 set timing */
	CONSYS_REG_WRITE_MASK(CONN_BUS_CR_BASE +
		CONSYS_GEN_CONN_INFRA_OFF_BUS_TIMEOUT_CTRL_OFFSET_ADDR, 0x188, 0x7F8);

	/* set conn_infra_off bus apb/ahb/axi layer timeout - step 2 enable function */
	CONSYS_SET_BIT(CONN_BUS_CR_BASE +
		CONSYS_GEN_CONN_INFRA_OFF_BUS_TIMEOUT_CTRL_OFFSET_ADDR, (0x1 << 0));

	/* set conn_infra_on bus apb timeout - step 1 set timing */
	CONSYS_REG_WRITE_MASK(CONN_BUS_CR_ON_BASE +
		CONSYS_GEN_CONN_INFRA_ON_BUS_TIMEOUT_CTRL_OFFSET_ADDR, 0x188, 0x7F8);

	/* set conn_infra_on bus apb timeout - step 2 enable function */
	CONSYS_SET_BIT(CONN_BUS_CR_ON_BASE +
		CONSYS_GEN_CONN_INFRA_ON_BUS_TIMEOUT_CTRL_OFFSET_ADDR, (0x1 << 0));

	/* enable conn_infra off bus tool auto gen timeout feature */
	CONSYS_SET_BIT(CONN_OFF_DEBUG_CTRL_AO_BASE +
		CONSYS_GEN_CONN_INFRA_VDNR_GEN_U_DEBUG_CTRL_AO_CONN_INFRA_OFF_CTRL0_OFFSET_ADDR, (0x1 << 9));

	/* write 0x1804d000[31:16] = 0x7f40000 */
	CONSYS_REG_WRITE_MASK(CONN_OFF_DEBUG_CTRL_AO_BASE +
		CONSYS_GEN_CONN_INFRA_VDNR_GEN_U_DEBUG_CTRL_AO_CONN_INFRA_OFF_CTRL0_OFFSET_ADDR, 0x7F40000, 0xFFFF0000);

	/* write 0x1804d000[2] = 0x4 */
	CONSYS_SET_BIT(CONN_OFF_DEBUG_CTRL_AO_BASE +
		CONSYS_GEN_CONN_INFRA_VDNR_GEN_U_DEBUG_CTRL_AO_CONN_INFRA_OFF_CTRL0_OFFSET_ADDR, (0x1 << 2));

	/* write 0x1804d000[3] = 0x8 */
	CONSYS_SET_BIT(CONN_OFF_DEBUG_CTRL_AO_BASE +
		CONSYS_GEN_CONN_INFRA_VDNR_GEN_U_DEBUG_CTRL_AO_CONN_INFRA_OFF_CTRL0_OFFSET_ADDR, (0x1 << 3));

	/* write 0x1804d000[4] = 0x10 */
	CONSYS_SET_BIT(CONN_OFF_DEBUG_CTRL_AO_BASE +
		CONSYS_GEN_CONN_INFRA_VDNR_GEN_U_DEBUG_CTRL_AO_CONN_INFRA_OFF_CTRL0_OFFSET_ADDR, (0x1 << 4));

	/* write 0x1804d000[9] = 0x0 */
	CONSYS_CLR_BIT(CONN_OFF_DEBUG_CTRL_AO_BASE +
		CONSYS_GEN_CONN_INFRA_VDNR_GEN_U_DEBUG_CTRL_AO_CONN_INFRA_OFF_CTRL0_OFFSET_ADDR, (0x1 << 9));

	/* enable conn_infra bus bpll div_1 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_CLKGEN_TOP_BASE +
			CONSYS_GEN_CKGEN_BUS_BPLL_DIV_1_OFFSET_ADDR, (0x1 << 0));
	#endif

	/* enable conn_infra bus bpll div_2 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_CLKGEN_TOP_BASE +
			CONSYS_GEN_CKGEN_BUS_BPLL_DIV_2_OFFSET_ADDR, (0x1 << 0));
	#endif

	/* enable conn_infra bus wpll div_1 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_CLKGEN_TOP_BASE +
			CONSYS_GEN_CKGEN_BUS_WPLL_DIV_1_OFFSET_ADDR, (0x1 << 0));
	#endif

	/* enable conn_infra bus wpll div_2 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_CLKGEN_TOP_BASE +
			CONSYS_GEN_CKGEN_BUS_WPLL_DIV_2_OFFSET_ADDR, (0x1 << 0));
	#endif

	/* set rfspi pll to bpll div 13 */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_CLR_BIT(CONN_CLKGEN_TOP_BASE +
			CONSYS_GEN_CLKGEN_RFSPI_CK_CTRL_OFFSET_ADDR, (0x1 << 7));
	#endif

	/* set rfsp bpll div 13 en */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_CLKGEN_TOP_BASE +
			CONSYS_GEN_CLKGEN_RFSPI_CK_CTRL_OFFSET_ADDR, (0x1 << 6));
	#endif

	/* set rfspi pll to bpll */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_CLKGEN_TOP_BASE +
			CONSYS_GEN_CLKGEN_RFSPI_CK_CTRL_OFFSET_ADDR, (0x1 << 4));
	#endif

	/* set conn_infra sleep count to host side control */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_HOST_CSR_TOP_BASE +
			CONSYS_GEN_HOST_CONN_INFRA_SLP_CNT_CTL_OFFSET_ADDR, (0x1 << 31));
	#endif

	/* set conn_infra sleep count enable (host side) */
	#ifndef CONFIG_FPGA_EARLY_PORTING
		CONSYS_SET_BIT(CONN_HOST_CSR_TOP_BASE +
			CONSYS_GEN_HOST_CONN_INFRA_SLP_CNT_CTL_OFFSET_ADDR, (0x1 << 0));
	#endif

	/* set coex related clock cg clock enable */
	CONSYS_REG_WRITE(CONN_CLKGEN_TOP_BASE +
		CONSYS_GEN_CKGEN_COEX_0_OFFSET_ADDR, 0xFFFFFFFF);
	CONSYS_REG_WRITE_MASK(CONN_CLKGEN_TOP_BASE +
		CONSYS_GEN_CKGEN_COEX_1_OFFSET_ADDR, 0xFFFF, 0xFFFF);

	/* disable conn_infra bus clock sw control  ==> conn_infra bus clock hw control */
	CONSYS_CLR_BIT(CONN_CLKGEN_TOP_BASE +
		CONSYS_GEN_CKGEN_BUS_OFFSET_ADDR, (0x1 << 0));

	/* conn_infra cmdbt code download */
	addr_offset = 0x0;
	for (i = 0; i < 1024; i++) {
		CONSYS_REG_WRITE(vir_addr_consys_gen_conn_infra_sysram_base_offset +
			addr_offset, g_cmdbt_dwn_value_ary[i]);
		addr_offset += 0x4;
	}

	/* conn_infra wakeup need restore first */
	CONSYS_SET_BIT(CONN_CFG_ON_BASE +
		CONSYS_GEN_CONN_INFRA_CFG_PWRCTRL0_OFFSET_ADDR, (0x1 << 6));

	/* Conn_infra HW_CONTROL => conn_infra enter dsleep mode */
	CONSYS_SET_BIT(CONN_CFG_ON_BASE +
		CONSYS_GEN_CONN_INFRA_CFG_PWRCTRL0_OFFSET_ADDR, (0x1 << 0));

	if (vir_addr_consys_gen_disp0_mutex_base)
		iounmap(vir_addr_consys_gen_disp0_mutex_base);

	if (vir_addr_consys_gen_conn_infra_sysram_base_offset)
		iounmap(vir_addr_consys_gen_conn_infra_sysram_base_offset);

	return 0;
}

int consys_conninfra_wakeup_mt6983_gen(void)
{
	if (CONN_HOST_CSR_TOP_BASE == 0) {
		pr_err("CONN_HOST_CSR_TOP_BASE is not defined\n");
		return -1;
	}

	/* wake up conn_infra */
	CONSYS_REG_WRITE(CONN_HOST_CSR_TOP_BASE +
		CONSYS_GEN_CONN_INFRA_WAKEPU_TOP_OFFSET_ADDR, 0x1);

	return 0;
}

int consys_conninfra_sleep_mt6983_gen(void)
{
	if (CONN_HOST_CSR_TOP_BASE == 0) {
		pr_err("CONN_HOST_CSR_TOP_BASE is not defined\n");
		return -1;
	}

	/* release conn_infra force on */
	CONSYS_REG_WRITE(CONN_HOST_CSR_TOP_BASE +
		CONSYS_GEN_CONN_INFRA_WAKEPU_TOP_OFFSET_ADDR, 0x0);

	return 0;
}
