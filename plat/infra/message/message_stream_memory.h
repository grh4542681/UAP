#define __MESSAGE_STREAM_MEMORY_H__
#define __MESSAGE_STREAM_MEMORY_H__

#include "mempool_return.h"
#include "mempool_stream_mode.h"

namespace message {

class MessageStreamMemory {
public:
    MessageStreamMemory(MessageStreamMode smode, size_t size) {
        smode_ = smode;
        size_ = size;
        use_size_ = 0;
        mempool_ = mempool::MemPool::getInstance();
        cache_ = mempool->Malloc(size_);
        if (!cache_) {
            ret_ = MessageRet::EMEMORY;
        }
        pcursor_ = cache_;
    }

    MessageStreamMemory() {
        smode_ = MessageStreamMode::In;
        size_ = 1024*1024;
        use_size_ = 0;
        mempool_ = mempool::MemPool::getInstance();
        cache_ = mempool->Malloc(size_);
        if (!cache_) {
            ret_ = MessageRet::EMEMORY;
        }
        phead_ = cache_;
        ptail_ = cache_;
    }

    ~MessageStreamMemory() {
        if (cache_) {
            mempool_->Free(cache);
        }
    }

    size_t GetSize() {
        return ptail_ - phead_;
    }
    void* GetPointer() {
        return phead_;
    }
    MessageStreamMode& GetStreamMode() {
        return smode_;
    }

    MessageStreamMemory& SetStreamMode(MessageStreamMode& smode) {
        smode_ = smode;
        return *this;
    }

    MessageStreamMemory& operator<<(char value) {
        _write(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator<<(short value) {
        _write(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator<<(unsigned short value) {
        _write(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator<<(int value) {
        _write(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator<<(unsigned int value) {
        _write(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator<<(long value) {
        _write(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator<<(long long value) {
        _write(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator<<(unsigned long long value) {
        _write(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator<<(float value) {
        _write(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator<<(double value) {
        _write(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator<<(long double value) {
        _write(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator<<(bool value) {
        _write(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator<<(void* value) {
        _write(&value, sizeof(value));
        return *this;
    }


    void Clean() {
        if (cache_) {
            memset(cache, 0, size_);
            use_size_ = 0;
        }
    }

private:
    MessageStreamMemory(MessageStreamMemory& other) { }

    size_t _write(void* pdata, size_t size) {
        if (ret_ == MessageRet::EINIT || ret_ == MessageRet::EMEMORY) {
            return 0;
        }
        if (smode_ != MessageStreamMode::In) {
            ret_ = MessageRet::EMSMODE;
            return 0;
        }
        if (size > (limit_size_ - (ptail_ - phread_)) -1 ) {
            ret_ = MessageRet::EMSNOSPACE;
            return 0;
        }
        memcpy(ptail_, pdate, size);
        ptail_ += size;
        use_size_ += size;
        ret_ = MessageRet::SUCCESS;
    }

    size_t _read(void* pdata, size_t size) {
        if (ret_ == MessageRet::EINIT || ret_ == MessageRet::EMEMORY) {
            return 0;
        }
        if (smode_ != MessageStreamMode::Out) {
            ret_ = MessageRet::EMSMODE;
            return 0;
        }
        if (size > (ptail_ - phead_)) {
            ret_ = MessageRet::EMSNOMESSG;
            return 0;
        }
        memcpy(pdata, phead_, size);
        phead_ += size;
        use_size -= size;
        ret_ = MessageRet::SUCCESS;
    }

    size_t _peek(void* pdata, size_t size) {
        if (ret_ == MessageRet::EINIT || ret_ == MessageRet::EMEMORY) {
            return 0;
        }
        if (smode_ != MessageStreamMode::Out) {
            ret_ = MessageRet::EMSMODE;
            return 0;
        }
        if (size > (ptail_ - phead_)) {
            ret_ = MessageRet::EMSNOMESSG;
            return 0;
        }
        memcpy(pdata, phead_, size);
        ret_ = MessageRet::SUCCESS;
    }

private:
    MessageRet ret_;
    MessageStreamMode smode_;
    size_t limit_size_;
    void* cache_;
    void* phead_;
    void* ptail_;

    mempool::MemPool* mempool_;
}

}

#endif
