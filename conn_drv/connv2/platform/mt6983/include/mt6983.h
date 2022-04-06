/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2021 MediaTek Inc.
 */

#ifndef _PLATFORM_MT6983_H_
#define _PLATFORM_MT6983_H_

#define	ADIE_6637	0x6637
#define	ADIE_6635	0x6635

enum conn_semaphore_type
{
	CONN_SEMA_CHIP_POWER_ON_INDEX = 0,
	CONN_SEMA_CALIBRATION_INDEX = 1,
	CONN_SEMA_FW_DL_INDEX = 2,
	CONN_SEMA_CLOCK_SWITCH_INDEX = 3,
	CONN_SEMA_PINMUX_INDEX = 4,
	CONN_SEMA_CCIF_INDEX = 5,
	CONN_SEMA_COEX_INDEX = 6,
	CONN_SEMA_USB_EP0_INDEX = 7,
	CONN_SEMA_USB_SHARED_INFO_INDEX = 8,
	CONN_SEMA_USB_SUSPEND_INDEX = 9,
	CONN_SEMA_USB_RESUME_INDEX = 10,
	CONN_SEMA_PCIE_INDEX = 11,
	CONN_SEMA_RFSPI_INDEX = 12,
	CONN_SEMA_EFUSE_INDEX = 13,
	CONN_SEMA_THERMAL_INDEX = 14,
	CONN_SEMA_FLASH_INDEX = 15,
	CONN_SEMA_DEBUG_INDEX = 16,
	CONN_SEMA_WIFI_LP_INDEX = 17,
	CONN_SEMA_PATCH_DL_INDEX = 18,
	CONN_SEMA_SHARED_VAR_INDEX = 19,
	CONN_SEMA_BGF_UART0_INDEX = 20,
	CONN_SEMA_BGF_UART1_INDEX = 21,
	CONN_SEMA_SDIO_CLK_INDEX = 22,
	CONN_SEMA_CONN_INFRA_COMMON_SYSRAM_INDEX = 23,
	CONN_SEMA_NUM_MAX = 25 /* can't be omitted */
};

struct consys_plat_thermal_data_mt6983 {
	int thermal_b;
	int slop_molecule;
	int offset;
};

int consys_clk_get_from_dts_mt6983(struct platform_device *pdev);
int consys_clock_buffer_ctrl_mt6983(unsigned int enable);
unsigned int consys_soc_chipid_get_mt6983(void);
void consys_clock_fail_dump_mt6983(void);
unsigned int consys_get_hw_ver_mt6983(void);
int consys_thermal_query_mt6983(void);
/* Power state relative */
int consys_enable_power_dump_mt6983(void);
int consys_reset_power_state_mt6983(void);
int consys_power_state_dump_mt6983(char *buf, unsigned int size);

unsigned long long consys_soc_timestamp_get_mt6983(void);
unsigned int consys_adie_detection_mt6983(void);
void consys_set_mcu_control_mt6983(int type, bool onoff);

int consys_pre_cal_backup_mt6983(unsigned int offset, unsigned int size);
int consys_pre_cal_clean_data_mt6983(void);

int consys_platform_spm_conn_ctrl_mt6983(unsigned int enable);
int consys_get_co_clock_type_mt6983(void);
int consys_co_clock_type_mt6983(void);
void update_thermal_data_mt6983(struct consys_plat_thermal_data_mt6983* input);
unsigned int consys_get_adie_chipid_mt6983(void);
int consys_pre_cal_restore_mt6983(void);

#endif /* _PLATFORM_MT6983_H_ */
