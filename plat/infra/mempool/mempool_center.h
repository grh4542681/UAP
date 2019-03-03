#ifndef __MEMPOOL_CENTER_H__
#define __MEMPOOL_CENTER_H__

namespace mempool {

class MemPoolCenter {
public:
    class CenterCache {

    };
    
public:
    MemPoolCenter();
    ~MemPoolCenter();

    void report();
    static MemPoolCenter* getInstance();
private:
};

static MemPoolCenter* pInstance;

} //namespace end

#endif