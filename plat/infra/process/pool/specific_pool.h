#ifndef __SPECIFIC_POOL_H__
#define __SPECIFIC_POOL_H__

#include <string>
#include <utility>
#include <tuple>

#include "process_template.h"

namespace process::pool {

template < typename F, typename ... Args >
class SpecificPool {
public:
    SpecificPool(std::string name, F worker, Args&& ... args) {
        name_ = name;
        ptemp_ = ProcessTemplate<F>(name_ + ":worker", worker);
        tuple_args = std::make_tuple(std::forward<Args>(args)...);
    }
    ~SpecificPool() {

    }

    ProcessRet Run() {
//        std::apply(ptemp_.Run, tuple_args);
        std::index_sequence<std::size_t...> num = std::make_index_sequence<std::tuple_size<std::tuple<Args...>::value>();
        ptemp_.Run(std::get<num>(tuple_args)...);
    }

private:
    std::string name_;
    bool fork_keeper_;
    size_t min_size_;
    size_t max_size_;
    size_t cur_size_;
    bool init_flag_;
    bool auto_size_flag_;

    std::tuple<Args...> tuple_args;

    ProcessTemplate<F> ptemp_;
};

}

#endif
