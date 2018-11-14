#include <pthread.h>
#include <errno.h>
#include "pthread_mutex_lock.h"
#include "mutex_log.h"

namespace base {

PthreadMutexLock::PthreadMutexLock()
{
    this->_init = false;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_NORMAL);
    if (pthread_mutex_init(&(this->_mutex), &attr)) {
        MUTEX_ERROR("Cannot create the mutex");
    } else {
        this->_init = true;
    }    
    pthread_mutexattr_destroy(&attr);
}

PthreadMutexLock::~PthreadMutexLock()
{
    if (this->_init) {
        pthread_mutex_destroy(&(this->_mutex));
    }
}

MutexRet PthreadMutexLock::lock()
{
    if (!this->_init) {
        return MutexRet::UNINIT;
    }
    if (int ret = pthread_mutex_lock(&(this->_mutex))) {
        MUTEX_ERROR("Cannot lock the mutex, ret:%d, errno:%d", ret, errno);
        return MutexRet::ERROR;
    }
    return MutexRet::SUCCESS;
}

MutexRet PthreadMutexLock::unlock()
{
    if (!this->_init) {
        return MutexRet::UNINIT;
    }
    if (int ret = pthread_mutex_unlock(&(this->_mutex))) {
        MUTEX_ERROR("Cannot lock the mutex, ret:%d, errno:%d", ret, errno);
        return MutexRet::ERROR;
    }
    return MutexRet::SUCCESS;
}

} //namespace base end
