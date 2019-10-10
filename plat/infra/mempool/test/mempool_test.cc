#include "mempool.h"
#include "file.h"

#include <utility>

#include <pthread.h>
#include <unistd.h>

void* test_thread(void* args)
{
    mempool::MemPool* mp = mempool::MemPool::getInstance();
    void* p =mp->Malloc(100);
    p = mp->Malloc(200);

    file::File fd(std::forward<file::FileFD>(stdout));    
    mp->ReportThread(fd);
    printf("-------------\n");
    mp->Free(p);
    mp->ReportThread(fd);
    return NULL;
}

int main()
{

    pthread_t tid1;
    pthread_t tid2;
    pthread_t tid3;

    pthread_create(&tid1, NULL, test_thread, NULL);
    sleep(1);
    pthread_create(&tid2, NULL, test_thread, NULL);
    sleep(1);
    pthread_create(&tid3, NULL, test_thread, NULL);
    sleep(1);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
/*
    mempool::MemPool* mp = mempool::MemPool::getInstance();
    void* p =mp->Malloc(100);
    printf("%p\n",p);
    p = mp->Malloc(200);
    printf("%p\n",p);

    file::File fd(stdout);    
    mp->ReportThread(fd);
    printf("-------------\n");
    mp->Free(p);
    mp->ReportThread(fd);
*/
    return 0;
}
