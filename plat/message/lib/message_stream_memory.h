#ifndef __MESSAGE_STREAM_MEMORY_H__
#define __MESSAGE_STREAM_MEMORY_H__

#include "mempool.h"

#include "message_return.h"
#include "message_stream_mode.h"

namespace message {

class MessageStreamMemory {
public:
    MessageStreamMemory(MessageStreamMode smode, size_t size) {
        smode_ = smode;
        limit_size_ = size;
        mempool_ = mempool::MemPool::getInstance();
        cache_ = mempool_->Malloc(limit_size_);
        if (!cache_) {
            ret_ = MessageRet::EMALLOC;
        }
        phead_ = cache_;
        ptail_ = cache_;
        ret_ = MessageRet::SUCCESS;
    }

    MessageStreamMemory() {
        smode_ = MessageStreamMode::In;
        limit_size_ = 1024*1024;
        mempool_ = mempool::MemPool::getInstance();
        cache_ = mempool_->Malloc(limit_size_);
        if (!cache_) {
            ret_ = MessageRet::EMALLOC;
        }
        phead_ = cache_;
        ptail_ = cache_;
        ret_ = MessageRet::SUCCESS;
    }

    ~MessageStreamMemory() {
        if (cache_) {
            mempool_->Free(cache_);
        }
    }

    size_t GetSize() {
        return (reinterpret_cast<long>(ptail_) - reinterpret_cast<long>(phead_));
    }
    void* GetPointer() {
        return phead_;
    }
    MessageStreamMode& GetStreamMode() {
        return smode_;
    }

    MessageStreamMemory& SetStreamMode(MessageStreamMode smode) {
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

    MessageStreamMemory& operator>>(char& value) {
        _read(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator>>(short& value) {
        _read(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator>>(unsigned short& value) {
        _read(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator>>(int& value) {
        _read(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator>>(unsigned int& value) {
        _read(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator>>(long& value) {
        _read(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator>>(long long& value) {
        _read(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator>>(unsigned long long& value) {
        _read(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator>>(float& value) {
        _read(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator>>(double& value) {
        _read(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator>>(long double& value) {
        _read(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator>>(bool& value) {
        _read(&value, sizeof(value));
        return *this;
    }
    MessageStreamMemory& operator>>(void*& value) {
        _read(&value, sizeof(value));
        return *this;
    }

    template < typename T >
    MessageStreamMemory& Put(T* value, size_t size) {
        _write(reinterpret_cast<void*>(value), size);
        return *this;
    }

    template < typename T >
    MessageStreamMemory& Get(T* value, size_t size) {
        _read(reinterpret_cast<void*>(value), size);
        return *this;
    }

    void Clean() {
        if (cache_) {
            memset(cache_, 0, limit_size_);
        }
    }

private:
    MessageStreamMemory(MessageStreamMemory& other) { }

    size_t _write(void* pdata, size_t size) {
        if (ret_ == MessageRet::EINIT || ret_ == MessageRet::EMALLOC) {
            return 0;
        }
        if (smode_ != MessageStreamMode::In) {
            ret_ = MessageRet::MESSAGE_EMSMODE;
            return 0;
        }
        if (size > (limit_size_ - (reinterpret_cast<long>(ptail_) - reinterpret_cast<long>(phead_))) -1 ) {
            ret_ = MessageRet::MESSAGE_EMSNOSPACE;
            return 0;
        }
        memcpy(ptail_, pdata, size);
        ptail_ = reinterpret_cast<void*>(reinterpret_cast<long>(ptail_) + size);
        ret_ = MessageRet::SUCCESS;
        return size;
    }

    size_t _read(void* pdata, size_t size) {
        if (ret_ == MessageRet::EINIT || ret_ == MessageRet::EMALLOC) {
            return 0;
        }
        if (smode_ != MessageStreamMode::Out) {
            ret_ = MessageRet::MESSAGE_EMSMODE;
            return 0;
        }
        if (size > static_cast<size_t>((reinterpret_cast<long>(ptail_) - reinterpret_cast<long>(phead_)))) {
            ret_ = MessageRet::MESSAGE_EMSNOSPACE;
            return 0;
        }
        memcpy(pdata, phead_, size);
        phead_ = reinterpret_cast<void*>(reinterpret_cast<long>(phead_) + size);
        ret_ = MessageRet::SUCCESS;
        return size;
    }

    size_t _peek(void* pdata, size_t size) {
        if (ret_ == MessageRet::EINIT || ret_ == MessageRet::EMALLOC) {
            return 0;
        }
        if (smode_ != MessageStreamMode::Out) {
            ret_ = MessageRet::MESSAGE_EMSMODE;
            return 0;
        }
        if (size > static_cast<size_t>((reinterpret_cast<long>(ptail_) - reinterpret_cast<long>(phead_)))) {
            ret_ = MessageRet::MESSAGE_EMSNOMESSG;
            return 0;
        }
        memcpy(pdata, phead_, size);
        ret_ = MessageRet::SUCCESS;
        return size;
    }

private:
    MessageRet ret_;
    MessageStreamMode smode_;
    size_t limit_size_;
    void* cache_;
    void* phead_;
    void* ptail_;

    mempool::MemPool* mempool_;
};

}

#endif
