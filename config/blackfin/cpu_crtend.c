
typedef void (*fptr)(void);

/*
 * ctor_list_end��dtor_list_end��ctor_list��dtor_list����ʼ��Ǥ��롣ɬ��0�ǽ���롣
 */
static fptr ctor_list_end[1] __attribute__((section(".ctors"), used)) = { (fptr) 0 };
static fptr dtor_list_end[1] __attribute__((section(".dtors"), used)) = { (fptr) 0 };



