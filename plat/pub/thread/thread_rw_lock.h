#ifndef __THREAD_RW_LOCK_H__
#define __THREAD_RW_LOCK_H__

#include <time.h>
#include <pthread.h>
#include "thread_return.h"

namespace thread {

class ThreadRWLock {
public:
    ThreadRWLock();
    ~ThreadRWLock();

    ThreadRet RLock();
    ThreadRet WLock();
    ThreadRet RLock(struct timespec* overtime);
    ThreadRet WLock(struct timespec* overtime);
    ThreadRet UnLock();

private:
    bool init_flag_;
    pthread_rwlock_t rwlock_;

    static int _time_compare(struct timespec* a, struct timespec* b) {
        if (a->tv_sec < b->tv_sec) {
            return -1;
        } else if (a->tv_sec > b->tv_sec) {
            return 1;
        } else {
            if (a->tv_nsec < b->tv_nsec) {
                return -1;
            } else if (a->tv_nsec > b->tv_nsec) {
                return 1;
            } else {
                return 0;
            }
        }
    }

    static ThreadRet _errno2ret(int ierrno) {
        switch (ierrno) {
            case 0:
                return ThreadRet::SUCCESS;
            case EBUSY:
            case EINVAL:
            case EAGAIN:
            case EDEADLK:
            default:
                return ThreadRet::ERROR;
        }
    }

};

} // namespace thread


#endif
