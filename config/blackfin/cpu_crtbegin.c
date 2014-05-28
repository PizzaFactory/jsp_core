
typedef void (*fptr)(void);

/*
 * ctor_list_begin��dtor_list_begin�ϥޥ��å��ʥ�С�(-1)����Ϥޤ롣gcc�Ϥ��줾���1�֤�
 * ����ȥ꤫������襪�֥������Ȥν�����Τ���Υ��󥹥ȥ饯���Υݥ��󥿤����Ƥ�����
 * �Ǹ��NULL���֤���
 */
static fptr ctor_list_begin[1] __attribute__((section(".ctors"), used)) = { (fptr) -1 };
static fptr dtor_list_begin[1] __attribute__((section(".dtors"), used)) = { (fptr) -1 };


/*
 * _init��_fini���ü�ʥ�������� .init��.fini�˳�Ǽ����롣�����gcc�ο侩�Ǥ��롣
 * �ܤ�����gcc�Υޥ˥奢�뻲��
 */
extern void _init(void) __attribute__((section(".init")));
extern void _fini(void) __attribute__((section(".fini")));

void
_init(void)
{
    fptr *fpp;

        // �Ǹ�Υ��󥹥ȥ饯����õ��
    for(fpp = ctor_list_begin + 1;  *fpp != 0;  ++fpp)
        ;
        // ��������ؼ¹Ԥ���
    while(--fpp > ctor_list_begin)
        (**fpp)();
}


void
_fini(void)
{
    fptr *fpp;

        // �ǥ��ȥ饯���������ȵս�˼¹Ԥ���
    for(fpp = dtor_list_begin + 1;  *fpp != 0;  ++fpp)
        (**fpp)();

}

