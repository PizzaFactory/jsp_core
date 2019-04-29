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

/*
 *  ���ꥢ��I/O�ǥХ�����SIO�˥ɥ饤�С�Blackfin UART�ѡ�
 *
 *   ���Υե�����ϡ�TOPPERS/JSP 1.4.2�� config/sh3/ms7727cp01/hw_serial.h��
 *   ��͡��ष�������μ��̻Ҥ��ѹ�������ΤǤ��롣
 *
 *   ���Υե�����ϲ��̤ΥǥХ����������������롼�����«�ͤƾ�̤��ؤ��Ϥ�
 *   ����Τ�ΤǤ��롣Blackfin�γ����ˤ��륷�ꥢ���TOPPERS/JSP�Ǵ������ʤ�
 *   �Τʤ顢�ѹ�����ɬ�פϤʤ���
 */

#ifndef _HW_SERIAL_H_
#define _HW_SERIAL_H_

#include <s_services.h>

#include "uart.h"

#ifdef __GNUC__         // gcc
#include "cdefBF506F.h"
#elif defined(__ECC__)  // visualdsp
#include <cdefbf506F.h>
#else
#error "Compiler is not supported"
#endif


/*
 *  SIO�ɥ饤�Фν�����롼����
 */
#define sio_initialize  uart_initialize

#ifndef _MACRO_ONLY
/*
 *  ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
Inline SIOPCB *
sio_opn_por(ID siopid, VP_INT exinf)
{
    SIOPCB  *siopcb;
    UW regBase;

    /*
     *  �ǥХ�����¸�Υ����ץ������
     */
    siopcb = uart_opn_por(siopid, exinf);

    /*
    * Enable Corrensponding Interrupt at IMASK
    */
    regBase = siopcb->siopinib->reg_base;
    if ( regBase == UART0_ADDRESS ) {        // UART0�ξ��
        ena_int( INTNO_UART0_TX );
        ena_int( INTNO_UART0_RX );
        *pPORTG_MUX &= ~(0x3000);   // bit13:12 ������0�ˤ���
        *pPORTG_FER |= 0x3000;      // PG12,PG13��UART0�˳�꿶��
    }
    else if ( regBase == UART1_ADDRESS ){       // uart1�ξ��
        ena_int( INTNO_UART1_TX );
        ena_int( INTNO_UART1_RX );
        *pPORTH_MUX &= ~(0x00F0);               // bit7:6, bit5:4 ������0�ˤ���
        *pPORTH_MUX |= (0x01<<6) | (0x01<<4);   //  bit7:6, bit5:4 ��01�ˤ���
        *pPORTH_FER |= 0x00C0;                  // PH7,6��UART1�˳�꿶��
    }

    return(siopcb);
}

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�������
 */
Inline void
sio_cls_por(SIOPCB *siopcb)
{

    /*
     *  �ǥХ�����¸�Υ�������������
     */
    uart_cls_por(siopcb);
}


/*
 *  SIO�γ���ߥϥ�ɥ�
 */
#define sio0_rx_handler uart0_rx_isr
#define sio0_tx_handler uart0_tx_isr
#define sio1_rx_handler uart1_rx_isr
#define sio1_tx_handler uart1_tx_isr

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
#define sio_snd_chr uart_snd_chr

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
#define sio_rcv_chr uart_rcv_chr

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
#define sio_ena_cbr uart_ena_cbr

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
#define sio_dis_cbr uart_dis_cbr

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����������ǽ������Хå�
 */
#define sio_ierdy_snd   uart_ierdy_snd

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���μ������Υ�����Хå�
 */
#define sio_ierdy_rcv   uart_ierdy_rcv

#endif /* _MACRO_ONLY */
#endif /* _HW_SERIAL_H_ */