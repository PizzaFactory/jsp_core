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
 *  Copyright (C) 2004,2006,2009 by Takemasa Nakamura
 *  Copyright (C) 2004 by Ujinosuke
 *  Copyright (C) 2010,2011 by Kaneko System Co., Ltd.
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


#ifndef _CHIP_CONFIG_H_
#define _CHIP_CONFIG_H_


/*
 *  �������åȥ����ƥ��¸�⥸�塼���EZKIT-BF534,6,7�ѡ�
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�t_config.h �Τߤ��饤�󥯥롼�ɤ���롥
 *  ¾�Υե����뤫��ľ�ܥ��󥯥롼�ɤ��ƤϤʤ�ʤ���
*/

/*
 *  �������åȥ����ƥ�Υϡ��ɥ������񸻤����
 *
 *  DEVICE_INTERRUPT_COUNT��SIC_IMASK�Υӥåȿ�
 *  ��Ϳ���롣
 *  ADSP-BF506�Υӥåȿ���56�ʤΤǡ��ͤ�56�Ǥ��롣
 */

#define DEVICE_INTERRUPT_COUNT 56



/*
 *  PLL����å����ȿ�
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
#define INHNO_TIMER INHNO_TIMER7
#endif


/*
 *  ���������Ԥ��Τ�������
 *  sil_dly_nse�θƤӽФ������С��إåɤȥ롼�ץܥǥ������������
 *  nS��ɽ�����ؿ���cpu_support.asm��������Ƥ��롣
 *  SIL_DLY_TIM1��24�������롣32nS( 750MHz ), 40nS( 600MHz )
 *  SIL_DLY_TIM2��12�������롣16nS( 750MHz ), 20nS( 600MHz )
 */


#define SIL_DLY_TIM1    (24*1000000000/CORECLOCK)
#define SIL_DLY_TIM2    (12*1000000000/CORECLOCK)

/*************************************************************************
 * uart.c�ѹ����ޥ���
 */

/*  ���ꥢ��γ���ߥϥ�ɥ�Υ٥����ֹ� */
#define INHNO_SIO0_TX   INHNO_UART0_TX
#define INHNO_SIO0_RX   INHNO_UART0_RX
#define INHNO_SIO1_TX   INHNO_UART1_TX
#define INHNO_SIO1_RX   INHNO_UART1_RX

/*
 *  UART�쥸���������ֶ�����ADSP-BF506����¢UART��4�Х��ȼ����ǥ쥸������
 *  �¤�Ǥ���Τǡ������ˤ�4����ꤹ�롣
 */
#define UART_BOUNDARY 4

/*  UART�쥸������sil_xxb_iop()��Ȥäƥ�����������Ȥ��ˤ�UART_IOP_ACCESS�� ������롣*/
#define UART_IOP_ACCESS

/*  ���ꥢ��ݡ��ȤΥ��ɥ쥹�� */
#define UART0_ADDRESS 0xFFC00400    // ��¢UART0 DLL�Υ��ɥ쥹��
#define UART1_ADDRESS 0xFFC02000    // ��¢UART1 DLL�Υ��ɥ쥹��

/*  UART�Υܡ��졼�ȥ����ͥ졼�������ꤹ�٤��͡� */
#define UART0_DIVISOR   SYSCLOCK/16/UART0_BAUD_RATE
#define UART1_DIVISOR   SYSCLOCK/16/UART1_BAUD_RATE

/*  ��¢UART��Ȥ����ϡ�UARTx_BLACKFIN_UCEN���������UCEN���������ʤ���Фʤ�ʤ���*/
#define UART0_BLACKFIN_UCEN
#define UART1_BLACKFIN_UCEN


/*
 * uart.c�ѹ����ޥ������
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
#define INHNO_UART0_ERROR   5
#define INHNO_UART1_ERROR   6
#define INHNO_SPI0_ERROR    7
#define INHNO_SPI1_ERROR    8
#define INHNO_CAN_ERROR     9
#define INHNO_RSI_INT0      10
/* reserved */
#define INHNO_CNT0          12
#define INHNO_CNT1          13
#define INHNO_PPI           14
#define INHNO_RSI           15
#define INHNO_SPORT0_RX     16
#define INHNO_SPORT0_TX     17
#define INHNO_SPORT1_RX     18
#define INHNO_SPORT1_TX     19
#define INHNO_SPI0          20
#define INHNO_SPI1          21
#define INHNO_UART0_RX      22
#define INHNO_UART0_TX      23
#define INHNO_UART1_RX      24
#define INHNO_UART1_TX      25
#define INHNO_CAN_RX        26
#define INHNO_CAN_TX        27
#define INHNO_TWI           28
#define INHNO_PFA_PORT      29
#define INHNO_PFB_PORT      30
/* reserved */

#define INHNO_TIMER0        32
#define INHNO_TIMER1        33
#define INHNO_TIMER2        34
#define INHNO_TIMER3        35
#define INHNO_TIMER4        36
#define INHNO_TIMER5        37
#define INHNO_TIMER6        38
#define INHNO_TIMER7        39
#define INHNO_PFA_PORTG     40
#define INHNO_PFB_PORTG     41
#define INHNO_MDMA_DST      42
#define INHNO_MDMA_SRC      43
#define INHNO_WDOG          44
#define INHNO_PFA_PORTH     44
#define INHNO_PFB_PORTH     45
#define INHNO_ACM_ERROR     46
#define INHNO_ACM           47
/* reserved */
/* reserved */
#define INHNO_PWM0_TRIPINT  51
#define INHNO_PWM0_SYNCINT  52
#define INHN1_PWM0_TRIPINT  53
#define INHN1_PWM0_SYNCINT  54
#define INHNO_RSI_INT1      55

// SIC_ISR�ˤʤ��ü�ʳ�����
#define INHNO_HW_ERROR      56
#define INHNO_CORE_TIMER    57
#define INHNO_RAISE         58


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
#define INTNO_UART0_ERROR   5
#define INTNO_UART1_ERROR   6
#define INTNO_SPI0_ERROR    7
#define INTNO_SPI1_ERROR    8
#define INTNO_CAN_ERROR     9
#define INTNO_RSI_INT0      10
/* reserved */
#define INTNO_CNT0          12
#define INTNO_CNT1          13
#define INTNO_PPI           14
#define INTNO_RSI           15
#define INTNO_SPORT0_RX     16
#define INTNO_SPORT0_TX     17
#define INTNO_SPORT1_RX     18
#define INTNO_SPORT1_TX     19
#define INTNO_SPI0          20
#define INTNO_SPI1          21
#define INTNO_UART0_RX      22
#define INTNO_UART0_TX      23
#define INTNO_UART1_RX      24
#define INTNO_UART1_TX      25
#define INTNO_CAN_RX        26
#define INTNO_CAN_TX        27
#define INTNO_TWI           28
#define INTNO_PFA_PORT      29
#define INTNO_PFB_PORT      30
/* reserved */

#define INTNO_TIMER0        32
#define INTNO_TIMER1        33
#define INTNO_TIMER2        34
#define INTNO_TIMER3        35
#define INTNO_TIMER4        36
#define INTNO_TIMER5        37
#define INTNO_TIMER6        38
#define INTNO_TIMER7        39
#define INTNO_PFA_PORTG     40
#define INTNO_PFB_PORTG     41
#define INTNO_MDMA_DST      42
#define INTNO_MDMA_SRC      43
#define INTNO_WDOG          44
#define INTNO_PFA_PORTH     44
#define INTNO_PFB_PORTH     45
#define INTNO_ACM_ERROR     46
#define INTNO_ACM           47
/* reserved */
/* reserved */
#define INTNO_PWM0_TRIPINT  51
#define INTNO_PWM0_SYNCINT  52
#define INHN1_PWM0_TRIPINT  53
#define INHN1_PWM0_SYNCINT  54
#define INTNO_RSI_INT1      55

// SIC_ISR�ˤʤ��ü�ʳ�����
#define INTNO_HW_ERROR      56
#define INTNO_CORE_TIMER    57
#define INTNO_RAISE         58

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
typedef unsigned long long int IMS;
extern ER chg_ims( IMS ims );
extern ER get_ims( IMS * p_ims );

/*
 *  �����ߤ�ǥХ����˳�����Ƥ�
 */
extern void device_dispatcher( unsigned int priority, unsigned int imask );

/**
 * ���ץꥢ�������٥�ȡ��ϥ�ɥ�
 */
void spurious_exc_handler(VP p_excinf);
void spurious_int_handler();

#endif /* _MACRO_ONLY */
#endif /* _SYS_CONFIG_H_ */
