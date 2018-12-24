#ifndef __TEMP_SINGLETON_H__
#define __TEMP_SINGLETON_H__

#include <utility>
#include <memory>
#include "pthread_mutex_lock.h"

namespace pub {

template <typename T>
class Singleton {
public:
    /**
    * @brief getInstance - Get an instance
    *
    * @tparam [Args] -  Indefinite length parameter template.
    * @param [args] - Parameters for instance.
    *
    * @returns  Instance pointer
    */
    template <typename ... Args>
    static T* getInstance(Args&& ... args)
    {
        if (!pInstance_) {
            mutex_.lock();
            if (!pInstance_) {
                pInstance_ = new T(std::forward<Args>(args)...);
            }
            mutex_.unlock();
        }
        return pInstance_;
    }

    static void delInstance()
    {
        if (pInstance_) {
            delete pInstance_;
            pInstance_ = NULL;
        }
    }

    template <typename ... Args>
    static T* resetInstance(Args&& ... args)
    {
        delInstance();
        return getInstance(std::forward<Args>(args)...);
    }

private:
    Singleton();
    ~Singleton();
    Singleton(const Singleton&);
    Singleton& operator = (const Singleton&);

    static T* pInstance_;
    static PthreadMutexLock mutex_;
};

template <typename T> T* Singleton<T>::pInstance_ = NULL;
template <typename T> PthreadMutexLock Singleton<T>::mutex_;

} //namespace pub end

#endif
