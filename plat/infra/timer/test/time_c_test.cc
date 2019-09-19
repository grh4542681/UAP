#include <unistd.h>
#include <string.h>
#include "timer_time.h"

int main()
{
//    timer::TimeC::GetCurrTime().print();
    std::string now = timer::Time::Now().Format("%Y-%m-%d %H:%M:%S");
    printf("%s\n", now.c_str());
    struct timespec ts;
    memset(&ts, 0, sizeof(struct timespec));
    timer::Time t1 = timer::Time::Now();
    t1.To(&ts);
    printf("%ld, %ld\n",t1.GetSecond(),t1.GetNanoSecond());
    printf("%ld, %ld\n",ts.tv_sec,ts.tv_nsec);
    sleep(10);
    return 0;
}
