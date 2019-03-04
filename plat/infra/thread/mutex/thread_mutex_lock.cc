#include <pthread.h>
#include <errno.h>
#include "../thread_log.h"
#include "thread_mutex_lock.h"

namespace thread::mutex {

ThreadMutexLock::ThreadMutexLock()
{
    this->init_ = false;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_NORMAL);
    if (pthread_mutex_init(&(this->mutex_), &attr)) {
        THREAD_ERROR("Cannot create the mutex");
    } else {
        this->init_ = true;
    }    
    pthread_mutexattr_destroy(&attr);
}

ThreadMutexLock::~ThreadMutexLock()
{
    if (this->init_) {
        pthread_mutex_destroy(&(this->mutex_));
    }
}

ThreadRet ThreadMutexLock::lock()
{
    if (!this->init_) {
        return ThreadRet::EINIT;
    }
    if (int ret = pthread_mutex_lock(&(this->mutex_))) {
        THREAD_ERROR("Cannot lock the mutex, ret:%d, errno:%d", ret, errno);
        return ThreadRet::ERROR;
    }
    return ThreadRet::SUCCESS;
}

ThreadRet ThreadMutexLock::unlock()
{
    if (!this->init_) {
        return ThreadRet::EINIT;
    }
    if (int ret = pthread_mutex_unlock(&(this->mutex_))) {
        THREAD_ERROR("Cannot lock the mutex, ret:%d, errno:%d", ret, errno);
        return ThreadRet::ERROR;
    }
    return ThreadRet::SUCCESS;
}

} //namespace end
