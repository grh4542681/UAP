#include <stdio.h>

#include "process_info.h"
#include "single/process_single.h"
#include "file_c.h"
#include "thread.h"
#include "report_mode.h"

void test_process()
{
    printf("child [%d]\n",getpid());
    sleep(20);
}

int main()
{
    process::ProcessInfo* p = process::ProcessInfo::getInstance();

/*
    std::string i = "/home/ezgaoro/workspace/cppfram/bin/test/time_c_test";
    process::single::ProcessSingle<std::string> p2(i);
    p2.Run(NULL);
*/

    auto process_type = test_process;
    process::single::ProcessSingle<decltype(process_type)> p1("test_grh", test_process);
    p1.Run();

    sleep(5);
    file::FileC fd(stdout);
    p->Report(fd,report::ReportMode::DETAIL);

    sleep(25);
    p->Report(fd,report::ReportMode::DETAIL);
    return 0;
}
