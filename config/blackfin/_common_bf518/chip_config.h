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
 *  ADSP-BF518�Υӥåȿ���56�ʤΤǡ��ͤ�56�Ǥ��롣
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
 *  UART�쥸���������ֶ�����ADSP-BF518����¢UART��4�Х��ȼ����ǥ쥸������
 *  �¤�Ǥ���Τǡ������ˤ�4����ꤹ�롣
 */
#define UART_BOUNDARY 4

/*  UART�쥸������sil_xxb_iop()��Ȥäƥ�����������Ȥ��ˤ�UART_IOP_ACCESS�� ������롣*/
#define UART_IOP_ACCESS

/*  ���ꥢ��ݡ��ȤΥ��ɥ쥹�� */
#define UART0_ADDRESS 0xFFC00400    // ��¢UART0 THR�Υ��ɥ쥹��
#define UART1_ADDRESS 0xFFC02000    // ��¢UART0 THR�Υ��ɥ쥹��

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

/* Peripheral Masks For SIC_ISR0, SIC_IWR0, SIC_IMASK0 */
#define INHNO_PLL_WAKEUP        0   /* PLL Wakeup Interrupt                             */
#define INHNO_DMA_ERR0          1  /* Error Interrupt (DMA error 0 interrupt (generic))             */
#define INHNO_DMAR0             2  /* DMAR0 Block (DMAR0 block interrupt)                   */
#define INHNO_DMAR1             3  /* DMAR1 Block  (DMAR1 block interrupt)                  */
#define INHNO_DMAR0_ERR         4  /* Error Interrupt (DMAR0 overflow error interrupt)              */
#define INHNO_DMAR1_ERR         5  /* Error Interrupt (DMAR1 overflow error interrupt)              */
#define INHNO_PPI_ERR           6  /* Error Interrupt (PPI error interrupt)                     */
#define INHNO_MAC_ERR           7  /* Error Interrupt (MAC status interrupt)                */
#define INHNO_SPORT0_ERR        8  /* Error Interrupt (SPORT0 status interrupt)                 */
#define INHNO_SPORT1_ERR        9  /* Error Interrupt (SPORT1 status interrupt)                 */
#define INHNO_PTP_ERR           10  /* Error Interrupt (PTP error interrupt)                    */
/* reserved */
#define INHNO_UART0_ERR         12  /* Error Interrupt (UART0 status interrupt)                 */
#define INHNO_UART1_ERR         13  /* Error Interrupt (UART1 status interrupt)                 */
#define INHNO_RTC               14  /* Real Time Clock Interrupt                            */
#define INHNO_PPI               15  /* DMA channel 0 (PPI/NFC) Interrupt                    */
#define INHNO_SPORT0_RX     16  /* DMA Channel 3 (SPORT0 RX) Interrupt                  */
#define INHNO_SPORT0_TX     17  /* DMA Channel 4 (SPORT0 TX) Interrupt                  */
#define INHNO_SPORT1_RX     18  /* DMA Channel 5 (SPORT1 RX) Interrupt                  */
#define INHNO_SPORT1_TX     19  /* DMA Channel 6 (SPORT1 TX) Interrupt                  */
#define INHNO_TWI               20  /* TWI Interrupt                                    */
#define INHNO_SPI               21  /* DMA Channel 7 (SPI) Interrupt                        */
#define INHNO_UART0_RX          22  /* DMA Channel 8 (UART0 RX) Interrupt                   */
#define INHNO_UART0_TX          23  /* DMA Channel 9 (UART0 TX) Interrupt                   */
#define INHNO_UART1_RX          24  /* DMA Channel 10 (UART1 RX) Interrupt                  */
#define INHNO_UART1_TX          25  /* DMA Channel 11 (UART1 TX) Interrupt                  */
#define INHNO_OTP               26  /* OTP Interrupt                                    */
#define INHNO_CNT           27  /* GP Counter Interrupt                             */
#define INHNO_ETHERNET_RX       28  /* DMA Channel 1 (EthernetRX/HOSTDP) Interrupt              */
#define INHNO_PFA_PORTH         29  /* PF Port H Interrupt A                            */
#define INHNO_ETHERNET_TX       30  /* DMA Channel 2 (Ethernet TX/NFC) Interrupt                */
#define INHNO_PFB_PORTH         31  /* PF Port H  Interrupt B                           */

/* Peripheral Masks For SIC_ISR1, SIC_IWR1, SIC_IMASK1 */
#define INHNO_TIMER0            32  /* Timer 0 Interrupt                                */
#define INHNO_TIMER1            33  /* Timer 1 Interrupt                                */
#define INHNO_TIMER2            34  /* Timer 2 Interrupt                                */
#define INHNO_TIMER3            35  /* Timer 3 Interrupt                                */
#define INHNO_TIMER4            36  /* Timer 4 Interrupt                                */
#define INHNO_TIMER5            37  /* Timer 5 Interrupt                                */
#define INHNO_TIMER6            38  /* Timer 6 Interrupt                                */
#define INHNO_TIMER7            39  /* Timer 7 Interrupt                                */
#define INHNO_PFA_PORTG     40  /* PF Port G Interrupt A                            */
#define INHNO_PFB_PORTG     41  /* PF Port G Interrupt B                            */
#define INHNO_MDMA0_DST     42  /* DMA Channels 12 (MDMA0 Destination) TX Interrupt         */
#define INHNO_MDMA0_SRC     42  /* DMA Channels 13 (MDMA0 Source) RX Interrupt              */
#define INHNO_MDMA1_DST     43  /* DMA Channels 14 (MDMA1 Destination) TX Interrupt         */
#define INHNO_MDMA1_SRC     43  /* DMA Channels 15 (MDMA1 Source) RX Interrupt              */
#define INHNO_WDOG              44  /* Software Watchdog Timer Interrupt                    */
#define INHNO_PFA_PORTF     45  /* PF Port F Interrupt A                            */
#define INHNO_PFB_PORTF     46  /* PF Port F Interrupt B                            */
#define INHNO_SPI0_ERR      47  /* Error Interrupt (SPI0 status interrupt)              */
#define INHNO_SPI1_ERR          48  /* Error Interrupt (SPI1 status interrupt)              */
/* reserved */
/* reserved */
#define INHNO_RSI_INT0          51  /* USB EINT interrupt                               */
#define INHNO_RSI_INT1          52  /* USB INT0 interrupt                               */
#define INHNO_PWM_TRIPINT       53  /* USB INT1 interrupt                               */
#define INHNO_PWM_SYNCINT       54  /* USB INT1 interrupt                               */
#define INHNO_PTP_STATINT       55  /* USB DMAINT interrupt                             */


// SIC_ISR�ˤʤ��ü�ʳ�����

#define INHNO_HW_ERROR      56
#define INHNO_CORE_TIMER    57
#define INHNO_RAISE         58


/*
 *  SIC_ISR�γ����ߤΥ٥����ֹ�
 *
 *  ���������ena_int, dis_int�ΰ����Ȥ��ƻȤ���
 */

/* Peripheral Masks For SIC_ISR0, SIC_IWR0, SIC_IMASK0 */
#define INTNO_PLL_WAKEUP        0   /* PLL Wakeup Interrupt                             */
#define INTNO_DMA_ERR0          1  /* Error Interrupt (DMA error 0 interrupt (generic))             */
#define INTNO_DMAR0             2  /* DMAR0 Block (DMAR0 block interrupt)                   */
#define INTNO_DMAR1             3  /* DMAR1 Block  (DMAR1 block interrupt)                  */
#define INTNO_DMAR0_ERR         4  /* Error Interrupt (DMAR0 overflow error interrupt)              */
#define INTNO_DMAR1_ERR         5  /* Error Interrupt (DMAR1 overflow error interrupt)              */
#define INTNO_PPI_ERR           6  /* Error Interrupt (PPI error interrupt)                     */
#define INTNO_MAC_ERR           7  /* Error Interrupt (MAC status interrupt)                */
#define INTNO_SPORT0_ERR        8  /* Error Interrupt (SPORT0 status interrupt)                 */
#define INTNO_SPORT1_ERR        9  /* Error Interrupt (SPORT1 status interrupt)                 */
#define INTNO_PTP_ERR           10  /* Error Interrupt (PTP error interrupt)                    */
/* reserved */
#define INTNO_UART0_ERR         12  /* Error Interrupt (UART0 status interrupt)                 */
#define INTNO_UART1_ERR         13  /* Error Interrupt (UART1 status interrupt)                 */
#define INTNO_RTC               14  /* Real Time Clock Interrupt                            */
#define INTNO_PPI               15  /* DMA channel 0 (PPI/NFC) Interrupt                    */
#define INTNO_SPORT0_RX     16  /* DMA Channel 3 (SPORT0 RX) Interrupt                  */
#define INTNO_SPORT0_TX     17  /* DMA Channel 4 (SPORT0 TX) Interrupt                  */
#define INTNO_SPORT1_RX     18  /* DMA Channel 5 (SPORT1 RX) Interrupt                  */
#define INTNO_SPORT1_TX     19  /* DMA Channel 6 (SPORT1 TX) Interrupt                  */
#define INTNO_TWI               20  /* TWI Interrupt                                    */
#define INTNO_SPI               21  /* DMA Channel 7 (SPI) Interrupt                        */
#define INTNO_UART0_RX          22  /* DMA Channel 8 (UART0 RX) Interrupt                   */
#define INTNO_UART0_TX          23  /* DMA Channel 9 (UART0 TX) Interrupt                   */
#define INTNO_UART1_RX          24  /* DMA Channel 10 (UART1 RX) Interrupt                  */
#define INTNO_UART1_TX          25  /* DMA Channel 11 (UART1 TX) Interrupt                  */
#define INTNO_OTP               26  /* OTP Interrupt                                    */
#define INTNO_CNT           27  /* GP Counter Interrupt                             */
#define INTNO_ETHERNET_RX       28  /* DMA Channel 1 (EthernetRX/HOSTDP) Interrupt              */
#define INTNO_PFA_PORTH         29  /* PF Port H Interrupt A                            */
#define INTNO_ETHERNET_TX       30  /* DMA Channel 2 (Ethernet TX/NFC) Interrupt                */
#define INTNO_PFB_PORTH         31  /* PF Port H  Interrupt B                           */

/* Peripheral Masks For SIC_ISR1, SIC_IWR1, SIC_IMASK1 */
#define INTNO_TIMER0            32  /* Timer 0 Interrupt                                */
#define INTNO_TIMER1            33  /* Timer 1 Interrupt                                */
#define INTNO_TIMER2            34  /* Timer 2 Interrupt                                */
#define INTNO_TIMER3            35  /* Timer 3 Interrupt                                */
#define INTNO_TIMER4            36  /* Timer 4 Interrupt                                */
#define INTNO_TIMER5            37  /* Timer 5 Interrupt                                */
#define INTNO_TIMER6            38  /* Timer 6 Interrupt                                */
#define INTNO_TIMER7            39  /* Timer 7 Interrupt                                */
#define INTNO_PFA_PORTG     40  /* PF Port G Interrupt A                            */
#define INTNO_PFB_PORTG     41  /* PF Port G Interrupt B                            */
#define INTNO_MDMA0_DST     42  /* DMA Channels 12 (MDMA0 Destination) TX Interrupt         */
#define INTNO_MDMA0_SRC     42  /* DMA Channels 13 (MDMA0 Source) RX Interrupt              */
#define INTNO_MDMA1_DST     43  /* DMA Channels 14 (MDMA1 Destination) TX Interrupt         */
#define INTNO_MDMA1_SRC     43  /* DMA Channels 15 (MDMA1 Source) RX Interrupt              */
#define INTNO_WDOG              44  /* Software Watchdog Timer Interrupt                    */
#define INTNO_PFA_PORTF     45  /* PF Port F Interrupt A                            */
#define INTNO_PFB_PORTF     46  /* PF Port F Interrupt B                            */
#define INTNO_SPI0_ERR      47  /* Error Interrupt (SPI0 status interrupt)              */
#define INTNO_SPI1_ERR          48  /* Error Interrupt (SPI1 status interrupt)              */
/* reserved */
/* reserved */
#define INTNO_RSI_INT0          51  /* USB EINT interrupt                               */
#define INTNO_RSI_INT1          52  /* USB INT0 interrupt                               */
#define INTNO_PWM_TRIPINT       53  /* USB INT1 interrupt                               */
#define INTNO_PWM_SYNCINT       54  /* USB INT1 interrupt                               */
#define INTNO_PTP_STATINT       55  /* USB DMAINT interrupt                             */



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
