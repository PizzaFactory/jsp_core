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
 *  �������åȥ����ƥ��¸�⥸�塼���ADSP-BF518�ѡ�
 */

#include "jsp_kernel.h"
#include <sil.h>

#ifdef __GNUC__
#include <cdefBF518.h>      /* gnu tool chain */
#elif defined(__ECC__)
#include <cdefbf518.h>              /* VisualDSP++ */
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
     * ���åפΥ��ꥳ���ӥ����˱�����PLL_CTL�Υǥե������.
     * Silicon Rev�ˤ��PLL_CTL���Ѳ��ˤĤ��Ƥ� anomaly �����
     * http://ez.analog.com/thread/14209 �򻲾ȡ�
     */
    int plldefault;

    if (( *pDSPID & 0xFF ) < 2 )
        plldefault = 0x0A00;
    else
        plldefault = 0x0b00;

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
        // PLL������ͤΤޤޤǤ��ꡢ���ġ�SDRAM��������Ǥʤ����PLL����������
     if ( ( *pPLL_CTL == plldefault ) && ( !(*pEBIU_SDBCTL & EBE ) ) )
#endif
     {

        *pSIC_IWR = IWR_ENABLE(0);              // PLL�Τ�IWR�����
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
        *pSIC_IWR = IWR_ENABLE_ALL;
    }

    /*
     *  UARTʬ���������
     *
     *  Logtask��ư�������sys_putc()��Ȥ�����������Ԥ����ʲ��������
     *  serial��Ϣ�Υ���������ư�����Ȥ��˾�񤭤���롣
     */
#define DLAB 0x80

        /* Blackfin ��ͭ�����ꡣUART���͡��֥� */
    *pUART0_GCTL = 1;

        /* ����å������� */
    *pUART0_LCR |= DLAB;
    *pUART0_DLL = UART0_DIVISOR & 0xFF ;
    *pUART0_DLH = UART0_DIVISOR >> 8;
    *pUART0_LCR &= ~DLAB;

        /* �⡼������, �ѥ�ƥ�̵�� 8bit data, 1 stop bit */
    *pUART0_LCR = 0x03;

        /* ����߶ػ� */
    *pUART0_IER = 0;

    *pPORTG_MUX &= ~(0x0C00);   // bit11:10 ������0�ˤ���
    *pPORTG_MUX |= 0x01<<10;    // bit11:10 ������01�ˤ���
    *pPORTG_FER |= 0x0600;      // PG9,PG10��UART0�˳�꿶��
}

/*
 * priority_mask�ϡ�event���0..15�˱������������׵�Υӥåȥޥåפ��ݻ����롣
 * priority_mask[]�Υ���ǥå�����event��̤�Ʊ���Ǥ��롣�������װ��� BF51x�Ǥ�
 * 64�װ�����Τǡ�unsigned long long�ˤ��64bit���Ȥ��Ƥ��롣
 *
 * device_dispatch()��priority_mask[]�򻲾Ȥ��ơ����ߵ��������٥�Ȥ��ɤγ�����
 * �װ��Ǥ��뤫���ꤹ������Ȥ��롣
 *
 * �����ѿ���make_priority_mask()��Ƥ��٤ˡ��ºݤ�IARx���ͤ˱����ƾ�񤭤���롣
 *
 */
unsigned long long int priority_mask[16]={
    0x0000000000000000ull,  /* EMU */
    0x0000000000000000ull,  /* RST */
    0x0000000000000000ull,  /* NMI */
    0x0000000000000000ull,  /* EVX */
    0x0000000000000000ull,
    0x0000000000000000ull,  /* IVHW */
    0x0000000000000000ull,  /* IVTMR */
    0x0007800000003FFFull,  /* IVG7 */
    0x000000000000C000ull,  /* IVG8 */
    0x00000000000F0000ull,  /* IVG9 */
    0x00F8000003F00000ull,  /* IVG10 */
    0x00000000FC000000ull,  /* IVG11 */
    0x000003FF00000000ull,  /* IVG12 */
    0x00007C0000000000ull,  /* IVG13 */
    0x0000000000000000ull,  /* IVG14 */
    0x0000000000000000ull   /* IVG15 */
};


/*
* SIC_IARx����Ϥ��ơ����٥�Ƚ�̤��Ȥ˳�����Ƥ��Ƥ��������
* �Υӥåȥޥåפ��롣SIC_IARx�Υե�������ͤ�ͥ����-7�ʤΤ�
* ����ʬ�������롣
*/
#define INSTALL_PRIORITY    \
    for ( i=0; i<8; i++ ){ \
        priority = iar & 0xf;                         /* IAR����ͥ���̤���Ф� */ \
        priority_mask[priority + 7] |= device;        /* ���Ф���ͥ���̤˴�Ť��ǥХ�������Ͽ */ \
        device <<= 1;                                 /* ���ΥǥХ��� */ \
        iar >>= 4;                                    /* ����IAR�ե������ */ \
    }

/*
*  �����߽�̤��Ȥ�ISR�ӥåȥޥåפκ���SIC_IARx������Ϥ�����ʬ������˺Ѥޤ��뤳�ȡ�
*  ���δؿ���uITRON�Υ��˥���饤���ǻ��Ѥ��뤳�Ȥ����ꤷ�Ƥ��ꡢ�ä˳����ߤ����ݸ�Ƥ��ʤ���
*/
void make_priority_mask( void )
{
    unsigned int i, priority, iar;
    unsigned long long int device;



        // priority_mask�ϡ�event���0..15�˱������������׵�Υӥåȥޥåפ��ݻ����롣
        // �ǽ�˥��ꥢ����
    for ( i=0; i<16; i++ ){
        priority_mask[i] = 0;
    }

    device = 1;
    iar = *pSIC_IAR0;
    INSTALL_PRIORITY

    iar = *pSIC_IAR1;
    INSTALL_PRIORITY

    iar = *pSIC_IAR2;
    INSTALL_PRIORITY

    iar = *pSIC_IAR3;
    INSTALL_PRIORITY

    iar = *pSIC_IAR4;
    INSTALL_PRIORITY

    iar = *pSIC_IAR5;
    INSTALL_PRIORITY

    iar = *pSIC_IAR6;
    INSTALL_PRIORITY

    iar = *pSIC_IAR7;
    INSTALL_PRIORITY

}


/*
 * �����ߤε��ġ�ADSP-BF51x�ϸ�ΨŪ�ʳ����߽����Ȱ����ʳ����߶ػߤ�ξΩ����
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
        else{
            mask = 1 << (intno-32);
            SIL_LOC_INT();
            *pSIC_IMASK1 |= mask;
            asm volatile( "ssync;" );
            SIL_UNL_INT();
        }
        return (0);
    }
}


/*
 * �����ߥޥ����μ�����ADSP-BF51x�ϸ�ΨŪ�ʳ����߽����Ȱ����ʳ����߶ػߤ�ξΩ����
 * ���ʤ�����ʤ����ᡢ�ػߴؿ����֤��Ƥ��ʤ���
 *
 * ���ؤǤϤ��뤬���ץ���ޤ���դ�¥������ˤ������Ƥ��롣
 */


extern ER get_ims( IMS * p_ims )
{
    SIL_PRE_LOC;

    SIL_LOC_INT();
    *p_ims = (((IMS)*pSIC_IMASK1)<<32 ) | (IMS)*pSIC_IMASK0;
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
    unsigned int device, candidates;
    unsigned long long int longcandidates, sic_isr, sic_imask;

        //���ʲ��Ǥ� SIC_IMASK0,1��ޤȤ��64bit�쥸�����Ȥ��ư��äƤ��롣SIC_ISR��Ʊ���Ǥ��롣
    get_ims(&sic_imask);
    sic_isr = (((IMS)*pSIC_ISR1)<<32 ) | (IMS)*pSIC_ISR0;

        // ���ߤΥץ饤����ƥ��������������߸������ꤹ�롣
    longcandidates = priority_mask[priority] & sic_isr & sic_imask;

    asm volatile("sti %0;": : "d"(imask) );

    if ( ! longcandidates ) // �����߸�������Ǥ��ʤ��ʤ顢����ͳ��Ǥ���
    {
        if ( priority == ik_hardware_err)
            dev_vector[INHNO_HW_ERROR]();
        else
            if ( priority == ik_timer)
            dev_vector[INHNO_TIMER]();
        else
            dev_vector[INHNO_RAISE]();      //�����եȥ�����������

    }
    else if ( longcandidates & 0xFFFFFFFF00000000ull )
    {
        candidates = longcandidates >> 32;
        if ( candidates & 0x80000000 )
            device = 31;
        else
        {
#ifdef __GNUC__
    asm ( "r1.L = signbits %1; %0 = r1.L(z);":"=d"(device) :"d"(candidates): "R1"  );
#elif defined(__ECC__)
    asm( "%0 = signbits %1;" : "=l"( device ) : "d"( candidates ) );
#else
#error "Compiler is not supported"
#endif
            device = 30 - device;       // bit mask is converted to bit number
        }
        dev_vector[device+32]();
    }
    else
    {
        candidates = (unsigned int)longcandidates;
        if ( candidates & 0x80000000 )
            device = 31;
        else
        {
#ifdef __GNUC__
    asm ( "r1.L = signbits %1; %0 = r1.L(z);":"=d"(device) :"d"(candidates): "R1"  );
#elif defined(__ECC__)
    asm( "%0 = signbits %1;" : "=l"( device ) : "d"( candidates ) );
#else
#error "Compiler is not supported"
#endif
            device = 30 - device;       // bit mask is converted to bit number
        }
        dev_vector[device]();
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

    while( !( *pUART0_LSR & (1<<5)) )
        ;       /* UART0 LSR��THRE��1�ˤʤ�ޤ��Ԥġ�1�ʤ�������쥸����������*/

    *pUART0_THR = c;    /* ��ʸ������ */
}



