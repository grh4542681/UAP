#include "return.h"
#include <stdio.h>

int main()
{
    ret::Return ret(ret::Return::ECode::EBADARGS);
    printf("%d %s\n",ret.Code(),ret.Message().c_str());
    return 0;
}
