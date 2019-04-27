/**
 * \file postmotem533.c
 * \brief ADSP-BF533�ѤΥݥ��ȥ⡼�ƥ����ץ롼����
 *
 * �ϡ��ɥ��������顼�ѤΥϥ�ɥ�ȡ��㳰�ѤΥϥ�ɥ餫��ʤ롣�������ƤӽФ�����UART����
 * �ݥ��ȥ⡼�ƥ���Ϥ�ɽ�����롣
 */
#include "jsp_kernel.h"
#include <cdefBF518.h>

/**
 * \brief UART������տ魯��DMA��ư�����ߤ������٤Ƥγ����ߤ�ػߤ��롣
 *
 * �Ǹ��UART_IER�򥯥ꥢ����Τϡ�UART�����ߤ�ػߤ����Ʊ����DMA��ػߤ��뤿�ᡣ
 * UART DMA�ϡ�UART�γ��������Ƕ�ư����Ƥ���Τǡ������ߤ�ػߤ����DMA�ꥯ������
 * ����ߤ��롣
 *
 * UART�ν������ɤ����뤫Ǻ�ޤ������������ǤϤ��Τޤް�������������Ѥ��뤳�Ȥˤ��롣
 *
 * �ݥ��ȥ⡼�ƥࡦ����פ���Ū�Ȥ��Ƥ���Τǡ����ξ��֤���β����Ϲͤ��ʤ���
 */
static void pm_occupy_uart()
{
        /* ���٤ƤΥ��������ߤ�ػߤ��� */
    asm( "cli r0;" : : : "R0" );

        /* ���٤ƤΥ����ƥ�����ߥ�������ػߤ��� */
    *pSIC_IMASK0 = 0;
    *pSIC_IMASK1 = 0;

        /* UART_IER��ǥ������֥�ˤ��뤳�Ȥǡ�DMA�򻦤��� */
    *pUART0_IER = 0;
}

/**
 * \brief ��ʸ������
 *
 * UART�������쥸���������ˤʤ�Τ��Ԥäư�ʸ�����Ϥ��롣
 */
static void pm_putc( unsigned char c )
{

        /* THR�����ˤʤ�ޤ��Ԥ� */
    while ( ! ( *pUART0_LSR & THRE ) )
        ;

        /*  THR�����ˤʤä���1ʸ������ */
    *pUART0_THR = c;
}

/**
 * \brief ���󥽡������ϴƻ�
 *
 * UART�μ����쥸�����˥ǡ���������С��ɤ߹��ࡣ�ǡ�����"!"�ʤ鿿��
 * ����ʳ��ʤ鵶���֤���
 */
static BOOL is_ready()
{
        /* �����ǡ����Ϥ��뤫�� */
    if ( *pUART0_LSR & DR )

    {
        char c;

        c= *pUART0_RBR;
        if ( c == '!' )
            return TRUE;
    }
    return FALSE;
}


/**
 * \brief ʸ�������
 *
 * ������ä�ʸ�����UART�˽��Ϥ��롣
 */
static void pm_putstr( char * s )
{
    int i;

    i=0;
    while( s[i] )   /* ��ü��NULL�������ޤǽ��� */
        pm_putc(s[i++]);
}

/**
 * \brief 1�Х��Ȥ�إ����ǥ��ޥ�ǽ��Ϥ��롣
 */
static void pm_puthex1byte( unsigned int data )
{
    int i;
    int nibble;

        /* 8bit��Τ��٤ƤΥ˥֥����� */
    for ( i=0; i<2; i++ )
    {
            /*���Ǿ�̥˥֥����С�*/
        nibble = ( data >> 4 ) & 0xF;
            /* ��Ф����˥֥����� */
        if ( nibble < 10 )
            pm_putc( nibble + '0' );
        else
            pm_putc( nibble - 10 + 'A' );
            /* ���Υ˥֥� */
        data <<= 4;
    }
}

/*
 * \brief ���Ե������Ϥ���
 */
static void pm_putrtn()
{
    pm_putstr("\r\n");
}

/**
 * \brief 4�Х��Ȥ�إ����ǥ��ޥ�ǽ��Ϥ��롣
 */
static void pm_puthex4byte( unsigned int data )
{
    int i;
    int nibble;

        /* 32bit��Τ��٤ƤΥ˥֥����� */
    for ( i=0; i<8; i++ )
    {
            /*���Ǿ�̥˥֥����С�*/
        nibble = ( data >> 28 ) & 0xF;
            /* ��Ф����˥֥����� */
        if ( nibble < 10 )
            pm_putc( nibble + '0' );
        else
            pm_putc( nibble - 10 + 'A' );
            /* ���Υ˥֥� */
        data <<= 4;
    }

}

/**
 * \brief �㳰�ե饰
 *
 * �㳰��ȯ�������Ȥ��ˤϿ��������Ǥʤ���е���hwei_handler()���㳰���ݤ��������롣
 *
 * GCC��ĥ���ڤä�link/unlink̿��ΰ��֤��Ŭ�����뤿�ᡢhwei_hanlder()��
 * ������ʤ�fp��귫��ʤ������Τ��ᡢdummy�򥢥��������뤳�Ȥ�link/unlink�ΰ���
 * ��Ŭ�����޻ߤ�ޤ����ܤ⤢�롣���̤����뤫�ɤ�����������
 */
static volatile int expFlag =0;
/**
 * \brief �ϡ��ɥ����������顼���ϥ�ɥ�
 *
 * �ϡ��ɥ����������顼���˸ƤӽФ���ơ��ϡ��ɥ����������顼�������ߤΥݥ��ȥ⡼�ƥ������Ԥ���
 * �ǽ��FP��귫�äơ������ߤΥ����å��ե졼���õ�������ˤ��٤Ƥγ����ߤ�ػߤ���
 * UART0����ͭ�������ȡ��ݡ���󥰤�Ȥäƥ����å�����¸���줿�ƥ쥸�����Υ���פ�Ԥ���
 * DEF_INH(INHNO_HW_ERROR, { TA_HLNG, hwei_handler });
 *
 */
void spurious_int_handler()
{
    unsigned int * fp, *ptr ;   /* �ե졼�ࡦ�ݥ��󥿤�귫�äƤ���������ѿ� */
    unsigned int reg;   /* �����ƥ�쥸�����������뤿����ѿ� */
    unsigned int imask, sic_imask0, sic_imask1; /*�ޥ�����Ͽ�쥸����*/

            /* ���ȤǻȤ� */
    imask = *pIMASK;
    sic_imask0 = *pSIC_IMASK0;
    sic_imask1 = *pSIC_IMASK1;
            /* UART0����������DMA�ȳ����ߤ�ػߤ��� */
    pm_occupy_uart();

    while (1)
    {
        int count = 0;

        pm_putstr( "Type '!' to display post mortem dump" ); pm_putrtn();

        while ( ! is_ready() )
        {
            int i;
            for ( i=0; i<100000000; i++)
                asm volatile ("nop;");
            if ( count > 30 )
            {
                pm_putstr( "Type '!' to display post mortem dump" ); pm_putrtn();
                count = 0;
            }
            else
                count ++;
        }
        pm_putrtn();


        /* ���ߤδؿ���FP��������� */
        asm ( "%0=fp;" : "=d"((unsigned int)fp) );

        /*
         * ���δؿ���ƤӽФ����ؿ� ( interrupt_dispatcher ) ��FP��������롣
         * FP�ϸƤӽФ��ؿ���FP�γ�Ǽ���Ϥ�ؤ��Ƥ��뤳�Ȥ����Ѥ���
         */
        fp = (void *)*fp;
        /*
         * interrupt_dispatcher ��ƤӽФ����ؿ���FP��������롣
         * ���δؿ��ϳ����ߥϥ�ɥ���������������¾�ʤ�ʤ���
         */
        fp = (void *)*fp;

        /* ���ޤ䡢FP�ϳ����߼��ջ�����¸���줿�쥸��������ؤ��Ƥ��� */

        /* �ץå��夵�줿 P0��ؤ� */
        ptr = fp + 2;
        /*
         * ���
         *      0   1   2   3   4   5   6   7   8   9
         * -----------------------------------------------
         *  00  P0  RTS FP  R0  R1  R2  R3  R4  R5  R6
         *  10  R7  P1  P2  P3  P4  P5  I3  I2  I1  I0
         *  20  M3  M2  M1  M0  B3  B2  B1  B0  L3  L2
         *  30  L1  L0  A0x A0w A1x A1w LC1 LC0 LT1 LT0
         *  40  LB1 LB0 AST RETI
         * ����
         *
        */
        if ( expFlag )
            pm_putstr( "Spurious Exception  !!" );
        else
            pm_putstr( "Spurious Interrupt  !!" );
        pm_putrtn();

        pm_putstr( "Registers On Stack :" );    pm_putrtn();
        pm_putstr( "P0   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "RETS " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "FP   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "R0   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "R1   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "R2   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "R3   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "R4   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "R5   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "R6   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "R7   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "P1   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "P2   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "P3   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "P4   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "P5   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "I3   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "I2   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "I1   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "I0   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "M3   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "M2   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "M1   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "M0   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "B3   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "B2   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "B1   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "B0   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "L3   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "L2   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "L1   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "L0   " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "A0   " );   pm_puthex1byte( *(ptr--) ); pm_putstr( ":" );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "A1   " );   pm_puthex1byte( *(ptr--) ); pm_putstr( ":" );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "LC1  " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "LC0  " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "LT1  " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "LT0  " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "LB1  " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "LB0  " );   pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "ASTAT " );  pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putstr( "RETI  " );  pm_puthex4byte( *(ptr--) ); pm_putrtn();
        pm_putrtn();
        pm_putstr( "System Registers :" );  pm_putrtn();
        pm_putstr( "SIC_IMASK1:0 " );   pm_puthex4byte( sic_imask1 );pm_putstr( " : " );pm_puthex4byte( sic_imask0 ); pm_putrtn();
        pm_putstr( "SIC_ISR1:0   " );   pm_puthex4byte( *pSIC_ISR1 );pm_putstr( " : " );pm_puthex4byte( *pSIC_ISR0 );  pm_putrtn();
        pm_putstr( "IMASK        " );   pm_puthex4byte( imask ); pm_putrtn();
        pm_putstr( "ILAT         " );   pm_puthex4byte( *pILAT ); pm_putrtn();
        pm_putstr( "IPEND        " );   pm_puthex4byte( *pIPEND ); pm_putrtn();
        asm( "%0=SEQSTAT;" : "=d"(reg) );
        pm_putstr( "SEQSTAT      " );   pm_puthex4byte( reg ); pm_putrtn();
        pm_putstr( "  EXCAUSE    " );   pm_puthex1byte( reg & 0x3F ); pm_putrtn();
        pm_putstr( "  HWERRCAUSE " );   pm_puthex1byte( (reg>>14)&0x1F ); pm_putrtn();
        pm_putstr( "DMA0_IRQ_STATUS    " ); pm_puthex4byte( *pDMA0_IRQ_STATUS ); pm_putrtn();
        pm_putstr( "DMA1_IRQ_STATUS    " ); pm_puthex4byte( *pDMA1_IRQ_STATUS ); pm_putrtn();
        pm_putstr( "DMA2_IRQ_STATUS    " ); pm_puthex4byte( *pDMA2_IRQ_STATUS ); pm_putrtn();
        pm_putstr( "DMA3_IRQ_STATUS    " ); pm_puthex4byte( *pDMA3_IRQ_STATUS ); pm_putrtn();
        pm_putstr( "DMA4_IRQ_STATUS    " ); pm_puthex4byte( *pDMA4_IRQ_STATUS ); pm_putrtn();
        pm_putstr( "DMA5_IRQ_STATUS    " ); pm_puthex4byte( *pDMA5_IRQ_STATUS ); pm_putrtn();
        pm_putstr( "DMA6_IRQ_STATUS    " ); pm_puthex4byte( *pDMA6_IRQ_STATUS ); pm_putrtn();
        pm_putstr( "DMA7_IRQ_STATUS    " ); pm_puthex4byte( *pDMA7_IRQ_STATUS ); pm_putrtn();
        pm_putstr( "DMA8_IRQ_STATUS    " ); pm_puthex4byte( *pDMA8_IRQ_STATUS ); pm_putrtn();
        pm_putstr( "DMA9_IRQ_STATUS    " ); pm_puthex4byte( *pDMA9_IRQ_STATUS ); pm_putrtn();
        pm_putstr( "DMA10_IRQ_STATUS    " );    pm_puthex4byte( *pDMA10_IRQ_STATUS ); pm_putrtn();
        pm_putstr( "DMA11_IRQ_STATUS    " );    pm_puthex4byte( *pDMA11_IRQ_STATUS ); pm_putrtn();
        pm_putstr( "MDMA_D0_IRQ_STATUS " ); pm_puthex4byte( *pMDMA_D0_IRQ_STATUS ); pm_putrtn();
        pm_putstr( "MDMA_S0_IRQ_STATUS " ); pm_puthex4byte( *pMDMA_S0_IRQ_STATUS ); pm_putrtn();
        pm_putstr( "MDMA_D1_IRQ_STATUS " ); pm_puthex4byte( *pMDMA_D1_IRQ_STATUS ); pm_putrtn();
        pm_putstr( "MDMA_S1_IRQ_STATUS " ); pm_puthex4byte( *pMDMA_S1_IRQ_STATUS ); pm_putrtn();
        pm_putstr( "SPI_STAT           " ); pm_puthex4byte( *pSPI_STAT ); pm_putrtn();
        pm_putstr( "PPI_STATUS         " ); pm_puthex4byte( *pPPI_STATUS ); pm_putrtn();
        pm_putstr( "SPORT0_STAT        " ); pm_puthex4byte( *pSPORT0_STAT ); pm_putrtn();
        pm_putstr( "SPORT1_STAT        " ); pm_puthex4byte( *pSPORT1_STAT ); pm_putrtn();
        pm_putstr( "TIMER_STATUS       " ); pm_puthex4byte( *pTIMER_STATUS ); pm_putrtn();
        pm_putstr( "EBIU_SDSTAT        " ); pm_puthex4byte( *pEBIU_SDSTAT ); pm_putrtn();
        pm_putrtn();
        pm_putstr( "Calling Stack :" ); pm_putrtn();

        while( fp )
        {
            pm_putstr( "Called from " );    pm_puthex4byte( *(fp+1) ); pm_putrtn();
            fp = *fp;
        }
    }
}

/**
 * \brief CPU�㳰�ϥ�ɥ�
 *
 * CPU�㳰�ϥ�ɥ�Ȥ���cfg�ե��������Ͽ���롣 hwei_handler()�ϸƤФ줿����äƤ��ʤ�����
 * ���Τ��Ȥˤ�expFlag���ͤ��������Ƥ���Τϡ���Ŭ���ˤ�ä�unlink̿����ͤ��롼����ƤӽФ���
 * ���˰�ư���뤳�Ȥ��ɤ�����Ǥ��롣
 *
 * DEF_EXC(CPUEXC1, { TA_HLNG, excp_handler} );
 *
 */
void spurious_exc_handler(VP p_excinf)
{
    expFlag = TRUE;
    spurious_int_handler();
}

