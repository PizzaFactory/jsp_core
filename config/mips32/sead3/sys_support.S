/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2000-2003 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 *  Copyright (C) 2007-     by Monami Software Limited Partnership, JAPAN
 *
 *  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation
 *  �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
 *  �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
 *  ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 *  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ��������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ����դ��뤳�ȡ�
 *
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ��������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 */

#define _MACRO_ONLY

#include "jsp_kernel.h"
#include "offset.h"		/* INT_TABLE_intmask�Τ����ɬ�� */

	.set at
	.set noreorder

/*============================================================================*/

/* ����߽����˴ؤ��롢������װ���Ƚ��ʬ�������Υ����ƥ��¸�� */

	.section .text
	.align 2

	.global proc_interrupt_sys

	/*  �ƤӽФ��줿�Ȥ���       */
	/*    a1�˥��ơ������쥸���� */
	/*    a2�˸����쥸����       */
	/*  ���ͤ����äƤ���         */

proc_interrupt_sys:
	and     t2, a2, a1          /*  ������׵�ӥåȤ˥ޥ����򤫤���  */
	sll t1, t2, 16
	clz t1, t1 /* t1 = (t2 & Cause_IP7) ? 0 : (t2 & Cause_IP6) ? 1 : (t2 & Cause_IP5) ? 2 : ... */
	li t0, 7
	subu t0, t0, t1
	bltz t0, proc_interrupt_sys_0
	nop

/*  ���ơ������쥸�����Υޥ��������C����롼����ƤӽФ�  */
/*    t0�˳�����װ��ֹ椬���ꤵ�줿���֤Ǥ��������  */
	la      t3, int_table   /*  �����٥������ɥ쥹  */
	sll     t4, t0, 3       /*  ������װ��ֹ��8��
				      TNT_TABLE���ϡ�
					�ϥ�ɥ�Υ��ɥ쥹(4�Х���)
					��MIPS32�����γ���ߥޥ���(4�Х���)
				      �Ρ����8�Х��ȡ� */
	addu     t5, t3, t4      /*  �٥������ɥ쥹�򻻽�  */
	lw      t6, INT_TABLE_intmask(t5)
				/*  IPM(����ߵ��ĥӥå�)�ɤ߽Ф���*/
	and t6, t6, a1
	ori t4, a1, (SR_IM | SR_EXL | SR_IE)
	xori t4, t4, (SR_IM | SR_EXL | SR_IE)
	or t6, t6, t4
	mtc0 t6, Status /* EXL = 0, IE = 0 */
	ori t6, t6, SR_IE
	lw      t7, (t5)        /*  C����롼������Ƭ���ɥ쥹�ɤ߽Ф�  */

	jalr    t7          /*  C����롼����ƤӽФ�  */
	mtc0 t6, Status /* EXL = 0, IE = 1 */

	mfc0    t0, Status
	ori t0, t0, SR_IE
	xori t0, t0, SR_IE
	mtc0 t0, Status /* IE = 0 */

	/*  CP0�ϥ����ɤΤ���λ��ֲԤ�  */
#ifdef NOP_FOR_CP0_HAZARD
	NOP_FOR_CP0_HAZARD
#endif /* NOP_FOR_CP0_HAZARD */

proc_interrupt_sys_0:
	j	join_interrupt_and_exception
	nop