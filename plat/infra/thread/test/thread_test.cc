#include <unistd.h>
#include <stdio.h>

#include "thread_info.h"
#include "single/thread_single.h"

#include "process_info.h"
#include "file_c.h"
#include "report_mode.h"

void test_thread(int i)
{
    printf("%d\n",i);
    sleep(10);
}

int main()
{

    auto thread_type = test_thread;

    thread::single::ThreadSingle<decltype(thread_type)> thread1;
    thread::single::ThreadSingle<decltype(thread_type)> thread2;
    thread::single::ThreadSingle<decltype(thread_type)> thread3;

    thread1.Run(100);
    thread2.Run(111);
    thread3.Run(122);

    process::ProcessInfo* p = process::ProcessInfo::getInstance();
    file::FileC fd(stdout);
    p->Report(fd,report::ReportMode::DETAIL);
    sleep(15);
    return 0;
}
