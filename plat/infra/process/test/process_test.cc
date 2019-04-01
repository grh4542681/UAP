#include "process_info.h"
#include "file_c.h"
#include "thread.h"
#include "report_mode.h"

int main()
{
    process::ProcessInfo* p = process::ProcessInfo::getInstance();
    printf("pid %d ppid %d name %s pname %s\n", p->GetPid(), p->GetPPid(), p->GetName().c_str(), p->GetProcessName().c_str());

    thread::RegisterThread("grhtest");

    file::FileC fd(stdout);
    p->Report(fd,report::ReportMode::DETAIL);
    return 0;
}
