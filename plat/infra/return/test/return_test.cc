#include "return.h"
#include <stdio.h>

ret::Return test() {
    return ret::Return::EMALLOC;
}

int main()
{
    ret::Return ret = test();
    printf("%d %s\n",ret.Code(),ret.Message().c_str());
    return 0;
}
