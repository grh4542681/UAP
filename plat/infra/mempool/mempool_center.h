#ifndef __MEMPOOL_CENTER_H__
#define __MEMPOOL_CENTER_H__

namespace mempool {

class MemPoolCenter {
public:
    class CenterCache {

    };
    
public:
    static MemPoolCenter* pInstance;

    void report();
    static MemPoolCenter* getInstance();
private:
    MemPoolCenter();
    ~MemPoolCenter();
};


} //namespace end

#endif
