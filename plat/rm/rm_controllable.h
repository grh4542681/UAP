#ifndef _RM_CONTROLLABLE_H__
#define _RM_CONTROLLABLE_H__

#include "rm_return.h"

namespace rm {

class RMControllable{

public:
    RMControllable(){ }
    virtual ~RMControllable(){ }

    virtual RmRet create() = 0;
    virtual RmRet destory()= 0;
//    virtual RmRet check() = 0;
};

}//namespace rm end

#endif
