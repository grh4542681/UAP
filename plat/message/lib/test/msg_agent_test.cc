#include "process_info.h"
#include "file.h"
#include "message_agent.h"

int main()
{
    process::ProcessInfo* p = process::ProcessInfo::getInstance();
    file::File fd(stdout);
    p->Report(fd,report::ReportMode::DETAIL);
    message::MessageAgent* agent = message::MessageAgent::getInstance();
    agent->Run();
    printf("run agent\n");
    sleep(2);
    p->Report(fd,report::ReportMode::DETAIL);

    sleep(15);
    p->Report(fd,report::ReportMode::DETAIL);
    return 0;
}
