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

/*
 *  �������åȥ����ƥ��¸�⥸�塼���ADSP-BF548�ѡ�
 */

#include "jsp_kernel.h"
#include <sil.h>

#ifdef __GNUC__
#include <cdefBF548.h>      /* gnu tool chain */
#elif defined(__ECC__)
#include <cdefbf548.h>              /* VisualDSP++ */
#include <ccblkfn.h>
#include <sysreg.h>
#else
#error "Compiler is not supported"
#endif




/*
 *  �������åȥ����ƥ��¸�ν����
 */
void
sys_initialize()
{
    /*
     * ���ץꥢ�������ߥϥ�ɥ������
     *
     * cpu_initialize()���Ԥ����ߡ��γ����ߥϥ�ɥ��������񤭤��롣
     * ���ץꥱ������󤬳����ߥϥ�ɥ�����ꤹ��ȡ��ʲ����������
     * ����롣
     */
    int i;

    for ( i=0; i<DEVICE_INTERRUPT_COUNT+3; i++ )
        dev_vector[i] = &spurious_int_handler;

    exc_vector = &spurious_exc_handler;

    /*
     *  PLL������
     *
     */
    /*
     *  SSELVAL, CSELVAL��board_config.h�ˤ������FORCE_PLL_INITIALIZE��sys_config.h��
     *  ɬ�פ˱�����������롣
     */
#ifndef FORCE_PLL_INITIALIZE
        // PLL������ͤΤޤޤǤ��ꡢ���ġ�DDR-SDRAM��������Ǥʤ����PLL����������
     if ( ( *pPLL_CTL == 0x1000 ) && ( !(*pEBIU_RSTCTL & DDRSRESET ) ) )
#endif
     {

        *pSIC_IWR0 = IWR_ENABLE(0);             // PLL�Τ�IWR�����
#if CSELVAL == 1
        *pPLL_DIV = CSEL_DIV1 | SET_SSEL(SSELVAL);
#elif CSELVAL == 2
        *pPLL_DIV = CSEL_DIV2 | SET_SSEL(SSELVAL);
#elif CSELVAL == 4
        *pPLL_DIV = CSEL_DIV4 | SET_SSEL(SSELVAL);
#elif CSELVAL == 8
        *pPLL_DIV = CSEL_DIV8 | SET_SSEL(SSELVAL);
#else
#error Wrong CSELVAL. Must be one of 1,2,4,8.
#endif
                // PLL��ʬ������ͤ����ꤹ��
        *pPLL_CTL = MSELVAL << 9;

                // PLL��ư���롣
        asm("cli r0; csync; idle; sti r0;": : :"R0");
        *pSIC_IWR0 = IWR_ENABLE_ALL;
    }

    /*
     *  UARTʬ���������
     *
     *  Logtask��ư�������sys_putc()��Ȥ�����������Ԥ����ʲ��������
     *  serial��Ϣ�Υ���������ư�����Ȥ��˾�񤭤���롣
     */
#define DLAB 0x80
#if 0
    /* Blackfin ��ͭ�����ꡣUART0���͡��֥� */
    *pUART0_GCTL = 1;

        /* ����å������� */
    *pUART0_LCR |= DLAB;
    *pUART0_DLL = UART0_DIVISOR & 0xFF ;
    *pUART0_DLH = UART0_DIVISOR >> 8;
    *pUART0_LCR &= ~DLAB;

        /* �⡼������, �ѥ�ƥ�̵�� 8bit data, 1 stop bit */
    *pUART0_LCR = 0x03;

        /* ����߶ػ� */
    *pUART0_IER_CLEAR = 0xFFFF;

    *pPORTH_MUX &= ~(0x0003C000);   // bit3:0 ������0�ˤ���
    *pPORTH_FER |= 0x0180;      // PE7,PE8��UART0�˳�꿶��
#else
    /* Blackfin ��ͭ�����ꡣUART1���͡��֥� */
    *pUART1_GCTL = 1;

        /* ����å������� */
    *pUART1_LCR |= DLAB;
    *pUART1_DLL = UART1_DIVISOR & 0xFF ;
    *pUART1_DLH = UART1_DIVISOR >> 8;
    *pUART1_LCR &= ~DLAB;

        /* �⡼������, �ѥ�ƥ�̵�� 8bit data, 1 stop bit */
    *pUART1_LCR = 0x03;

        /* ����߶ػ� */
    *pUART1_IER_CLEAR = 0xFFFF;

    *pPORTH_MUX &= ~(0x000F);   // bit3:0 ������0�ˤ���
    *pPORTH_FER |= 0x0003;      // PH0,PH1��UART1�˳�꿶��
#endif
}

/*
 * priority_mask�ϡ�event���0..15�˱������������׵�Υӥåȥޥåפ��ݻ����롣
 * priority_mask[]�Υ���ǥå�����event��̤�Ʊ���Ǥ��롣�������װ��� BF54x�Ǥ�
 * 96�װ�����Τǡ�unsigned int����3�Ĥ�����ˤ��96bit���Ȥ��Ƥ��롣
 * (chip_config.h��IMS���������)
 *
 * device_dispatch()��priority_mask[]�򻲾Ȥ��ơ����ߵ��������٥�Ȥ��ɤγ�����
 * �װ��Ǥ��뤫���ꤹ������Ȥ��롣
 *
 * �����ѿ���make_priority_mask()��Ƥ��٤ˡ��ºݤ�IARx���ͤ˱����ƾ�񤭤���롣
 *
 */
IMS priority_mask[16]={
    {0x00000000u, 0x00000000u, 0x00000000u},    /* EMU */
    {0x00000000u, 0x00000000u, 0x00000000u},    /* RST */
    {0x00000000u, 0x00000000u, 0x00000000u},    /* NMI */
    {0x00000000u, 0x00000000u, 0x00000000u},    /* EVX */
    {0x00000000u, 0x00000000u, 0x00000000u},
    {0x00000000u, 0x00000000u, 0x00000000u},    /* IVHW */
    {0x00000000u, 0x00000000u, 0x00000000u},    /* IVTMR */
    {0xFF00007Fu, 0xFFC00001u, 0x00000000u},    /* IVG7 */
    {0x00000180u, 0x00000000u, 0x0000003Fu},    /* IVG8 */
    {0x00001E00u, 0x0000007Eu, 0x00000000u},    /* IVG9 */
    {0x0000E000u, 0x00001F80u, 0x00000000u},    /* IVG10 */
    {0x00070000u, 0x0039E000u, 0x3FFFFFC0u},    /* IVG11 */
    {0x00180000u, 0x00000000u, 0x00000000u},    /* IVG12 */
    {0x00E00000u, 0x00060000u, 0x00000000u},    /* IVG13 */
    {0x00000000u, 0x00000000u, 0x00000000u},    /* IVG14 */
    {0x00000000u, 0x00000000u, 0x00000000u}     /* IVG15 */
};


/*
* SIC_IARx����Ϥ��ơ����٥�Ƚ�̤��Ȥ˳�����Ƥ��Ƥ��������
* �Υӥåȥޥåפ��롣SIC_IARx�Υե�������ͤ�ͥ����-7�ʤΤ�
* ����ʬ�������롣
*/
#define INSTALL_PRIORITY(imask_idx)    \
    for ( i=0; i<8; i++ ){ \
        priority = iar & 0xf;                                       /* IAR����ͥ���̤���Ф� */ \
        priority_mask[priority + 7].imask[imask_idx] |= device;     /* ���Ф���ͥ���̤˴�Ť��ǥХ�������Ͽ */ \
        device <<= 1;                                               /* ���ΥǥХ��� */ \
        iar >>= 4;                                                  /* ����IAR�ե������ */ \
    }

/*
*  �����߽�̤��Ȥ�ISR�ӥåȥޥåפκ���SIC_IARx������Ϥ�����ʬ������˺Ѥޤ��뤳�ȡ�
*  ���δؿ���uITRON�Υ��˥���饤���ǻ��Ѥ��뤳�Ȥ����ꤷ�Ƥ��ꡢ�ä˳����ߤ����ݸ�Ƥ��ʤ���
*/
void make_priority_mask( void )
{
    unsigned int i, priority, iar;
    unsigned int device;

        // priority_mask�ϡ�event���0..15�˱������������׵�Υӥåȥޥåפ��ݻ����롣
        // �ǽ�˥��ꥢ����
    for ( i=0; i<16; i++ ){
        priority_mask[i].imask[0] = 0;
        priority_mask[i].imask[1] = 0;
        priority_mask[i].imask[2] = 0;
    }

    device = 1;
    iar = *pSIC_IAR0;
    INSTALL_PRIORITY(0)

    iar = *pSIC_IAR1;
    INSTALL_PRIORITY(0)

    iar = *pSIC_IAR2;
    INSTALL_PRIORITY(0)

    iar = *pSIC_IAR3;
    INSTALL_PRIORITY(0)

    device = 1;
    iar = *pSIC_IAR4;
    INSTALL_PRIORITY(1)

    iar = *pSIC_IAR5;
    INSTALL_PRIORITY(1)

    iar = *pSIC_IAR6;
    INSTALL_PRIORITY(1)

    iar = *pSIC_IAR7;
    INSTALL_PRIORITY(1)

    device = 1;
    iar = *pSIC_IAR8;
    INSTALL_PRIORITY(2)

    iar = *pSIC_IAR9;
    INSTALL_PRIORITY(2)

    iar = *pSIC_IAR10;
    INSTALL_PRIORITY(2)

    iar = *pSIC_IAR11;
    INSTALL_PRIORITY(2)
}


/*
 * �����ߤε��ġ�ADSP-BF54x�ϸ�ΨŪ�ʳ����߽����Ȱ����ʳ����߶ػߤ�ξΩ����
 * ���ʤ�����ʤ����ᡢ�ػߴؿ����֤��Ƥ��ʤ���
 *
 * ���ؤǤϤ��뤬���ץ���ޤ���դ�¥������ˤ������Ƥ��롣
 */
ER ena_int( INTNO intno )
{
    unsigned int mask;
    SIL_PRE_LOC;

    if ( intno >= DEVICE_INTERRUPT_COUNT )
        return ( E_PAR );
    else {
        if ( intno < 32 ){
            mask = 1 << intno;
            SIL_LOC_INT();
            *pSIC_IMASK0 |= mask;
            asm volatile( "ssync;" );
            SIL_UNL_INT();
        }
        else if ( intno < 64 ){
            mask = 1 << (intno-32);
            SIL_LOC_INT();
            *pSIC_IMASK1 |= mask;
            asm volatile( "ssync;" );
            SIL_UNL_INT();
        }
        else {
            mask = 1 << (intno-64);
            SIL_LOC_INT();
            *pSIC_IMASK2 |= mask;
            asm volatile( "ssync;" );
            SIL_UNL_INT();
        }
        return (0);
    }
}


/*
 * �����ߥޥ����μ�����ADSP-BF54x�ϸ�ΨŪ�ʳ����߽����Ȱ����ʳ����߶ػߤ�ξΩ����
 * ���ʤ�����ʤ����ᡢ�ػߴؿ����֤��Ƥ��ʤ���
 *
 * ���ؤǤϤ��뤬���ץ���ޤ���դ�¥������ˤ������Ƥ��롣
 */


extern ER get_ims( IMS * p_ims )
{
    SIL_PRE_LOC;

    SIL_LOC_INT();
    p_ims->imask[0] = *pSIC_IMASK0;
    p_ims->imask[1] = *pSIC_IMASK1;
    p_ims->imask[2] = *pSIC_IMASK2;
    SIL_UNL_INT();
    return( 0 );
}


/*
 *  �����ߤ�ǥХ����˳�����Ƥ롣
 *
 *  ���δֿ��ϳ�����ȯ�����˶��̳����ߥϥ�ɥ�ΰ����Ȥ��ƥ�����֥���줫������߶ػ߾��֤�
 *  �ƤФ�롣�³����ߥϥ�ɥ������߲�ǽ�ˤ��뤿�ᡢasmʸ��Ȥä�����ǳ����߲�ǽ�ˤ��Ƥ��롣
 *  �����߶ػ߾��֤ǸƤ֤Τϳ����߸������������ˤ����ʤ�����Ǥ��롣
 *
 */
void device_dispatcher( unsigned int priority, unsigned int imask )
{
    unsigned int device;
    unsigned int candidates[3], sic_isr[3];
    IMS          sic_imask;

    // �ƥ쥸�������ͤ�������롣
    get_ims(&sic_imask);
    sic_isr[0] = *pSIC_ISR0;
    sic_isr[1] = *pSIC_ISR1;
    sic_isr[2] = *pSIC_ISR2;

    // ���ߤΥץ饤����ƥ��������������߸������ꤹ�롣
    candidates[0] = priority_mask[priority].imask[0] & sic_isr[0] & sic_imask.imask[0];
    candidates[1] = priority_mask[priority].imask[1] & sic_isr[1] & sic_imask.imask[1];
    candidates[2] = priority_mask[priority].imask[2] & sic_isr[2] & sic_imask.imask[2];

    asm volatile("sti %0;": : "d"(imask) );

    // �����߸�������Ǥ��ʤ��ʤ顢����ͳ��Ǥ���
    if ( (0u == candidates[0]) && (0u == candidates[1]) && (0u == candidates[2]) )
    {
        if ( priority == ik_hardware_err )
            dev_vector[INHNO_HW_ERROR]();
        else
            if ( priority == ik_timer )
            dev_vector[INHNO_TIMER]();
        else
            dev_vector[INHNO_RAISE]();      //�����եȥ�����������

    }
    else if ((0u != candidates[0]))
    {
        if ( candidates[0] & 0x80000000 )
            device = 31;
        else
        {
#ifdef __GNUC__
    asm ( "r1.L = signbits %1; %0 = r1.L(z);":"=d"(device) :"d"(candidates[0]): "R1"  );
#elif defined(__ECC__)
    asm( "%0 = signbits %1;" : "=l"( device ) : "d"( candidates[0] ) );
#else
#error "Compiler is not supported"
#endif
            device = 30 - device;       // bit mask is converted to bit number
        }
        dev_vector[device]();
    }
    else if ((0u != candidates[1]))
    {
        if ( candidates[1] & 0x80000000 )
            device = 31;
        else
        {
#ifdef __GNUC__
    asm ( "r1.L = signbits %1; %0 = r1.L(z);":"=d"(device) :"d"(candidates[1]): "R1"  );
#elif defined(__ECC__)
    asm( "%0 = signbits %1;" : "=l"( device ) : "d"( candidates[1] ) );
#else
#error "Compiler is not supported"
#endif
            device = 30 - device;       // bit mask is converted to bit number
        }
        dev_vector[device + 32]();
    }
    else
    {
        if ( candidates[2] & 0x80000000 )
            device = 31;
        else
        {
#ifdef __GNUC__
    asm ( "r1.L = signbits %1; %0 = r1.L(z);":"=d"(device) :"d"(candidates[2]): "R1"  );
#elif defined(__ECC__)
    asm( "%0 = signbits %1;" : "=l"( device ) : "d"( candidates[2] ) );
#else
#error "Compiler is not supported"
#endif
            device = 30 - device;       // bit mask is converted to bit number
        }
        dev_vector[device + 64]();
    }
}



/*
 *  �������åȥ����ƥ�ν�λ��TOPPERS/JSP�����÷�ROM��˥�����뤳�Ȥ����ꤷ�Ƥ��뤬��
 *  ���Υܡ��ɤ�ROM�Ϥʤ���
 */
void
sys_exit()
{
    while(1)
        ;
}

/*
 *  �������åȥ����ƥ��ʸ�����ϡ������ߤ�̵���ʾ��֤ǥݡ���󥰤ˤ����Ϥ�Ԥ���
 */
void
sys_putc(char c)
{
    if ( c== 0x0A )         /* �⤷ LF �ʤ�� */
        sys_putc( 0x0D );   /* CR���ʸ������ */

    while( !( *pUART1_LSR & (1<<5)) )
        ;       /* UART0 LSR��THRE��1�ˤʤ�ޤ��Ԥġ�1�ʤ�������쥸����������*/

    *pUART1_THR = c;    /* ��ʸ������ */
}



