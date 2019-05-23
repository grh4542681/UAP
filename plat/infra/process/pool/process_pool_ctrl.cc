#include "process_pool.h"

namespace process:pool {

ProcessPool::ProcessPool(std::string name) {
    name_ = name;
    mix_size_ = 0;
    max_size_ = 0;
    working_size_ = 0;
    init_flag_ = false;
    auto_size_flag_ = false;
}

}
