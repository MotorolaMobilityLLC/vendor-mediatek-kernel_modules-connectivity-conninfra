/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2022 MediaTek Inc.
 */

#ifndef PLATFORM_MT6983_ATF_H
#define PLATFORM_MT6983_ATF_H

#include <linux/arm-smccc.h>
#include <linux/soc/mediatek/mtk_sip_svc.h>

#define CONNSYS_SMC_CALL_VOID(OPID, x2, x3, x4, x5, x6, x7) \
struct arm_smccc_res res; \
arm_smccc_smc(MTK_SIP_KERNEL_CONNSYS_CONTROL, OPID, \
	      x2, x3, x4, x5, x6, x7, &res)

#define CONNSYS_SMC_CALL_RET(OPID, x2, x3, x4, x5, x6, x7, ret) \
struct arm_smccc_res res; \
arm_smccc_smc(MTK_SIP_KERNEL_CONNSYS_CONTROL, OPID, \
	      x2, x3, x4, x5, x6, x7, &res);  \
ret = res.a0;

enum conn_smc_opid
{
	/* init */
	SMC_CONNSYS_INIT_ATF_DATA_MT6983_OPID = 0,

	/* consys_hw_ops */
	SMC_CONSYS_POLLING_CHIPID_MT6983_OPID = 10,
	SMC_CONNSYS_D_DIE_CFG_MT6983_OPID,
	SMC_CONNSYS_SPI_MASTER_CFG_MT6983_OPID,
	SMC_CONNSYS_A_DIE_CFG_MT6983_OPID,
	SMC_CONNSYS_AFE_SW_PATCH_MT6983_OPID,
	SMC_CONNSYS_AFE_WBG_CAL_MT6983_OPID,
	SMC_CONNSYS_SUBSYS_PLL_INITIAL_MT6983_OPID,
	SMC_CONNSYS_LOW_POWER_SETTING_MT6983_OPID,
	SMC_CONSYS_CONNINFRA_WAKEUP_MT6983_OPID,
	SMC_CONSYS_CONNINFRA_SLEEP_MT6983_OPID,

	SMC_CONNSYS_SPI_READ_MT6983_OPID,
	SMC_CONNSYS_SPI_WRITE_MT6983_OPID,
	SMC_CONNSYS_SPI_UPDATE_BITS_MT6983_OPID,
	SMC_CONNSYS_SPI_CLOCK_SWITCH_MT6983_OPID,
	SMC_CONNSYS_SUBSYS_STATUS_UPDATE_MT6983_OPID,
	SMC_CONNSYS_THERMAL_QUERY_MT6983_OPID,
	SMC_CONNSYS_RESET_POWER_STATE_MT6983_OPID,
	SMC_CONNSYS_POWER_STATE_DUMP_MT6983_START_OPID,
	SMC_CONNSYS_POWER_STATE_DUMP_MT6983_2_OPID,
	SMC_CONNSYS_POWER_STATE_DUMP_MT6983_3_OPID,

	SMC_CONNSYS_POWER_STATE_DUMP_MT6983_4_OPID,
	SMC_CONNSYS_POWER_STATE_DUMP_MT6983_5_OPID,
	SMC_CONNSYS_POWER_STATE_DUMP_MT6983_6_OPID,
	SMC_CONNSYS_POWER_STATE_DUMP_MT6983_7_OPID,
	SMC_CONNSYS_POWER_STATE_DUMP_MT6983_8_OPID,
	SMC_CONNSYS_POWER_STATE_DUMP_MT6983_END_OPID,
	SMC_CONNSYS_SET_MCU_CONTROL_MT6983_OPID,
	SMC_CONNSYS_PRE_CAL_BACKUP_MT6983_OPID,
	SMC_CONNSYS_PRE_CAL_CLEAN_DATA_MT6983_OPID,

	/* g_consys_reg_ops */
	SMC_CONNSYS_DEBUG_INIT_MT6983_OPID = 50,
	SMC_CONNSYS_DEBUG_DEINIT_MT6983_OPID,
	SMC_CONNSYS_CHECK_CONNINFRA_OFF_DOMAIN_OPID,
	SMC_CONNSYS_CHECK_CONNINFRA_IRQ_STATUS_OPID,
	SMC_CONNSYS_PRINT_DEBUG_MT6983_OPID,

	/* consys_platform_emi_ops */
	SMC_CONNSYS_EMI_SET_REMAPPING_REG_MT6983_OPID = 70,

	/* consys_platform_coredump_ops */
	SMC_CONNSYS_SETUP_DUMP_REGION_MT6983_OPID = 80,
	SMC_CONNSYS_SETUP_DYNAMIC_REMAP_MT6983_OPID,
};

int consys_init_atf_data_mt6983_atf(void);
int consys_polling_chipid_mt6983_atf(void);
int connsys_d_die_cfg_mt6983_atf(void);
int connsys_spi_master_cfg_mt6983_atf(unsigned int next_status);
int connsys_a_die_cfg_mt6983_atf(void);
int connsys_afe_wbg_cal_mt6983_atf(void);
void connsys_afe_sw_patch_mt6983_atf(void);
int connsys_subsys_pll_initial_mt6983_atf(void);
int connsys_low_power_setting_mt6983_atf(unsigned int curr_status, unsigned int next_status);
int consys_conninfra_wakeup_mt6983_atf(void);
int consys_conninfra_sleep_mt6983_atf(void);
int consys_spi_read_mt6983_atf(enum sys_spi_subsystem subsystem, unsigned int addr, unsigned int *data);
int consys_spi_write_mt6983_atf(enum sys_spi_subsystem subsystem, unsigned int addr, unsigned int data);
int consys_spi_update_bits_mt6983_atf(enum sys_spi_subsystem subsystem, unsigned int addr, unsigned int data, unsigned int mask);
int consys_spi_clock_switch_mt6983_atf(enum connsys_spi_speed_type type);
int consys_subsys_status_update_mt6983_atf(bool on, int radio);
int consys_thermal_query_mt6983_atf(void);
int consys_reset_power_state_mt6983_atf(void);
int consys_power_state_dump_mt6983_atf(char *buf, unsigned int size);
void consys_set_mcu_control_mt6983_atf(int type, bool onoff);
int consys_pre_cal_backup_mt6983_atf(unsigned int offset, unsigned int size);
int consys_pre_cal_clean_data_mt6983_atf(void);

#endif /* PLATFORM_MT6983_ATF_H */
