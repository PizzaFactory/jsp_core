/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *
 *  TOPPERS/JSP for Blackfin
 *
 *  Copyright (C) 2004,2006,2006 by Takemasa Nakamura
 *  Copyright (C) 2004 by Ujinosuke
 *
 *  �嵭����Ԥϡ��ʲ��� (1)����(4) �ξ�狼��Free Software Foundation
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
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 *
 *
 */

/*
 *  �����ޥɥ饤�С�ADSP-BF533�ѡ�
 *
 */

#ifndef _HW_TIMER_H_
#define _HW_TIMER_H_

#include <s_services.h>
#include <sil.h>

#ifndef _MACRO_ONLY




/**************************************************************
 *  �����ޤε�ư����
 *
 *  �����ޤ�������������Ū�ʥ����޳�����׵��ȯ�������롥
 *
 **************************************************************/
Inline void
hw_timer_initialize()
{
#ifdef USE_TIC_CORE
    // Core timer
    // TCNTL bit assignement
    // TMPWR                  0x00000001
    // TMREN                  0x00000002
    // TAUTORLD               0x00000004
    // TINT                   0x00000008
    *__pTCNTL = 0x00000001;                 // TMPWR : power up timer;
    *__pTPERIOD = CORECLOCK/1000;           // CORE CLOCK is defined in sys_config.h
    *__pTCNTL = 0x00000007;                 // TMPWR | TMREN | TAUTORLD;
#else
    // GPT2(General-purpose timer2)


    /* TIMERx_CONFIG Registers */
    // PWM_OUT      0x0001
    // WDTH_CAP     0x0002
    // EXT_CLK      0x0003
    // PULSE_HI     0x0004
    // PERIOD_CNT   0x0008
    // IRQ_ENA      0x0010
    // TIN_SEL      0x0020
    // OUT_DIS      0x0040
    // CLK_SEL      0x0080
    // TOGGLE_HI    0x0100
    // EMU_RUN      0x0200

    *__pTIMER2_CONFIG = 0x0059; // PERIOD_CNT | OUT_DIS |IRQ_ENA | PWM_OUT ( PWM_OUT, Output Pad disable)
    *__pTIMER2_PERIOD = SYSCLOCK/1000;  // SYS CLOCK is defined in sys_config.h
    *__pTIMER2_WIDTH = 1;                   // 0 < width < period

    // TIMEN0           0x0001
    // TIMEN1           0x0002
    // TIMEN2           0x0004
    *__pTIMER_ENABLE = 0x004;           // TIMEN2 timer2 start

    ena_int( INHNO_TIMER );             // enable Timer Interrupt
#endif
    asm("ssync;");

}

/**************************************************************
 *  �����޳�����׵�Υ��ꥢ
 **************************************************************/
Inline void
hw_timer_int_clear()
{
#ifdef USE_TIC_CORE
    // Core timer
    // TCNTL bit assignement
    // TMPWR                  0x00000001
    // TMREN                  0x00000002
    // TAUTORLD               0x00000004
    // TINT                   0x00000008

    /* TINT��W1C�ǤϤʤ��Τǡ�TINT��TINT�ӥåȤ�0��񤭹��� */
    *__pTCNTL = 0x00000007; // TMPWR | TMREN | TAUTORLD;
#else
    // GPT2(General-purpose timer2)

    // TIMIL0           0x0001
    // TIMIL1           0x0002
    // TIMIL2           0x0004
    *__pTIMER_STATUS = 0x004;   // TIMIL2, Clear interrupt
#endif
    asm("ssync;");
}

/**************************************************************
 *  �����ޤ���߽���
 *
 *  �����ޤ�ư�����ߤ����롥
 **************************************************************/
Inline void
hw_timer_terminate()
{
    /*
     *  �����ޤ�ư�����ߤ��롥
     */
#ifdef USE_TIC_CORE
    // Core timer
    // TCNTL bit assignement
    // TMPWR                  0x00000001
    // TMREN                  0x00000002
    // TAUTORLD               0x00000004
    // TINT                   0x00000008
    *__pTCNTL = 0x00000005; //TMPWR | TAUTORLD | TINT;      // ���
    *__pTCNTL = 0;                          // �ѥ������⡼��
#else
    // GPT2(General-purpose timer2)
    // TIMDIS0          0x0001
    // TIMDIS1          0x0002
    // TIMDIS2          0x0004
    *__pTIMER_DISABLE = 0x004;          // TIMDIS2, timer2 disable
#endif
    asm("ssync;");
}


#endif /* _MACRO_ONLY */
#endif /* _HW_TIMER_H_ */
