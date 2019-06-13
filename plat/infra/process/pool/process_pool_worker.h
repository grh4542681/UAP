#ifndef __PROCESS_POOL_WORKER_H__
#define __PROCESS_POOL_WORKER_H__

#include "process_child.h"

namespace process::pool {

class ProcessPoolWorker {
public:
    ProcessPoolWorker();
    ~ProcessPoolWorker();

    ProcessRet Run();
protected:
    ProcessRet _main();
};

}

#endif
