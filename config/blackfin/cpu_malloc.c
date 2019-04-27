#include <t_services.h>

static void * heapPtr = 0;
extern void *_heap_start, *_heap_end;

/*
 * �׵᤬����Хҡ��׾�˥����ΰ�������Ƥ롣free�ϻȤ�ʤ����Ȥ��ꤷ�Ƥ��롣
 */

void * malloc(size_t size)
{
    void * retPtr;
    SIL_PRE_LOC;

    SIL_LOC_INT();
    // �ǽ�θƤӽФ��ǥҡ��פ���������
    if (! heapPtr)
        heapPtr = _heap_start;

    retPtr = heapPtr;

    if ((heapPtr+size) >= _heap_end)
        retPtr =  NULL;
    else
    {
        heapPtr += size;
            // �ݥ��󥿤�32bit������·����
        while ((unsigned int)heapPtr % 4)
            heapPtr++;
    }
    SIL_UNL_INT();
    return retPtr;
}

/*
 * �ʤˤ⤻�������
 */
void free( void * ptr )
{
}
