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
 *
 *
 */


#ifndef _CHIP_CONFIG_H_
#define _CHIP_CONFIG_H_


/*
 *  �������åȥ����ƥ��¸�⥸�塼���ADSP-BF592���ѡ�
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�t_config.h �Τߤ��饤�󥯥롼�ɤ���롥
 *  ¾�Υե����뤫��ľ�ܥ��󥯥롼�ɤ��ƤϤʤ�ʤ���
*/

/*
 *  �������åȥ����ƥ�Υϡ��ɥ������񸻤����
 *
 *  DEVICE_INTERRUPT_COUNT��SIC_IMASK�Υӥåȿ�
 *  ��Ϳ���롣
 *  ADSP-BF592�Υӥåȿ���32�ʤΤǡ��ͤ�32�Ǥ��롣
 */

#define DEVICE_INTERRUPT_COUNT 32



/*
 *  PLL�����å����ȿ��׻��ޥ���
 *
 *  �ѹ����ƤϤʤ�ʤ����ѥ�᡼����sys_config.h��Ϳ���롣
 */
#define PLLCLOCK (CLKIN*MSELVAL)
#define SYSCLOCK  (PLLCLOCK / SSELVAL)
#define CORECLOCK (PLLCLOCK / CSELVAL)



/*
 *  TIC�γ���ߥϥ�ɥ�Υ٥����ֹ�
 */
#ifdef USE_TIC_CORE
#define INHNO_TIMER INHNO_CORE_TIMER
#else
#define INHNO_TIMER INHNO_GP_TIMER2
#endif


/*
 *  ���������Ԥ��Τ�������
 *  sil_dly_nse�θƤӽФ������С��إåɤȥ롼�ץܥǥ������������
 *  nS��ɽ�����ؿ���cpu_support.asm��������Ƥ��롣
 *  SIL_DLY_TIM1��24�������롣60nS( 400MHz )
 *  SIL_DLY_TIM2��12�������롣30nS( 400MHz )
 */


#define SIL_DLY_TIM1    (24*1000000000/CORECLOCK)
#define SIL_DLY_TIM2    (12*1000000000/CORECLOCK)

/*************************************************************************
 * uart.c�ѹ����ޥ���
 */

/*  ���ꥢ��γ���ߥϥ�ɥ�Υ٥����ֹ� */
#define INHNO_SIO0_TX   INHNO_UART0_TX
#define INHNO_SIO0_RX   INHNO_UART0_RX

/*
 *  UART�쥸���������ֶ�����ADSP-BF592����¢UART��4�Х��ȼ����ǥ쥸������
 *  �¤�Ǥ���Τǡ������ˤ�4����ꤹ�롣
 */
#define UART_BOUNDARY 4

/*  UART�쥸������sil_xxb_iop()��Ȥäƥ�����������Ȥ��ˤ�UART_IOP_ACCESS�� ������롣*/
#define UART_IOP_ACCESS

/*  ���ꥢ��ݡ��ȤΥ��ɥ쥹�� */
#define UART0_ADDRESS 0xFFC00400    // ��¢UART THR�Υ��ɥ쥹��

/*  UART�Υܡ��졼�ȥ����ͥ졼�������ꤹ�٤��͡� */
#define UART0_DIVISOR   SYSCLOCK/16/UART0_BAUD_RATE

/*  ��¢UART��Ȥ����ϡ�UARTx_BLACKFIN_UCEN���������UCEN���������ʤ���Фʤ�ʤ���*/
#define UART0_BLACKFIN_UCEN


/*
 * uart.c�ѹ����ޥ��������
 *************************************************************************/



/*
 *  �����ߥ٥��ȥ��ֹ�
 *
 *  ��������ϥ���ե����졼�����ե������DEF_INH�ΰ����Ȥ��ƻȤ�
 *  SIC_ISR�ˤ�����ӥå��ֹ�Ǥ��롣
 *
 */
#define INHNO_PLL           0
#define INHNO_DMA_ERROR     1
#define INHNO_PPI_ERROR     2
#define INHNO_SPORT0_ERROR  3
#define INHNO_SPORT1_ERROR  4
#define INHNO_SPI0_ERROR    5
#define INHNO_SPI1_ERROR    6
#define INHNO_UART0_ERROR   7
#define INHNO_PPI           8
#define INHNO_SPORT0_RX     9
#define INHNO_SPORT0_TX     10
#define INHNO_SPORT1_RX     11
#define INHNO_SPORT1_TX     12
#define INHNO_SPI0          13
#define INHNO_SPI1          14
#define INHNO_UART0_RX      15
#define INHNO_UART0_TX      16
#define INHNO_PFA           17
#define INHNO_PFB           18
#define INHNO_GP_TIMER0     19
#define INHNO_GP_TIMER1     20
#define INHNO_GP_TIMER2     21
#define INHNO_PGA           22
#define INHNO_PGB           23
#define INHNO_TWI           24
#define INHNO_MEMORY_DMA0   29
#define INHNO_MEMORY_DMA1   30
#define INHNO_WDG           31

// SIC_ISR�ˤʤ��ü�ʳ�����
#define INHNO_HW_ERROR      32
#define INHNO_CORE_TIMER    33
#define INHNO_RAISE         34


/*
 *  SIC_ISR�γ����ߤΥ٥����ֹ�
 *
 *  ���������ena_int, dis_int�ΰ����Ȥ��ƻȤ���
 */

#define INTNO_PLL           0
#define INTNO_DMA_ERROR     1
#define INTNO_PPI_ERROR     2
#define INTNO_SPORT0_ERROR  3
#define INTNO_SPORT1_ERROR  4
#define INTNO_SPI0_ERROR    5
#define INTNO_SPI1_ERROR    6
#define INTNO_UART0_ERROR   7
#define INTNO_PPI           8
#define INTNO_SPORT0_RX     9
#define INTNO_SPORT0_TX     10
#define INTNO_SPORT1_RX     11
#define INTNO_SPORT1_TX     12
#define INTNO_SPI0          13
#define INTNO_SPI1          14
#define INTNO_UART0_RX      15
#define INTNO_UART0_TX      16
#define INTNO_PFA           17
#define INTNO_PFB           18
#define INTNO_GP_TIMER0     19
#define INTNO_GP_TIMER1     20
#define INTNO_GP_TIMER2     21
#define INTNO_PGA           22
#define INTNO_PGB           23
#define INTNO_TWI           24
#define INTNO_MEMORY_DMA0   29
#define INTNO_MEMORY_DMA1   30
#define INTNO_WDG           31



#ifndef _MACRO_ONLY

/*
* SIC_IARx����Ϥ��ơ����٥�Ƚ�̤��Ȥ˳�����Ƥ��Ƥ��������
* �Υӥåȥޥåפ��롣SIC_IARx�Υե�������ͤ�ͥ����-7�ʤΤ�
* ����ʬ�������롣
*/
void make_priority_mask( void );

/*
 *  �������åȥ����ƥ��¸�ν����
 */
extern void sys_initialize(void);

/*
 *  �������åȥ����ƥ�ν�λ
 *
 *  �����ƥ��λ������˻Ȥ���ROM��˥���GDB STUB�ƽФ��Ǽ¸����롥
 */
extern void sys_exit(void);

/*
 *  �������åȥ����ƥ��ʸ������
 *
 *  �����ƥ�����٥��ʸ�����ϥ롼����ROM��˥���GDB STUB�ƽФ��Ǽ�
 *  �����롥
 */
extern void sys_putc(char c);

/*
* SIC_IARx����Ϥ��ơ����٥�Ƚ�̤��Ȥ˳�����Ƥ��Ƥ��������
* �Υӥåȥޥåפ��롣SIC_IARx�Υե�������ͤ�ͥ����-7�ʤΤ�
* ����ʬ�������롣
*/
void make_priority_mask( void );

/*
 * �����ߤε��ġ��ػ�
 *
 */
typedef unsigned int INTNO;
extern ER ena_int( INTNO intno );
extern ER dis_int( INTNO intno );

/*
 * �����ߥޥ��������
 *
 *
 */
typedef unsigned int IMS;
extern ER chg_ims( IMS ims );
extern ER get_ims( IMS * p_ims );

/**
 * ���ץꥢ�������٥�ȡ��ϥ�ɥ�
 */
void spurious_exc_handler(VP p_excinf);
void spurious_int_handler();

/*
 * �����ߤ򵯤������ǥХ�����Ĵ�٤�
*/
extern void device_dispatcher(  unsigned int priority, unsigned int imask );

#endif /* _MACRO_ONLY */
#endif /* _CHIP_CONFIG_H_ */