#include "process_info.h"
#include "file_c.h"
#include "message_agent.h"

int main()
{
    process::ProcessInfo* p = process::ProcessInfo::getInstance();
    file::FileC fd(stdout);
    p->Report(fd,report::ReportMode::DETAIL);
    message::MessageAgent agent("test");
    agent.Run();
    printf("run agent\n");
    sleep(2);
    p->Report(fd,report::ReportMode::DETAIL);

    sleep(15);
    p->Report(fd,report::ReportMode::DETAIL);
    return 0;
}
