#include <unistd.h>
#include "time/time_c.h"

int main()
{
    util::time::TimeC::GetCurrTime().print();
    sleep(10);
    return 0;
}
