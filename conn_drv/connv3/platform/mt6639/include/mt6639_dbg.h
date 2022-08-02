/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2022 MediaTek Inc.
 */

#ifndef _PLATFORM_MT6639_DBG_H_
#define _PLATFORM_MT6639_DBG_H_

#include "connv3_hw_dbg.h"

#define MT6639_AP2CONN_INFRA_ON_SLP_PROT	0x70028730
#define MT6639_CONN_INFRA_CLK_DETECT		0x7c023000
#define MT6639_CONN_INFRA_VERSION_ID_REG	0x7c011000
#define MT6639_CONN_INFRA_VERSION_ID		0x03010001
#define MT6639_CONN_INFRA_OFF_IRQ_REG		0x7c023400

const struct connv3_dbg_command mt6639_pwr_b[] = {
	/* Write, addr, mask, value, Read, addr*/
	{ false, 0, 0, 0, true, 0x7C060A10},
};

const struct connv3_dump_list mt6639_dmp_list_pwr_b = {
	"power_b", sizeof(mt6639_pwr_b)/sizeof(struct connv3_dbg_command),
	mt6639_pwr_b,
};

const struct connv3_dbg_command mt6639_pwr_c[] = {
	/* Write, addr, mask, value, Read, addr*/
	{false, 0, 0, 0, true, 0x7C011030},
	{false, 0, 0, 0, true, 0x7C012050},
	{false, 0, 0, 0, true, 0x7C001344},
	{false, 0, 0, 0, true, 0x7C000400},
	{false, 0, 0, 0, true, 0x7C000404},
	{false, 0, 0, 0, true, 0x7C0030A8},
	{false, 0, 0, 0, true, 0x7C003120},
	{false, 0, 0, 0, true, 0x7C003124},
	{false, 0, 0, 0, true, 0x7C003128},
	{false, 0, 0, 0, true, 0x7C00312C},
	{false, 0, 0, 0, true, 0x7C003130},
	{false, 0, 0, 0, true, 0x7C003134},
	{true, 0x7c011100, 0x00600000, 0x0, true, 0x7C011134},
	{true, 0x7c011100, 0x00600000, 0x00200000, true, 0x7C011134},
	{true, 0x7c011100, 0x00600000, 0x00400000, true, 0x7C011134},
	{true, 0x7c011100, 0x00600000, 0x00600000, true, 0x7C011134},
	{false, 0, 0, 0, true, 0x7C091B8C},
	{false, 0, 0, 0, true, 0x7C091B90},
	{false, 0, 0, 0, true, 0x7C091B94},
	{false, 0, 0, 0, true, 0x7C091B98},
	{false, 0, 0, 0, true, 0x7C091B9C},
	{false, 0, 0, 0, true, 0x7C091BA0},
	{false, 0, 0, 0, true, 0x7C091BA4},
	{false, 0, 0, 0, true, 0x7C098000},
	{false, 0, 0, 0, true, 0x7C098050},
	{false, 0, 0, 0, true, 0x7C098054},
	{false, 0, 0, 0, true, 0x7C098058},
	{false, 0, 0, 0, true, 0x7C098108},
	{false, 0, 0, 0, true, 0x7C098004},
};

const struct connv3_dump_list mt6639_dmp_list_pwr_c = {
	"power_c", sizeof(mt6639_pwr_c)/sizeof(struct connv3_dbg_command),
	mt6639_pwr_c,
};

const struct connv3_dbg_command mt6639_bus_a[] = {
	{true, 0x7c023408, 0x0, 0x00000000, false, 0x0},
	{true, 0x7c02340c, 0x0, 0x00010001, true, 0x7c023404},
	{true, 0x7c02340c, 0x0, 0x00020001, true, 0x7c023404},
	{true, 0x7c02340c, 0x0, 0x00030001, true, 0x7c023404},
	{true, 0x7c02340c, 0x0, 0x00010002, true, 0x7c023404},
	{true, 0x7c02340c, 0x0, 0x00000003, true, 0x7c023404},
	{true, 0x7c02340c, 0x0, 0x00010003, true, 0x7c023404},
	{true, 0x7c02340c, 0x0, 0x00020003, true, 0x7c023404},
	{true, 0x7c02340c, 0x0, 0x00030003, true, 0x7c023404},
	{true, 0x7c02340c, 0x0, 0x00010004, true, 0x7c023404},
	{true, 0x7c02340c, 0x0, 0x00020004, true, 0x7c023404},
	{true, 0x7c02340c, 0x0, 0x00030004, true, 0x7c023404},
	{false, 0, 0, 0, true, 0x7c023400},
	{false, 0, 0, 0, true, 0x7c023410},
	{false, 0, 0, 0, true, 0x7c023414},
	{false, 0, 0, 0, true, 0x7c023418},
	{false, 0, 0, 0, true, 0x7c023434},
	{false, 0, 0, 0, true, 0x7c00EA04},
};

const struct connv3_dump_list mt6639_dmp_list_bus_a = {
	"bus_a", sizeof(mt6639_bus_a)/sizeof(struct connv3_dbg_command),
	mt6639_bus_a,
};

const struct connv3_dbg_command mt6639_bus_b[] = {
	{false, 0x0, 0x0, 0x0, true, 0x7c02341c},
	{false, 0x0, 0x0, 0x0, true, 0x7c023420},
	{false, 0x0, 0x0, 0x0, true, 0x7c023424},
	{false, 0x0, 0x0, 0x0, true, 0x7c023428},
	{false, 0x0, 0x0, 0x0, true, 0x7c02342c},
	{false, 0x0, 0x0, 0x0, true, 0x7c023430},
	{false, 0x0, 0x0, 0x0, true, 0x7c00e128},
	{false, 0x0, 0x0, 0x0, true, 0x7c00e12c},
	{false, 0x0, 0x0, 0x0, true, 0x7c00e130},
	{false, 0x0, 0x0, 0x0, true, 0x7c00e134},
	{false, 0x0, 0x0, 0x0, true, 0x7c00e138},
	{false, 0x0, 0x0, 0x0, true, 0x7c00e13c},
	{false, 0x0, 0x0, 0x0, true, 0x7c00e140},
	{true, 0x7c023408, 0x0, 0x00000013, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000014, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000015, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000016, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000017, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000018, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000019, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x0000001a, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x0000001b, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x0000001c, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x0000001d, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x0000001e, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x0000001f, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000020, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000021, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000022, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000023, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000024, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000025, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000026, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000027, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000028, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000029, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x0000002a, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x0000002b, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x0000002c, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x0000002d, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000001, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000002, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000003, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000004, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000005, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000006, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000007, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000008, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000009, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x0000000a, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x0000000b, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x0000000c, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x0000000d, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x0000000e, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x0000000f, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000010, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000011, true, 0x7c023404},
	{true, 0x7c023408, 0x0, 0x00000012, true, 0x7c023404},
	{false, 0x0, 0x0, 0x0, true, 0x7c048280},
	{false, 0x0, 0x0, 0x0, true, 0x7c048284},
	{false, 0x0, 0x0, 0x0, true, 0x7c048288},
	{false, 0x0, 0x0, 0x0, true, 0x7c04828C},
	{false, 0x0, 0x0, 0x0, true, 0x7c048290},
	{false, 0x0, 0x0, 0x0, true, 0x7c049408},
	{false, 0x0, 0x0, 0x0, true, 0x7c04940C},
	{false, 0x0, 0x0, 0x0, true, 0x7c049410},
	{false, 0x0, 0x0, 0x0, true, 0x7c049414},
	{false, 0x0, 0x0, 0x0, true, 0x7c049418},
	{false, 0x0, 0x0, 0x0, true, 0x7c04941C},
	{false, 0x0, 0x0, 0x0, true, 0x7c049420},
	{false, 0x0, 0x0, 0x0, true, 0x7c049424},
	{false, 0x0, 0x0, 0x0, true, 0x7c049428},
	{false, 0x0, 0x0, 0x0, true, 0x7c04942C},
	{false, 0x0, 0x0, 0x0, true, 0x7c049430},
	{false, 0x0, 0x0, 0x0, true, 0x7c048320},
	{false, 0x0, 0x0, 0x0, true, 0x7c048400},
	{false, 0x0, 0x0, 0x0, true, 0x7c060D04},
	{false, 0x0, 0x0, 0x0, true, 0x7c060D08},
	{false, 0x0, 0x0, 0x0, true, 0x7c060D0C},
	{false, 0x0, 0x0, 0x0, true, 0x7c048310},
	{false, 0x0, 0x0, 0x0, true, 0x7c048314},
	{false, 0x0, 0x0, 0x0, true, 0x7c048318},
	{false, 0x0, 0x0, 0x0, true, 0x7c04831c},
};

const struct connv3_dump_list mt6639_dmp_list_bus_b = {
	"bus_b", sizeof(mt6639_bus_b)/sizeof(struct connv3_dbg_command),
	mt6639_bus_b,
};

const struct connv3_dbg_command mt6639_cfg_clk_a[] = {
	{false, 0x0, 0x0, 0x0, true, 0x7C060A00},
	{false, 0x0, 0x0, 0x0, true, 0x7C060A0C},
	{true, 0x7C06015c, 0x7, 0x0, true, 0x7C060a04},
	{true, 0x7C06015c, 0x7, 0x1, true, 0x7C060a04},
	{true, 0x7C06015c, 0x7, 0x2, true, 0x7C060a04},
	{true, 0x7C06015c, 0x7, 0x3, true, 0x7C060a04},
	{true, 0x7C06015c, 0x7, 0x4, true, 0x7C060a04},
	{true, 0x7C06015c, 0x7, 0x5, true, 0x7C060a04},
	{true, 0x7C06015c, 0x7, 0x6, true, 0x7C060a04},
	{true, 0x7C06015c, 0x7, 0x7, true, 0x7C060a04},
	{true, 0x7C060160, 0xf, 0x0, true, 0x7C060a08},
	{true, 0x7C060160, 0xf, 0x1, true, 0x7C060a08},
	{true, 0x7C060160, 0xf, 0x2, true, 0x7C060a08},
	{true, 0x7C060160, 0xf, 0x3, true, 0x7C060a08},
	{true, 0x7C060160, 0xf, 0x4, true, 0x7C060a08},
	{true, 0x7C060160, 0xf, 0x5, true, 0x7C060a08},
};

const struct connv3_dump_list mt6639_dmp_list_cfg_clk_a = {
	"cfg_clk_a", sizeof(mt6639_cfg_clk_a)/sizeof(struct connv3_dbg_command),
	mt6639_cfg_clk_a
};

const struct connv3_dbg_command mt6639_cfg_clk_b[] = {
	{false, 0x0, 0x0, 0x0, true, 0x7C023200}, /* B1 */
	{false, 0x0, 0x0, 0x0, true, 0x7C011130}, /* B2 */
	{true, 0x7C011100, 0x600000, 0x0, true, 0x7C011134}, /* B3 */
	{true, 0x7C011100, 0x600000, 0x200000, true, 0x7C011134}, /* B4 */
	{true, 0x7C011100, 0x600000, 0x400000, true, 0x7C011134}, /* B5 */
	{true, 0x7C011100, 0x600000, 0x600000, true, 0x7C011134}, /* B6 */
	{true, 0x7C01603C, 0x3f, 0x14, false, 0x0}, /* B7 */
	{true, 0x7C01603C, 0xfc0, 0x5c0, false, 0x0},
	{true, 0x7C01601C, 0x0, 0x03020100, false, 0x0},
	{true, 0x7C016020, 0x0, 0x07060504, false, 0x0},
	{true, 0x7C016024, 0x0, 0x0B0A0908, false, 0x0},
	{true, 0x7C016028, 0x0, 0x0F0E0D0C, false, 0x0},
	{true, 0x7C01602C, 0x0, 0x13121110, false, 0x0},
	{true, 0x7C016030, 0x0, 0x17161514, false, 0x0},
	{true, 0x7C016034, 0x0, 0x1B1A1918, false, 0x0},
	{true, 0x7C016038, 0x0, 0x1F1E1D1C, false, 0x0},
	{true, 0x7C016058, 0x2, 0x2, false, 0x0},
	{false, 0x0, 0x0, 0x0, true, 0x7C023200},
	{true, 0x7C01603C, 0x3f, 0x24, false, 0x0}, /* B8 */
	{true, 0x7C01601C, 0x0, 0x03020100, false, 0x0},
	{true, 0x7C016020, 0x0, 0x07060504, false, 0x0},
	{true, 0x7C016024, 0x0, 0x0B0A0908, false, 0x0},
	{true, 0x7C016028, 0x0, 0x0F0E0D0C, false, 0x0},
	{true, 0x7C01602C, 0x0, 0x13121110, false, 0x0},
	{true, 0x7C016030, 0x0, 0x17161514, false, 0x0},
	{true, 0x7C016034, 0x0, 0x1B1A1918, false, 0x0},
	{true, 0x7C016038, 0x0, 0x1F1E1D1C, false, 0x0},
	{true, 0x7C016058, 0x2, 0x2, false, 0x0},
	{false, 0x0, 0x0, 0x0, true, 0x7C023200},
};

const struct connv3_dump_list mt6639_dmp_list_cfg_clk_b = {
	"cfg_clk_b", sizeof(mt6639_cfg_clk_b)/sizeof(struct connv3_dbg_command),
	mt6639_cfg_clk_b
};

/* Not in debug sop, add for extra information.
 */
const struct connv3_dbg_command mt6639_bus_extra[] = {
	/* For RFSPI timeout */
	{false, 0x0, 0x0, 0x0, true, 0x7c012038},
	{false, 0x0, 0x0, 0x0, true, 0x7c01203c},
	{false, 0x0, 0x0, 0x0, true, 0x7c012080},
	{true, 0x7C023500, 0x0, 0xAEAA68, true, 0x7C023504},
};

const struct connv3_dump_list mt6639_dmp_list_bus_extra = {
	"bus_extra", sizeof(mt6639_bus_extra)/sizeof(struct connv3_dbg_command),
	mt6639_bus_extra
};

#endif
