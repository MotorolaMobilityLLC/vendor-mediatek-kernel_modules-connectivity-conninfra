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

#ifndef _PLATFORM_MT6885_POS_H_
#define _PLATFORM_MT6885_POS_H_


unsigned int consys_emi_set_remapping_reg(unsigned int);

int consys_conninfra_on_power_ctrl(unsigned int enable);
void consys_set_if_pinmux(unsigned int enable);
int consys_polling_chipid(void);

int connsys_d_die_cfg(void);
int connsys_spi_master_cfg(void);
int connsys_a_die_cfg(void);
int connsys_afe_wbg_cal(void);
int connsys_low_power_setting(void);

#endif				/* _PLATFORM_MT6789_POS_H_ */
