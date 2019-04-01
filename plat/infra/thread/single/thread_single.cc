#include "thread_single.h"

namespace thread::single {

ThreadSingle::ThreadSingle()
{

}

ThreadSingle::~ThreadSingle()
{

}

ThreadInfo* ThreadSingle::GetThreadInfo()
{
    return thread_info_;
}



}
