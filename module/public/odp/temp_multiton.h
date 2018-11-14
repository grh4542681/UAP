#ifndef __TEMP_MULTITON_H__
#define __TEMP_MULTITON_H__

#include <map>
#include <string>
#include <memory>
#include <utility>
#include "pthread_mutex_lock.h"

namespace base {

template < typename T, typename K = string>
class Multiton
{
public:
    template<typename... Args>
    static std::shared_ptr<T> getInstance(const K& key, Args&&... args)
    {
        return _getInstance(key, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static std::shared_ptr<T> getInstance(K&& key, Args&&... args)
    {
        return _getInstance(key, std::forward<Args>(args)...);
    }
private:
    template<typename Key, typename... Args>
    static std::shared_ptr<T> _getInstance(Key&& key, Args&&...args)
    {
        std::shared_ptr<T> instance = NULL;
        auto it = m_map.find(key);
        if (it == m_map.end()) {
            instance = std::make_shared<T>(std::forward<Args>(args)...);
            m_map.emplace(key, instance);
        } else {
            instance = it->second;
        }

        return instance;
    }

    Multiton(void);
    virtual ~Multiton(void);
    Multiton(const Multiton&);
    Multiton& operator = (const Multiton&);

    static map<K, std::shared_ptr<T>> m_map;
};
template <typename T, typename K> map<K, std::shared_ptr<T>> Multiton<T, K>::m_map;

} //namespace base end


#endif
