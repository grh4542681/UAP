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
    SpecificPool(std::string name, F worker, Args&& ... args) : tuple_args(std::forward_as_tuple(std::forward<Args>(args)...)){
        name_ = name;
        ptemp_ = ProcessTemplate<F>(name_ + ":worker", worker);
    }
    ~SpecificPool() {

    }

    ProcessRet Run() {
        _apply(std::make_index_sequence<std::tuple_size<std::tuple<Args...>>::value>());
        _apply(std::make_index_sequence<std::tuple_size<std::tuple<Args...>>::value>());
        sleep(20);
        return ProcessRet::SUCCESS;
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

    template <std::size_t... I>
    void _apply(std::index_sequence<I...>) {
        ptemp_.Run(std::get<I>(tuple_args)...);
    }
};

}

#endif
