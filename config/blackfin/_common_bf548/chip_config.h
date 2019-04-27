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
 *  ADSP-BF548�Υӥåȿ���96�ʤΤǡ��ͤ�96�Ǥ��롣
 */

#define DEVICE_INTERRUPT_COUNT 96



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
 *  UART�쥸���������ֶ�����ADSP-BF548����¢UART��4�Х��ȼ����ǥ쥸������
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

/* Peripheral Masks For SIC_ISR0, SIC_IWR0, SIC_IMASK0 */
#define INHNO_PLL_WAKEUP        0  /* PLL Wakeup Interrupt */
#define INHNO_DMA0_ERR          1  /* DMA Controller 0 Error */
#define INHNO_EPPI0_ERR         2  /* EPPI0 Error */
#define INHNO_SPORT0_ERR        3  /* SPORT0 Error */
#define INHNO_SPORT1_ERR        4  /* SPORT1 Error */
#define INHNO_SPI0_ERR          5  /* SPI0 Error */
#define INHNO_UART0_ERR         6  /* UART0 Error */
#define INHNO_RTC               7  /* Real-Time Clock */
#define INHNO_DMA12             8  /* DMA Channel 12 (EPPI0) */
#define INHNO_EPPI0             8  /* DMA Channel 12 (EPPI0) */
#define INHNO_DMA0              9  /* DMA Channel 0 (SPORT0 RX) */
#define INHNO_SPORT0_RX         9  /* DMA Channel 0 (SPORT0 RX) */
#define INHNO_DMA1              10 /* DMA Channel 1 (SPORT0 TX) */
#define INHNO_SPORT0_TX         10 /* DMA Channel 1 (SPORT0 TX) */
#define INHNO_DMA2              11 /* DMA Channel 2 (SPORT1 RX) */
#define INHNO_SPORT1_RX         11 /* DMA Channel 2 (SPORT1 RX) */
#define INHNO_DMA3              12 /* DMA Channel 3 (SPORT1 TX) */
#define INHNO_SPORT1_TX         12 /* DMA Channel 3 (SPORT1 TX) */
#define INHNO_DMA4              13 /* DMA Channel 4 (SPI0) */
#define INHNO_SPI0              13 /* DMA Channel 4 (SPI0) */
#define INHNO_DMA6              14 /* DMA Channel 6 (UART0 RX) */
#define INHNO_UART0_RX          14 /* DMA Channel 6 (UART0 RX) */
#define INHNO_DMA7              15 /* DMA Channel 7 (UART0 TX) */
#define INHNO_UART0_TX          15 /* DMA Channel 7 (UART0 TX) */
#define INHNO_TIMER8            16 /* Timer 8 */
#define INHNO_TIMER9            17 /* Timer 9 */
#define INHNO_TIMER10           18 /* Timer 10 */
#define INHNO_PINT0             19 /* Pin Interrupt 0 */
#define INHNO_PINT1             20 /* Pin Interrupt 1 */
#define INHNO_MDMA0             21 /* Memory DMA Stream 0 */
#define INHNO_MDMA1             22 /* Memory DMA Stream 1 */
#define INHNO_WDOG              23 /* Watchdog Timer */
#define INHNO_DMA1_ERR          24 /* DMA Controller 1 Error */
#define INHNO_SPORT2_ERR        25 /* SPORT2 Error */
#define INHNO_SPORT3_ERR        26 /* SPORT3 Error */
#define INHNO_MXVR_SD           27 /* MXVR Synchronous Data */
#define INHNO_SPI1_ERR          28 /* SPI1 Error */
#define INHNO_SPI2_ERR          29 /* SPI2 Error */
#define INHNO_UART1_ERR         30 /* UART1 Error */
#define INHNO_UART2_ERR         31 /* UART2 Error */

/* Peripheral Masks For SIC_ISR1, SIC_IWR1, SIC_IMASK1 */
#define INHNO_CAN0_ERR          32 /* CAN0 Error */
#define INHNO_DMA18             33 /* DMA Channel 18 (SPORT2 RX) */
#define INHNO_SPORT2_RX         33 /* DMA Channel 18 (SPORT2 RX) */
#define INHNO_DMA19             34 /* DMA Channel 19 (SPORT2 TX) */
#define INHNO_SPORT2_TX         34 /* DMA Channel 19 (SPORT2 TX) */
#define INHNO_DMA20             35 /* DMA Channel 20 (SPORT3 RX) */
#define INHNO_SPORT3_RX         35 /* DMA Channel 20 (SPORT3 RX) */
#define INHNO_DMA21             36 /* DMA Channel 21 (SPORT3 TX) */
#define INHNO_SPORT3_TX         36 /* DMA Channel 21 (SPORT3 TX) */
#define INHNO_DMA13             37 /* DMA Channel 13 (EPPI1) */
#define INHNO_EPPI1             37 /* DMA Channel 13 (EPPI1) */
#define INHNO_DMA14             38 /* DMA Channel 14 (EPPI2, HOSTDP) */
#define INHNO_EPPI2             38 /* DMA Channel 14 (EPPI2, HOSTDP) */
#define INHNO_HOSTDP            38 /* DMA Channel 14 (EPPI2, HOSTDP) */
#define INHNO_DMA5              39 /* DMA Channel 5 (SPI1) */
#define INHNO_SPI1              39 /* DMA Channel 5 (SPI1) */
#define INHNO_DMA23             40 /* DMA Channel 23 (SPI2) */
#define INHNO_SPI2              40 /* DMA Channel 23 (SPI2) */
#define INHNO_DMA8              41 /* DMA Channel 8 (UART1 RX) */
#define INHNO_UART1_RX          41 /* DMA Channel 8 (UART1 RX) */
#define INHNO_DMA9              42 /* DMA Channel 9 (UART1 TX) */
#define INHNO_UART1_TX          42 /* DMA Channel 9 (UART1 TX) */
#define INHNO_DMA10             43 /* DMA Channel 10 (ATAPI RX) */
#define INHNO_ATAPI_RX          43 /* DMA Channel 10 (ATAPI RX) */
#define INHNO_DMA11             44 /* DMA Channel 11 (ATAPI TX) */
#define INHNO_ATAPI_TX          44 /* DMA Channel 11 (ATAPI TX) */
#define INHNO_TWI0              45 /* TWI0 */
#define INHNO_TWI1              46 /* TWI1 */
#define INHNO_CAN0_RX           47 /* CAN0 Receive */
#define INHNO_CAN0_TX           48 /* CAN0 Transmit */
#define INHNO_MDMA2             49 /* Memory DMA Stream 0 */
#define INHNO_MDMA3             50 /* Memory DMA Stream 1 */
#define INHNO_MXVR_STAT         51 /* MXVR Status */
#define INHNO_MXVR_CM           52 /* MXVR Control Message */
#define INHNO_MXVR_AP           53 /* MXVR Asynchronous Packet */
#define INHNO_EPPI1_ERR         54 /* EPPI1 Error */
#define INHNO_EPPI2_ERR         55 /* EPPI2 Error */
#define INHNO_UART3_ERR         56 /* UART3 Error */
#define INHNO_HOSTDP_STATUS     57 /* Host DMA Port Error */
/* reserved */
#define INHNO_PIXC_ERR          59 /* Pixel Compositor Error */
#define INHNO_NFC_ERR           60 /* Nand Flash Controller Error */
#define INHNO_ATAPI_ERR         61 /* ATAPI Error */
#define INHNO_CAN1_ERR          62 /* CAN1 Error */
#define INHNO_DMAR0_ERR         63 /* DMAR0 Overflow Error */
#define INHNO_DMAR1_ERR         63 /* DMAR1 Overflow Error */
#define INHNO_DMAR0             63 /* DMAR0 Block */
#define INHNO_DMAR1             63 /* DMAR1 Block */

/* Peripheral Masks For SIC_ISR2, SIC_IWR2, SIC_IMASK2 */
#define INHNO_DMA15             64 /* DMA Channel 15 (PIXC IN0) */
#define INHNO_PIXC_IN0          64 /* DMA Channel 15 (PIXC IN0) */
#define INHNO_DMA16             65 /* DMA Channel 16 (PIXC IN1) */
#define INHNO_PIXC_IN1          65 /* DMA Channel 16 (PIXC IN1) */
#define INHNO_DMA17             66 /* DMA Channel 17 (PIXC OUT) */
#define INHNO_PIXC_OUT          66 /* DMA Channel 17 (PIXC OUT) */
#define INHNO_DMA22             67 /* DMA Channel 22 (SHD/NFC) */
#define INHNO_SDH               67 /* DMA Channel 22 (SHD/NFC) */
#define INHNO_NFC               67 /* DMA Channel 22 (SHD/NFC) */
#define INHNO_CNT               68 /* Counter */
#define INHNO_KEY               69 /* Keypad */
#define INHNO_CAN1_RX           70 /* CAN1 Receive */
#define INHNO_CAN1_TX           71 /* CAN1 Transmit */
#define INHNO_SDH_MASK0         72 /* SDH Mask 0 */
#define INHNO_SDH_MASK1         73 /* SDH Mask 1 */
/* reserved */
#define INHNO_USB_INT0          75 /* USB Interrupt 0 */
#define INHNO_USB_INT1          76 /* USB Interrupt 1 */
#define INHNO_USB_INT2          77 /* USB Interrupt 2 */
#define INHNO_USB_DMAINT        78 /* USB DMA */
#define INHNO_OTP               79 /* OTP Access Complete */
/* reserved */
/* reserved */
/* reserved */
/* reserved */
/* reserved */
/* reserved */
#define INHNO_TIMER0            86 /* Timer 0 */
#define INHNO_TIMER1            87 /* Timer 1 */
#define INHNO_TIMER2            88 /* Timer 2 */
#define INHNO_TIMER3            89 /* Timer 3 */
#define INHNO_TIMER4            90 /* Timer 4 */
#define INHNO_TIMER5            91 /* Timer 5 */
#define INHNO_TIMER6            92 /* Timer 6 */
#define INHNO_TIMER7            93 /* Timer 7 */
#define INHNO_PINT2             94 /* Pin Interrupt 2 */
#define INHNO_PINT3             95 /* Pin Interrupt 3 */


// SIC_ISR�ˤʤ��ü�ʳ�����

#define INHNO_HW_ERROR      96
#define INHNO_CORE_TIMER    97
#define INHNO_RAISE         98


/*
 *  SIC_ISR�γ����ߤΥ٥����ֹ�
 *
 *  ���������ena_int, dis_int�ΰ����Ȥ��ƻȤ���
 */

/* Peripheral Masks For SIC_ISR0, SIC_IWR0, SIC_IMASK0 */
#define INTNO_PLL_WAKEUP        0  /* PLL Wakeup Interrupt */
#define INTNO_DMA0_ERR          1  /* DMA Controller 0 Error */
#define INTNO_EPPI0_ERR         2  /* EPPI0 Error */
#define INTNO_SPORT0_ERR        3  /* SPORT0 Error */
#define INTNO_SPORT1_ERR        4  /* SPORT1 Error */
#define INTNO_SPI0_ERR          5  /* SPI0 Error */
#define INTNO_UART0_ERR         6  /* UART0 Error */
#define INTNO_RTC               7  /* Real-Time Clock */
#define INTNO_DMA12             8  /* DMA Channel 12 (EPPI0) */
#define INTNO_EPPI0             8  /* DMA Channel 12 (EPPI0) */
#define INTNO_DMA0              9  /* DMA Channel 0 (SPORT0 RX) */
#define INTNO_SPORT0_RX         9  /* DMA Channel 0 (SPORT0 RX) */
#define INTNO_DMA1              10 /* DMA Channel 1 (SPORT0 TX) */
#define INTNO_SPORT0_TX         10 /* DMA Channel 1 (SPORT0 TX) */
#define INTNO_DMA2              11 /* DMA Channel 2 (SPORT1 RX) */
#define INTNO_SPORT1_RX         11 /* DMA Channel 2 (SPORT1 RX) */
#define INTNO_DMA3              12 /* DMA Channel 3 (SPORT1 TX) */
#define INTNO_SPORT1_TX         12 /* DMA Channel 3 (SPORT1 TX) */
#define INTNO_DMA4              13 /* DMA Channel 4 (SPI0) */
#define INTNO_SPI0              13 /* DMA Channel 4 (SPI0) */
#define INTNO_DMA6              14 /* DMA Channel 6 (UART0 RX) */
#define INTNO_UART0_RX          14 /* DMA Channel 6 (UART0 RX) */
#define INTNO_DMA7              15 /* DMA Channel 7 (UART0 TX) */
#define INTNO_UART0_TX          15 /* DMA Channel 7 (UART0 TX) */
#define INTNO_TIMER8            16 /* Timer 8 */
#define INTNO_TIMER9            17 /* Timer 9 */
#define INTNO_TIMER10           18 /* Timer 10 */
#define INTNO_PINT0             19 /* Pin Interrupt 0 */
#define INTNO_PINT1             20 /* Pin Interrupt 1 */
#define INTNO_MDMA0             21 /* Memory DMA Stream 0 */
#define INTNO_MDMA1             22 /* Memory DMA Stream 1 */
#define INTNO_WDOG              23 /* Watchdog Timer */
#define INTNO_DMA1_ERR          24 /* DMA Controller 1 Error */
#define INTNO_SPORT2_ERR        25 /* SPORT2 Error */
#define INTNO_SPORT3_ERR        26 /* SPORT3 Error */
#define INTNO_MXVR_SD           27 /* MXVR Synchronous Data */
#define INTNO_SPI1_ERR          28 /* SPI1 Error */
#define INTNO_SPI2_ERR          29 /* SPI2 Error */
#define INTNO_UART1_ERR         30 /* UART1 Error */
#define INTNO_UART2_ERR         31 /* UART2 Error */

/* Peripheral Masks For SIC_ISR1, SIC_IWR1, SIC_IMASK1 */
#define INTNO_CAN0_ERR          32 /* CAN0 Error */
#define INTNO_DMA18             33 /* DMA Channel 18 (SPORT2 RX) */
#define INTNO_SPORT2_RX         33 /* DMA Channel 18 (SPORT2 RX) */
#define INTNO_DMA19             34 /* DMA Channel 19 (SPORT2 TX) */
#define INTNO_SPORT2_TX         34 /* DMA Channel 19 (SPORT2 TX) */
#define INTNO_DMA20             35 /* DMA Channel 20 (SPORT3 RX) */
#define INTNO_SPORT3_RX         35 /* DMA Channel 20 (SPORT3 RX) */
#define INTNO_DMA21             36 /* DMA Channel 21 (SPORT3 TX) */
#define INTNO_SPORT3_TX         36 /* DMA Channel 21 (SPORT3 TX) */
#define INTNO_DMA13             37 /* DMA Channel 13 (EPPI1) */
#define INTNO_EPPI1             37 /* DMA Channel 13 (EPPI1) */
#define INTNO_DMA14             38 /* DMA Channel 14 (EPPI2, HOSTDP) */
#define INTNO_EPPI2             38 /* DMA Channel 14 (EPPI2, HOSTDP) */
#define INTNO_HOSTDP            38 /* DMA Channel 14 (EPPI2, HOSTDP) */
#define INTNO_DMA5              39 /* DMA Channel 5 (SPI1) */
#define INTNO_SPI1              39 /* DMA Channel 5 (SPI1) */
#define INTNO_DMA23             40 /* DMA Channel 23 (SPI2) */
#define INTNO_SPI2              40 /* DMA Channel 23 (SPI2) */
#define INTNO_DMA8              41 /* DMA Channel 8 (UART1 RX) */
#define INTNO_UART1_RX          41 /* DMA Channel 8 (UART1 RX) */
#define INTNO_DMA9              42 /* DMA Channel 9 (UART1 TX) */
#define INTNO_UART1_TX          42 /* DMA Channel 9 (UART1 TX) */
#define INTNO_DMA10             43 /* DMA Channel 10 (ATAPI RX) */
#define INTNO_ATAPI_RX          43 /* DMA Channel 10 (ATAPI RX) */
#define INTNO_DMA11             44 /* DMA Channel 11 (ATAPI TX) */
#define INTNO_ATAPI_TX          44 /* DMA Channel 11 (ATAPI TX) */
#define INTNO_TWI0              45 /* TWI0 */
#define INTNO_TWI1              46 /* TWI1 */
#define INTNO_CAN0_RX           47 /* CAN0 Receive */
#define INTNO_CAN0_TX           48 /* CAN0 Transmit */
#define INTNO_MDMA2             49 /* Memory DMA Stream 0 */
#define INTNO_MDMA3             50 /* Memory DMA Stream 1 */
#define INTNO_MXVR_STAT         51 /* MXVR Status */
#define INTNO_MXVR_CM           52 /* MXVR Control Message */
#define INTNO_MXVR_AP           53 /* MXVR Asynchronous Packet */
#define INTNO_EPPI1_ERR         54 /* EPPI1 Error */
#define INTNO_EPPI2_ERR         55 /* EPPI2 Error */
#define INTNO_UART3_ERR         56 /* UART3 Error */
#define INTNO_HOSTDP_STATUS     57 /* Host DMA Port Error */
/* reserved */
#define INTNO_PIXC_ERR          59 /* Pixel Compositor Error */
#define INTNO_NFC_ERR           60 /* Nand Flash Controller Error */
#define INTNO_ATAPI_ERR         61 /* ATAPI Error */
#define INTNO_CAN1_ERR          62 /* CAN1 Error */
#define INTNO_DMAR0_ERR         63 /* DMAR0 Overflow Error */
#define INTNO_DMAR1_ERR         63 /* DMAR1 Overflow Error */
#define INTNO_DMAR0             63 /* DMAR0 Block */
#define INTNO_DMAR1             63 /* DMAR1 Block */

/* Peripheral Masks For SIC_ISR2, SIC_IWR2, SIC_IMASK2 */
#define INTNO_DMA15             64 /* DMA Channel 15 (PIXC IN0) */
#define INTNO_PIXC_IN0          64 /* DMA Channel 15 (PIXC IN0) */
#define INTNO_DMA16             65 /* DMA Channel 16 (PIXC IN1) */
#define INTNO_PIXC_IN1          65 /* DMA Channel 16 (PIXC IN1) */
#define INTNO_DMA17             66 /* DMA Channel 17 (PIXC OUT) */
#define INTNO_PIXC_OUT          66 /* DMA Channel 17 (PIXC OUT) */
#define INTNO_DMA22             67 /* DMA Channel 22 (SHD/NFC) */
#define INTNO_SDH               67 /* DMA Channel 22 (SHD/NFC) */
#define INTNO_NFC               67 /* DMA Channel 22 (SHD/NFC) */
#define INTNO_CNT               68 /* Counter */
#define INTNO_KEY               69 /* Keypad */
#define INTNO_CAN1_RX           70 /* CAN1 Receive */
#define INTNO_CAN1_TX           71 /* CAN1 Transmit */
#define INTNO_SDH_MASK0         72 /* SDH Mask 0 */
#define INTNO_SDH_MASK1         73 /* SDH Mask 1 */
/* reserved */
#define INTNO_USB_INT0          75 /* USB Interrupt 0 */
#define INTNO_USB_INT1          76 /* USB Interrupt 1 */
#define INTNO_USB_INT2          77 /* USB Interrupt 2 */
#define INTNO_USB_DMAINT        78 /* USB DMA */
#define INTNO_OTP               79 /* OTP Access Complete */
/* reserved */
/* reserved */
/* reserved */
/* reserved */
/* reserved */
/* reserved */
#define INTNO_TIMER0            86 /* Timer 0 */
#define INTNO_TIMER1            87 /* Timer 1 */
#define INTNO_TIMER2            88 /* Timer 2 */
#define INTNO_TIMER3            89 /* Timer 3 */
#define INTNO_TIMER4            90 /* Timer 4 */
#define INTNO_TIMER5            91 /* Timer 5 */
#define INTNO_TIMER6            92 /* Timer 6 */
#define INTNO_TIMER7            93 /* Timer 7 */
#define INTNO_PINT2             94 /* Pin Interrupt 2 */
#define INTNO_PINT3             95 /* Pin Interrupt 3 */

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
typedef struct
{
    unsigned int imask[3];
} IMS;
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
