#include "jsp_kernel.h"

#ifdef __GNUC__
#include "cdefBF548.h"       /* gnu tool chain */
#elif defined(__ECC__)
#error "Don't use sys_debugboot.c for VDSP "
#else
#error "Compiler is not supported"
#endif


/*
* gdbserver���������åȤΥꥻ�åȵ�ǽ���󶡤��ʤ����ᡢgdb��ͳ�ǥ������å�
* �˥��ץ�å����������������ɤ����������ư��ʤ����Ȥ����롣
* ���Υ롼����ϥ������åȤ���٤����ꥻ�åȤ��롣
*/
void boot_for_gdb( void )
{
    if ( enable_boot_for_gdb ){   /* ���եȥ������ꥻ�åȤ������Ƥ��ʤ��ʤ�ʲ��¹ԡ�*/
        enable_boot_for_gdb = 0;            /* ��֡��Ȥϰ����� */
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
    else
    {
        *pPLL_LOCKCNT = 0x200;          /* Fix the anormaly 05000430 */
    }
}
