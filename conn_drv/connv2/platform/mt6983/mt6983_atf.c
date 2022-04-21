// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2022 MediaTek Inc.
 */

#include "conninfra.h"
#include "consys_hw.h"
#include "mt6983.h"
#include "mt6983_atf.h"
#include "mt6983_connsyslog.h"
#include "mt6983_consys_reg_offset.h"
#include "mt6983_pos.h"

/*******************************************************************************
 *                                 M A C R O S
 ********************************************************************************
 */
#define PLATFORM_SOC_CHIP 0x6983

/*******************************************************************************
 *                            P U B L I C   D A T A
 ********************************************************************************
 */

struct consys_hw_ops_struct g_consys_hw_ops_mt6983_atf = {
	.consys_plt_init_atf_data = consys_init_atf_data_mt6983_atf,

	/* load from dts */
	/* TODO: mtcmos should move to a independent module */
	.consys_plt_clk_get_from_dts = consys_clk_get_from_dts_mt6983,

	/* clock */
	.consys_plt_clock_buffer_ctrl = consys_clock_buffer_ctrl_mt6983,
	.consys_plt_co_clock_type = consys_get_co_clock_type_mt6983,

	/* POS */
	.consys_plt_conninfra_on_power_ctrl = consys_conninfra_on_power_ctrl_mt6983,
	.consys_plt_set_if_pinmux = consys_set_if_pinmux_mt6983,

	.consys_plt_polling_consys_chipid = consys_polling_chipid_mt6983_atf,
	.consys_plt_d_die_cfg = connsys_d_die_cfg_mt6983_atf,
	.consys_plt_spi_master_cfg = connsys_spi_master_cfg_mt6983_atf,
	.consys_plt_a_die_cfg = connsys_a_die_cfg_mt6983_atf,
	.consys_plt_afe_wbg_cal = connsys_afe_wbg_cal_mt6983_atf,
	.consys_plt_afe_sw_patch = connsys_afe_sw_patch_mt6983_atf,
	.consys_plt_subsys_pll_initial = connsys_subsys_pll_initial_mt6983_atf,
	.consys_plt_low_power_setting = connsys_low_power_setting_mt6983_atf,
	.consys_plt_soc_chipid_get = consys_soc_chipid_get_mt6983,
	.consys_plt_conninfra_wakeup = consys_conninfra_wakeup_mt6983_atf,
	.consys_plt_conninfra_sleep = consys_conninfra_sleep_mt6983_atf,
	.consys_plt_is_rc_mode_enable = consys_is_rc_mode_enable_mt6983,

	/* debug */
	.consys_plt_clock_fail_dump = consys_clock_fail_dump_mt6983,
	.consys_plt_get_hw_ver = consys_get_hw_ver_mt6983,

	.consys_plt_spi_read = consys_spi_read_mt6983_atf,
	.consys_plt_spi_write = consys_spi_write_mt6983_atf,
	.consys_plt_spi_update_bits = consys_spi_update_bits_mt6983_atf,
	.consys_plt_spi_clock_switch = consys_spi_clock_switch_mt6983_atf,
	.consys_plt_subsys_status_update = consys_subsys_status_update_mt6983_atf,

	.consys_plt_thermal_query = consys_thermal_query_mt6983_atf,
	.consys_plt_enable_power_dump = consys_enable_power_dump_mt6983,
	.consys_plt_reset_power_state = consys_reset_power_state_mt6983_atf,
	.consys_plt_power_state = consys_power_state_dump_mt6983_atf,
	.consys_plt_soc_timestamp_get = consys_soc_timestamp_get_mt6983,
	.consys_plt_adie_detection = consys_adie_detection_mt6983,
	.consys_plt_set_mcu_control = consys_set_mcu_control_mt6983_atf,

	.consys_plt_pre_cal_backup = consys_pre_cal_backup_mt6983_atf,
	.consys_plt_pre_cal_clean_data = consys_pre_cal_clean_data_mt6983_atf,
};

extern struct consys_hw_ops_struct g_consys_hw_ops_mt6983_atf;
extern struct consys_reg_mng_ops g_dev_consys_reg_ops_mt6983_atf;
extern struct consys_platform_emi_ops g_consys_platform_emi_ops_mt6983_atf;
extern struct consys_platform_pmic_ops g_consys_platform_pmic_ops_mt6983;
extern struct consys_platform_coredump_ops g_consys_platform_coredump_ops_mt6983;

const struct conninfra_plat_data mt6983_plat_data_atf = {
	.chip_id = PLATFORM_SOC_CHIP,
	.consys_hw_version = CONN_HW_VER,
	.hw_ops = &g_consys_hw_ops_mt6983_atf,
	.reg_ops = &g_dev_consys_reg_ops_mt6983_atf,
	.platform_emi_ops = &g_consys_platform_emi_ops_mt6983_atf,
	.platform_pmic_ops = &g_consys_platform_pmic_ops_mt6983,
	.platform_coredump_ops = &g_consys_platform_coredump_ops_mt6983,
	.connsyslog_config = &g_connsyslog_config,
};

int consys_init_atf_data_mt6983_atf(void)
{
	struct arm_smccc_res res;
	int platform_config;
	static bool initialized = 0;
	int ret;

	if (initialized == 1)
		return 0;

	platform_config = consys_hw_get_platform_config();
	arm_smccc_smc(MTK_SIP_KERNEL_CONNSYS_CONTROL, SMC_CONNSYS_INIT_ATF_DATA_MT6983_OPID,
		platform_config, conn_hw_env.clock_type, 0, 0, 0, 0, &res);
	ret = res.a0;
	initialized = 1;
	return ret;
}

int consys_polling_chipid_mt6983_atf(void)
{
	int ret = 0;
	CONNSYS_SMC_CALL_RET(SMC_CONSYS_POLLING_CHIPID_MT6983_OPID, 0, 0, 0, 0, 0, 0, ret);
	return ret;
}

int connsys_d_die_cfg_mt6983_atf(void)
{
	int ret = 0;
	CONNSYS_SMC_CALL_RET(SMC_CONNSYS_D_DIE_CFG_MT6983_OPID, 0, 0, 0, 0, 0, 0, ret);
	return ret;
}

int connsys_spi_master_cfg_mt6983_atf(unsigned int next_status)
{
	int ret = 0;
	CONNSYS_SMC_CALL_RET(SMC_CONNSYS_SPI_MASTER_CFG_MT6983_OPID, 0, 0, 0, 0, 0, 0, ret);
	return ret;
}

int connsys_a_die_cfg_mt6983_atf(void)
{
	int ret = 0;
	CONNSYS_SMC_CALL_RET(SMC_CONNSYS_A_DIE_CFG_MT6983_OPID, 0, 0, 0, 0, 0, 0, ret);
	return ret;
}

int connsys_afe_wbg_cal_mt6983_atf(void)
{
	int ret = 0;
	CONNSYS_SMC_CALL_RET(SMC_CONNSYS_AFE_WBG_CAL_MT6983_OPID, 0, 0, 0, 0, 0, 0, ret);
	return ret;
}

void connsys_afe_sw_patch_mt6983_atf(void)
{
	CONNSYS_SMC_CALL_VOID(SMC_CONNSYS_AFE_SW_PATCH_MT6983_OPID, 0, 0, 0, 0, 0, 0);
}

int connsys_subsys_pll_initial_mt6983_atf(void)
{
	int ret = 0;
	CONNSYS_SMC_CALL_RET(SMC_CONNSYS_SUBSYS_PLL_INITIAL_MT6983_OPID, 0, 0, 0, 0, 0, 0, ret);
	return ret;
}

int connsys_low_power_setting_mt6983_atf(unsigned int curr_status, unsigned int next_status)
{
	int ret = 0;
	CONNSYS_SMC_CALL_RET(SMC_CONNSYS_LOW_POWER_SETTING_MT6983_OPID,
			     curr_status, next_status, 0, 0, 0, 0, ret);
	return ret;
}

int consys_conninfra_wakeup_mt6983_atf(void)
{
	int ret = 0;
	CONNSYS_SMC_CALL_RET(SMC_CONSYS_CONNINFRA_WAKEUP_MT6983_OPID, 0, 0, 0, 0, 0, 0, ret);
	return ret;
}

int consys_conninfra_sleep_mt6983_atf(void)
{
	int ret = 0;
	CONNSYS_SMC_CALL_RET(SMC_CONSYS_CONNINFRA_SLEEP_MT6983_OPID, 0, 0, 0, 0, 0, 0, ret);
	return ret;
}

int consys_spi_read_mt6983_atf(enum sys_spi_subsystem subsystem, unsigned int addr,
	unsigned int *data)
{
	struct arm_smccc_res res;
	int ret;

	arm_smccc_smc(MTK_SIP_KERNEL_CONNSYS_CONTROL, SMC_CONNSYS_SPI_READ_MT6983_OPID,
		subsystem, addr, 0, 0, 0, 0, &res);
	*data = res.a1;
	ret = res.a0;
	return ret;
}

int consys_spi_write_mt6983_atf(enum sys_spi_subsystem subsystem, unsigned int addr,
				unsigned int data)
{
	int ret = 0;
	CONNSYS_SMC_CALL_RET(SMC_CONNSYS_SPI_WRITE_MT6983_OPID, subsystem, addr, data, 0, 0, 0, ret);
	return ret;
}

int consys_spi_update_bits_mt6983_atf(enum sys_spi_subsystem subsystem, unsigned int addr,
	unsigned int data, unsigned int mask)
{
	int ret = 0;
	CONNSYS_SMC_CALL_RET(SMC_CONNSYS_SPI_UPDATE_BITS_MT6983_OPID,
			     subsystem, addr, data, mask, 0, 0, ret);
	return ret;
}

int consys_spi_clock_switch_mt6983_atf(enum connsys_spi_speed_type type)
{
	int ret = 0;
	CONNSYS_SMC_CALL_RET(SMC_CONNSYS_SPI_CLOCK_SWITCH_MT6983_OPID, type, 0, 0, 0, 0, 0, ret);
	return ret;
}

int consys_subsys_status_update_mt6983_atf(bool on, int radio)
{
	int ret = 0;
	CONNSYS_SMC_CALL_RET(SMC_CONNSYS_SUBSYS_STATUS_UPDATE_MT6983_OPID,
			     on, radio, 0, 0, 0, 0, ret);
	return ret;
}

int consys_thermal_query_mt6983_atf(void)
{
	int ret = 0;
	CONNSYS_SMC_CALL_RET(SMC_CONNSYS_THERMAL_QUERY_MT6983_OPID, 0, 0, 0, 0, 0, 0, ret);
	return ret;
}

int consys_reset_power_state_mt6983_atf(void)
{
	int ret = 0;
	CONNSYS_SMC_CALL_RET(SMC_CONNSYS_RESET_POWER_STATE_MT6983_OPID, 0, 0, 0, 0, 0, 0, ret);
	return ret;
}

/*
 * This is to get sleep count related information from ATF.
 * But it cannot get string from ATF.
 * Separate into several SMC call
 * Getting all data as integer value and then combine it into string.
 */
#define POWER_STATE_DUMP_DATA_SIZE	25
int consys_power_state_dump_mt6983_atf(char *buf, unsigned int size)
{
	int	i, op_id;
	struct arm_smccc_res res;
	unsigned long power_state_dump_data[POWER_STATE_DUMP_DATA_SIZE];
	int ret;

	for (op_id = SMC_CONNSYS_POWER_STATE_DUMP_MT6983_START_OPID, i = 0;
	     op_id < SMC_CONNSYS_POWER_STATE_DUMP_MT6983_END_OPID;
	     op_id++, i++) {
		arm_smccc_smc(MTK_SIP_KERNEL_CONNSYS_CONTROL, op_id,
			      0, 0, 0, 0, 0, 0, &res);
		ret = res.a0;
		if (ret) {
			pr_err("%s[%d], Get power state dump fail at opid=%d\n",
			       __func__, __LINE__, op_id);
			return -1;
		}
		power_state_dump_data[0 + 3 * i] = res.a1;
		power_state_dump_data[1 + 3 * i] = res.a2;
		power_state_dump_data[2 + 3 * i] = res.a3;
	}
	if (op_id == SMC_CONNSYS_POWER_STATE_DUMP_MT6983_END_OPID) {
		arm_smccc_smc(MTK_SIP_KERNEL_CONNSYS_CONTROL, op_id,
			      0, 0, 0, 0, 0, 0, &res);
		ret = res.a0;
		if (ret) {
			pr_err("%s[%d], Get power state dump fail\n", __func__, __LINE__);
			return -1;
		}
		power_state_dump_data[0 + 3 * i] = res.a1;
	}

	snprintf(buf, size,"[consys_power_state][round:%llu]"
		"conninfra:%u.%03u,%u;wf:%u.%03u,%u;bt:%u.%03u,%u;gps:%u.%03u,%u;"
		"[total]conninfra:%llu.%03llu,%llu;wf:%llu.%03llu,%llu;"
		"bt:%llu.%03llu,%llu;gps:%llu.%03llu,%llu;",
		power_state_dump_data[0],
		power_state_dump_data[1],
		power_state_dump_data[2],
		power_state_dump_data[3],
		power_state_dump_data[4],
		power_state_dump_data[5],
		power_state_dump_data[6],
		power_state_dump_data[7],
		power_state_dump_data[8],
		power_state_dump_data[9],
		power_state_dump_data[10],
		power_state_dump_data[11],
		power_state_dump_data[12],
		power_state_dump_data[13],
		power_state_dump_data[14],
		power_state_dump_data[15],
		power_state_dump_data[16],
		power_state_dump_data[17],
		power_state_dump_data[18],
		power_state_dump_data[19],
		power_state_dump_data[20],
		power_state_dump_data[21],
		power_state_dump_data[22],
		power_state_dump_data[23],
		power_state_dump_data[24]);

	pr_info("%s", buf);
	return ret;
}

void consys_set_mcu_control_mt6983_atf(int type, bool onoff)
{
	CONNSYS_SMC_CALL_VOID(SMC_CONNSYS_SET_MCU_CONTROL_MT6983_OPID, 0, 0, 0, 0, 0, 0);
}

int consys_pre_cal_backup_mt6983_atf(unsigned int offset, unsigned int size)
{
	int ret = 0;
	CONNSYS_SMC_CALL_RET(SMC_CONNSYS_PRE_CAL_BACKUP_MT6983_OPID,
			     offset, size, 0, 0, 0, 0, ret);
	return ret;
}

int consys_pre_cal_clean_data_mt6983_atf(void)
{
	int ret = 0;
	CONNSYS_SMC_CALL_RET(SMC_CONNSYS_PRE_CAL_CLEAN_DATA_MT6983_OPID, 0, 0, 0, 0, 0, 0, ret);
	return ret;
}

unsigned int consys_emi_set_remapping_reg_mt6983_atf(
	phys_addr_t con_emi_base_addr,
	phys_addr_t md_shared_emi_base_addr,
	phys_addr_t gps_emi_base_addr)
{
	int ret;
	CONNSYS_SMC_CALL_RET(SMC_CONNSYS_EMI_SET_REMAPPING_REG_MT6983_OPID,
			     0, 0, 0, 0, 0, 0, ret);
	return ret;
}

