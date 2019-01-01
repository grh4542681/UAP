#ifndef _RM_CONTROLLABLE_H__
#define _RM_CONTROLLABLE_H__

#include <list>
#include <map>
#include "rm_return.h"
#include "rm_common.h"

namespace rm {

class RmControlElement {
    ResourceType type;
    pid_t pid;
    pthread_t tid;
};

class RmTransferElement {
    ResourceType rtype;
    ControlType ctype;
};

class RmControlApi {
    ResourceType type;
    virtual RmRet Create(RmTransferElement*);
    virtual RmRet Delete(RmTransferElement*);
    virtual RmRet Update(RmTransferElement*);
    virtual RmRet Select(RmTransferElement*);
    virtual RmRet Show(RmTransferElement*);
};

class RMControllable{

public:
    RMControllable(){ }
    ~RMControllable(){ }
private:
    std::map<ResourceType, RmControlApi*> api_map_;
    std::map<ResourceType,std::list<int,RmControlElement*>> rm_map_;
};

}//namespace rm end

#endif
