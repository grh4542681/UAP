#ifndef __MEMPOLL_UNTRACK_H__
#define __MEMPOLL_UNTRACK_H__

namespace mempool {

class MemPoolUntrack {
public:

    static MemPoolUntrack* getInstance();

private:
    MemPoolUntrack();
    ~MemPoolUntrack();

    static MemPoolUntrack* pInstance;
};

};

#endif
