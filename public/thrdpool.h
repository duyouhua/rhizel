/*
 *file name : thrdpool.h
 *des : 
 *date : 2013-11-20
 *author : liwq (286570361)
 *notes :
 *       2013-10-21   liwq      create files
 */

/**********************************************************/
#ifndef THREAD_POOL_H__
#define THREAD_POOL_H__
 
#include <pthread.h>
 
/* Ҫִ�е��������� */
typedef struct tpool_work {
    void*               (*routine)(void*);       /* ������ */
    void                *arg;                    /* �����������Ĳ��� */
    struct tpool_work   *next;                    
}tpool_work_t;
 
typedef struct tpool {
    int             shutdown;                    /* �̳߳��Ƿ����� */
    int             list_close;
    int             max_thr_num;                /* ����߳��� */
    pthread_t       *thr_id;                    /* �߳�ID���� */
    tpool_work_t    *queue_head;                /* �߳����� */
    pthread_mutex_t queue_lock;                    
    pthread_cond_t  queue_ready;    
    pthread_cond_t  queue_empty;   
}tpool_t;
 
/*
 * @brief     �����̳߳� 
 * @param     max_thr_num ����߳���
 * @return     0: �ɹ� ����: ʧ��  
 */
int
tpool_create(tpool_t **ppTpool, int max_thr_num);
 
/*
 * @brief     �����̳߳� 
 */
void
tpool_destroy(tpool_t *tpool, int flag);
 
/*
 * @brief     ���̳߳����������
 * @param    routine ������ָ��
 * @param     arg ����������
 * @return     0: �ɹ� ����:ʧ�� 
 */
int
tpool_add_work(tpool_t *tpool, void*(*routine)(void*), void *arg, int len);
 
#endif