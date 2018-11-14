#ifndef __TEMP_SINGLETON_H__
#define __TEMP_SINGLETON_H__

#include <utility>
#include <memory>
#include "pthread_mutex_lock.h"

namespace base {

template <typename T>
class Singleton {
public:
    template <typename ... Args>
    static T* getInstance(Args&& ... args)
    {
        if (!_pInstance) {
            _mutex.lock();
            if (!_pInstance) {
                _pInstance = new T(std::forward<Args>(args)...);
            }
            _mutex.unlock();
        }
        return _pInstance;
    }

    static void delInstance()
    {
        if (_pInstance) {
            delete _pInstance;
            _pInstance = NULL;
        }
    }

private:
    Singleton();
    ~Singleton();
    Singleton(const Singleton&);
    Singleton& operator = (const Singleton&);

    static T* _pInstance;
    static std::shared_ptr<T> _pInstance1;
    static PthreadMutexLock _mutex;
};

template <typename T> T* Singleton<T>::_pInstance = NULL;
template <typename T> PthreadMutexLock Singleton<T>::_mutex;

} //namespace odp end

#endif
