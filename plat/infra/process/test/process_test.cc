#include "process_info.h"

int main()
{
    process::ProcessInfo* p = process::ProcessInfo::getInstance();
    printf("pid %d ppid %d name %s pname %s\n", p->GetPid(), p->GetPPid(), p->GetName().c_str(), p->GetProcessName().c_str());
    return 0;
}
