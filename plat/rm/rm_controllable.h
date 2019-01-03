#ifndef _RM_CONTROLLABLE_H__
#define _RM_CONTROLLABLE_H__

#include <list>
#include <map>
#include <sys/types.h>
#include <pthread.h>
#include "rm_return.h"
#include "rm_common.h"

namespace rm {

class RmControlElement {
    ResourceType rtype_;
    pid_t pid_;
    pthread_t tid_;
};

class RmTransferElement {
    ResourceType rtype_;
    ControlType ctype_;
};

//Inherited only need to implement the interface, not extendable
class RmControlApi {
public:
    ResourceType type_;
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
    std::map<ResourceType, std::map<int, RmControlElement*>> rm_map_;
};

template <typename T>
RmRet ApplyResource(T*);

}//namespace rm end

#endif
