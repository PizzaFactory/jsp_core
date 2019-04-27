#include "jsp_kernel.h"
#include "sil.h"

#ifdef __GNUC__
#include <cdefBF592-A.h>        /* gnu tool chain */
#elif defined(__ECC__)
#include <cdefbf592-A.h>                /* VisualDSP++ */
#include <ccblkfn.h>
#include <sysreg.h>
#else
#error "Compiler is not supported"
#endif

/*
* gdbserver���������åȤΥꥻ�åȵ�ǽ���󶡤��ʤ����ᡢgdb��ͳ�ǥ������å�
* �˥��ץ�å����������������ɤ����������ư��ʤ����Ȥ����롣
* ���Υ롼����ϥ������åȤ���٤����ꥻ�åȤ��롣
*
* �ʤ����ѥ�᡼�� debug�� FALSE�ξ�硢�ꥻ�åȤϤ��ʤ�
*/
void boot_for_gdb(void)
{
    // SYSTEM_RESET     0x0007
    // DOUBLE_FAULT     0x0008
    // RESET_DOUBLE     0x2000
    // RESET_WDOG       0x4000
    // RESET_SOFTWARE   0x8000
    if ( enable_boot_for_gdb ){
        enable_boot_for_gdb = 0;            /* ���ϥ֡��Ȥ��ʤ� */
        *pSWRST = 0x07;                     /* ��¢�ڥ�ե����Υꥻ�åȡ�*/
        asm volatile( "ssync;" );
        *pSWRST = 0x00;                     /* ��¢�ڥ�ե����Υꥻ�åȲ���� */
        asm volatile( "ssync;" );
        *pSYSCR |= 0x10;                    /* no boot on core reset */
        asm volatile( "ssync;" );
        asm volatile( "raise 1;" );         /* �����ꥻ�å� */
        while( 1 )
            ;                               /*�ꥻ�åȤ�ȯ������ޤǥ롼��*/
    }
}
