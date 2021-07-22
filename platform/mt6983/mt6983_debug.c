// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2020 MediaTek Inc.
 */
#include "consys_reg_util.h"

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
static void consys_print_power_debug(int level);
static void consys_print_bus_debug(int level);

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/

int consys_print_debug_mt6983(int level)
{
	if (level < 0 || level > 2) {
		pr_info("%s level[%d] unexpected value.");
		return 0;
	}

	consys_print_power_debug(level);
	consys_print_bus_debug(level);

	return 0;
}

static void consys_print_power_debug(int level)
{
	unsigned int ret = 0;
	unsigned char *addr;

	/* A0 */
	addr = ioremap(0x1c00183c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00183c\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A0]0x1C00183C = %x\n", ret);

	iounmap(addr);

	/* A1 */
	addr = ioremap(0x1c001840, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c001840\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A1]0x1C001840 = %x\n", ret);

	iounmap(addr);

	/* A2 */
	addr = ioremap(0x1c00d12c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d12c\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A2]0x1C00D12C = %x\n", ret);

	iounmap(addr);

	/* A3 */
	addr = ioremap(0x1c00d130, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d130\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A3]0x1C00D130 = %x\n", ret);

	iounmap(addr);

	/* A4 */
	addr = ioremap(0x1c00d134, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d134\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A4]0x1C00D134 = %x\n", ret);

	iounmap(addr);

	/* A5 */
	addr = ioremap(0x1c00d138, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d138\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A5]0x1C00D138 = %x\n", ret);

	iounmap(addr);

	/* A6 */
	addr = ioremap(0x1c001e04, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c001e04\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A6]0x1C001E04 = %x\n", ret);

	iounmap(addr);

	/* A7 */
	addr = ioremap(0x10000180, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x10000180\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A7]0x10000180 = %x\n", ret);

	iounmap(addr);

	/* A8 */
	addr = ioremap(0x1c00d700, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d700\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A8]0x1C00D700 = %x\n", ret);

	iounmap(addr);

	/* A9 */
	addr = ioremap(0x1c00d704, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d704\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A9]0x1C00D704 = %x\n", ret);

	iounmap(addr);

	/* A10 */
	addr = ioremap(0x1c00d708, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d708\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A10]0x1C00D708 = %x\n", ret);

	iounmap(addr);

	/* A11 */
	addr = ioremap(0x1c00d70c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d70c\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A11]0x1C00D70C = %x\n", ret);

	iounmap(addr);

	/* A12 */
	addr = ioremap(0x1c00d710, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d710\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A12]0x1C00D710 = %x\n", ret);

	iounmap(addr);

	/* A13 */
	addr = ioremap(0x1c00d714, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d714\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A13]0x1C00D714 = %x\n", ret);

	iounmap(addr);

	/* A14 */
	addr = ioremap(0x1c00d718, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d718\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A14]0x1C00D718 = %x\n", ret);

	iounmap(addr);

	/* A15 */
	addr = ioremap(0x1c00d71c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d71c\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A15]0x1C00D71C = %x\n", ret);

	iounmap(addr);

	/* A16 */
	addr = ioremap(0x1c00d720, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d720\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A16]0x1C00D720 = %x\n", ret);

	iounmap(addr);

	/* A17 */
	addr = ioremap(0x1c00d724, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d724\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A17]0x1C00D724 = %x\n", ret);

	iounmap(addr);

	/* A18 */
	addr = ioremap(0x1c00d728, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d728\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A18]0x1C00D728 = %x\n", ret);

	iounmap(addr);

	/* A19 */
	addr = ioremap(0x1c00d72c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d72c\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A19]0x1C00D72C = %x\n", ret);

	iounmap(addr);

	/* A20 */
	addr = ioremap(0x1c00d730, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d730\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A20]0x1C00D730 = %x\n", ret);

	iounmap(addr);

	/* A21 */
	addr = ioremap(0x1c00d734, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d734\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A21]0x1C00D734 = %x\n", ret);

	iounmap(addr);

	/* A22 */
	addr = ioremap(0x1c00d738, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d738\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A22]0x1C00D738 = %x\n", ret);

	iounmap(addr);

	/* A23 */
	addr = ioremap(0x1c00d73c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d73c\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A23]0x1C00D73C = %x\n", ret);

	iounmap(addr);

	/* A24 */
	addr = ioremap(0x1c00d740, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d740\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A24]0x1C00D740 = %x\n", ret);

	iounmap(addr);

	/* A25 */
	addr = ioremap(0x1c00d744, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d744\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A25]0x1C00D744 = %x\n", ret);

	iounmap(addr);

	/* A26 */
	addr = ioremap(0x1c00d748, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d748\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A26]0x1C00D748 = %x\n", ret);

	iounmap(addr);

	/* A27 */
	addr = ioremap(0x1c00d74c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d74c\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A27]0x1C00D74C = %x\n", ret);

	iounmap(addr);

	/* A28 */
	addr = ioremap(0x1c00d750, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d750\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A28]0x1C00D750 = %x\n", ret);

	iounmap(addr);

	/* A29 */
	addr = ioremap(0x1c00d754, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d754\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A29]0x1C00D754 = %x\n", ret);

	iounmap(addr);

	/* A30 */
	addr = ioremap(0x1c00d758, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d758\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A30]0x1C00D758 = %x\n", ret);

	iounmap(addr);

	/* A31 */
	addr = ioremap(0x1c00d75c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d75c\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A31]0x1C00D75C = %x\n", ret);

	iounmap(addr);

	/* A32 */
	addr = ioremap(0x1c00d760, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d760\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A32]0x1C00D760 = %x\n", ret);

	iounmap(addr);

	/* A33 */
	addr = ioremap(0x1c00d764, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d764\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A33]0x1C00D764 = %x\n", ret);

	iounmap(addr);

	/* A34 */
	addr = ioremap(0x1c00d768, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d768\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A34]0x1C00D768 = %x\n", ret);

	iounmap(addr);

	/* A35 */
	addr = ioremap(0x1c00d76c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d76c\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A35]0x1C00D76C = %x\n", ret);

	iounmap(addr);

	/* A36 */
	addr = ioremap(0x1c00d770, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d770\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A36]0x1C00D770 = %x\n", ret);

	iounmap(addr);

	/* A37 */
	addr = ioremap(0x1c00d774, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d774\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A37]0x1C00D774 = %x\n", ret);

	iounmap(addr);

	/* A38 */
	addr = ioremap(0x1c00d778, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d778\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A38]0x1C00D778 = %x\n", ret);

	iounmap(addr);

	/* A39 */
	addr = ioremap(0x1c00d77c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d77c\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A39]0x1C00D77C = %x\n", ret);

	iounmap(addr);

	/* A40 */
	addr = ioremap(0x1c00d104, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1c00d104\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][A40]0x1C00D104 = %x\n", ret);

	iounmap(addr);

	if (level == 0)
		return;

	/* Dump after conn_infra_on is ready */
	/* B0 */
	addr = ioremap(0x1806015c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1806015c\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	CONSYS_REG_WRITE(addr, ret & 0xfffffff8 | 0x0);
	iounmap(addr);

	addr = ioremap(0x18060a04, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18060a04\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][B0]0x18060a04 = %x\n", ret);

	iounmap(addr);

	/* B1 */
	addr = ioremap(0x1806015c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1806015c\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	CONSYS_REG_WRITE(addr, ret & 0xfffffff8 | 0x4);
	iounmap(addr);

	addr = ioremap(0x18060a04, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18060a04\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][B1]0x18060a04 = %x\n", ret);

	iounmap(addr);

	/* B2 */
	addr = ioremap(0x1806015c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1806015c\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	CONSYS_REG_WRITE(addr, ret & 0xfffffff8 | 0x5);
	iounmap(addr);

	addr = ioremap(0x180602c8, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x180602c8\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][B2]0x180602C8 = %x\n", ret);

	iounmap(addr);

	/* B3 */
	addr = ioremap(0x18060a10, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18060a10\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][B3]0x18060A10 = %x\n", ret);

	iounmap(addr);

	if (level == 1)
		return;

	/* Dump after conn_infra_off is ready */
	/* C0 */
	addr = ioremap(0x18011030, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18011030\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][C0]0x18011030 = %x\n", ret);

	iounmap(addr);

	/* C1 */
	addr = ioremap(0x18012050, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18012050\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][C1]0x18012050 = %x\n", ret);

	iounmap(addr);

	/* C2 */
	addr = ioremap(0x18001344, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18001344\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][C2]0x18001344 = %x\n", ret);

	iounmap(addr);

	/* C3 */
	addr = ioremap(0x18000400, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18000400\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][C3]0x18000400 = %x\n", ret);

	iounmap(addr);

	/* C4 */
	addr = ioremap(0x18000404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18000404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][C4]0x18000404 = %x\n", ret);

	iounmap(addr);

	/* C5 */
	addr = ioremap(0x180030a8, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x180030a8\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][C5]0x180030A8 = %x\n", ret);

	iounmap(addr);

	/* C6 */
	addr = ioremap(0x18003120, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18003120\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][C6]0x18003120 = %x\n", ret);

	iounmap(addr);

	/* C7 */
	addr = ioremap(0x18003124, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18003124\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][C7]0x18003124 = %x\n", ret);

	iounmap(addr);

	/* C8 */
	addr = ioremap(0x18003128, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18003128\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][C8]0x18003128 = %x\n", ret);

	iounmap(addr);

	/* C9 */
	addr = ioremap(0x1800312c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1800312c\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][C9]0x1800312C = %x\n", ret);

	iounmap(addr);

	/* C10 */
	addr = ioremap(0x18003130, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18003130\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][C10]0x18003130 = %x\n", ret);

	iounmap(addr);

	/* C11 */
	addr = ioremap(0x18003134, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18003134\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][C11]0x18003134 = %x\n", ret);

	iounmap(addr);

	/* C12 */
	addr = ioremap(0x18011100, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18011100\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	CONSYS_REG_WRITE(addr, ret & 0xff9fffff | 0x0);
	iounmap(addr);

	addr = ioremap(0x18011134, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18011134\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][]0x18011134 = %x\n", ret);

	iounmap(addr);

	/* C13 */
	addr = ioremap(0x18011100, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18011100\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	CONSYS_REG_WRITE(addr, ret & 0xff9fffff | 0x200000);
	iounmap(addr);

	addr = ioremap(0x18011134, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18011134\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][]0x18011134 = %x\n", ret);

	iounmap(addr);

	/* C14 */
	addr = ioremap(0x18011100, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18011100\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	CONSYS_REG_WRITE(addr, ret & 0xff9fffff | 0x400000);
	iounmap(addr);

	addr = ioremap(0x18011134, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18011134\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][]0x18011134 = %x\n", ret);

	iounmap(addr);

	/* C15 */
	addr = ioremap(0x18011100, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18011100\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	CONSYS_REG_WRITE(addr, ret & 0xff9fffff | 0x600000);
	iounmap(addr);

	addr = ioremap(0x18011134, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18011134\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read][]0x18011134 = %x\n", ret);

	iounmap(addr);

	return;
}
static void consys_print_bus_debug(int level)
{
	unsigned int ret = 0;
	unsigned char *addr;

	if (level == 0)
		return;

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x0);
	iounmap(addr);
	pr_info("[write]0x18023408=0x0");

	addr = ioremap(0x1802340c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1802340c\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x10001);
	iounmap(addr);
	pr_info("[write]0x1802340c=0x10001");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x1802340c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1802340c\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x20001);
	iounmap(addr);
	pr_info("[write]0x1802340c=0x20001");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x1802340c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1802340c\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x10002);
	iounmap(addr);
	pr_info("[write]0x1802340c=0x10002");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x1802340c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1802340c\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x20002);
	iounmap(addr);
	pr_info("[write]0x1802340c=0x20002");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x1802340c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1802340c\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x30002);
	iounmap(addr);
	pr_info("[write]0x1802340c=0x30002");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x1);
	iounmap(addr);
	pr_info("[write]0x18023408=0x1");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x2);
	iounmap(addr);
	pr_info("[write]0x18023408=0x2");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x3);
	iounmap(addr);
	pr_info("[write]0x18023408=0x3");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x4);
	iounmap(addr);
	pr_info("[write]0x18023408=0x4");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x5);
	iounmap(addr);
	pr_info("[write]0x18023408=0x5");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x6);
	iounmap(addr);
	pr_info("[write]0x18023408=0x6");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x7);
	iounmap(addr);
	pr_info("[write]0x18023408=0x7");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023400, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023400\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3400 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x9);
	iounmap(addr);
	pr_info("[write]0x18023408=0x9");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0xa);
	iounmap(addr);
	pr_info("[write]0x18023408=0xa");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0xb);
	iounmap(addr);
	pr_info("[write]0x18023408=0xb");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0xc);
	iounmap(addr);
	pr_info("[write]0x18023408=0xc");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0xd);
	iounmap(addr);
	pr_info("[write]0x18023408=0xd");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0xe);
	iounmap(addr);
	pr_info("[write]0x18023408=0xe");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0xf);
	iounmap(addr);
	pr_info("[write]0x18023408=0xf");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x10);
	iounmap(addr);
	pr_info("[write]0x18023408=0x10");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x11);
	iounmap(addr);
	pr_info("[write]0x18023408=0x11");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x12);
	iounmap(addr);
	pr_info("[write]0x18023408=0x12");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x13);
	iounmap(addr);
	pr_info("[write]0x18023408=0x13");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x14);
	iounmap(addr);
	pr_info("[write]0x18023408=0x14");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x15);
	iounmap(addr);
	pr_info("[write]0x18023408=0x15");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x16);
	iounmap(addr);
	pr_info("[write]0x18023408=0x16");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x17);
	iounmap(addr);
	pr_info("[write]0x18023408=0x17");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023408\n");
		return;
	}
	CONSYS_REG_WRITE(addr, 0x18);
	iounmap(addr);
	pr_info("[write]0x18023408=0x18");

	addr = ioremap(0x18023404, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023404\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3404 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x1802341c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1802341c\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_341c = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023410, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023410\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3410 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023414, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023414\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3414 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x18023418, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x18023418\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1802_3418 = %x\n", ret);
	iounmap(addr);

	if (level == 1)
		return;

	addr = ioremap(0x1800e03c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1800e03c\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1800_e03c = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x1800e040, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1800e040\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1800_e040 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x1800e044, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1800e044\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1800_e044 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x1804c004, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1804c004\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1804_c004 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x1804c00c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1804c00c\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1804_c00c = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x1804d408, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1804d408\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1804_D408 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x1804d40c, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1804d40c\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1804_D40c = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x1804d410, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1804d410\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1804_D410 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x1804d414, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1804d414\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1804_D414 = %x\n", ret);
	iounmap(addr);

	addr = ioremap(0x1804d418, 0x10);
	if (!addr) {
		pr_info("fail to ioremap: 0x1804d418\n");
		return;
	}
	ret = CONSYS_REG_READ(addr);
	pr_info("[read]0x1804_D418 = %x\n", ret);
	iounmap(addr);



	return;
}
