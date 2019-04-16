#include <unistd.h>
#include "time/time_c.h"

int main()
{
//    util::time::TimeC::GetCurrTime().print();
    std::string now = util::time::NowC().Format("%Y-%m-%d %H:%M:%S");
    printf("%s\n", now.c_str());
    sleep(10);
    return 0;
}
