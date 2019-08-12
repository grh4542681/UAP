#include <unistd.h>
#include <string.h>
#include "time_c.h"

int main()
{
//    timer::TimeC::GetCurrTime().print();
    std::string now = timer::NowC().Format("%Y-%m-%d %H:%M:%S");
    printf("%s\n", now.c_str());
    struct timespec ts;
    memset(&ts, 0, sizeof(struct timespec));
    timer::Time t1 = timer::NowC();
    t1.To<struct timespec>(&ts);
    printf("%ld, %ld\n",t1.GetSecond(),t1.GetNanoSecond());
    printf("%ld, %ld\n",ts.tv_sec,ts.tv_nsec);
    sleep(10);
    return 0;
}