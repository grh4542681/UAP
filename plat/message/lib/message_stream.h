#ifndef __MESSAGE_STREAM_H__
#define __MESSAGE_STREAM_H__

#include "mempool.h"

#include "message_return.h"
#include "message_raw.h"

namespace message {

class MessageStream {
public:
    class enum Mode {
        In,
        Out,
    };
public:
    MessageStream(Mode smode, size_t size);
    MessageStream();
    ~MessageStream();

    size_t GetSize();
    void* GetPointer();
    Mode& GetStreamMode();

    MessageStream& SetStreamMode(Mode smode);
    void Clean();

    MessageStream& operator<<(char& value);
    MessageStream& operator<<(char& value, size_t size);
    MessageStream& operator>>(char& value);
    MessageStream& operator>>(char& value, size_t size);

    MessageStream& operator<<(std::string& value);
    MessageStream& operator<<(std::string& value, size_t size);
    MessageStream& operator>>(std::string& value);
    MessageStream& operator>>(std::string& value, size_t size);
    
    MessageStream& operator<<(short& value);
    MessageStream& operator<<(short& value, size_t size);
    MessageStream& operator>>(short& value);
    MessageStream& operator>>(short& value, size_t size);

    MessageStream& operator<<(unsigned short& value);
    MessageStream& operator<<(unsigned short& value, size_t size);
    MessageStream& operator>>(unsigned short& value);
    MessageStream& operator>>(unsigned short& value, size_t size);

    MessageStream& operator<<(int& value);
    MessageStream& operator<<(int& value, size_t size);
    MessageStream& operator>>(int& value);
    MessageStream& operator>>(int& value, size_t size);

    MessageStream& operator<<(unsigned& int value);
    MessageStream& operator<<(unsigned& int value, size_t size);
    MessageStream& operator>>(unsigned& int value);
    MessageStream& operator>>(unsigned& int value, size_t size);

    MessageStream& operator<<(long& value);
    MessageStream& operator<<(long& value, size_t size);
    MessageStream& operator>>(long& value);
    MessageStream& operator>>(long& value, size_t size);

    MessageStream& operator<<(long long& value);
    MessageStream& operator<<(long long& value, size_t size);
    MessageStream& operator>>(long long& value);
    MessageStream& operator>>(long long& value, size_t size);

    MessageStream& operator<<(unsigned long long& value);
    MessageStream& operator<<(unsigned long long& value, size_t size);
    MessageStream& operator>>(unsigned long long& value);
    MessageStream& operator>>(unsigned long long& value, size_t size);

    MessageStream& operator<<(float& value);
    MessageStream& operator<<(float& value, size_t size);
    MessageStream& operator>>(float& value);
    MessageStream& operator>>(float& value, size_t size);

    MessageStream& operator<<(double& value);
    MessageStream& operator<<(double& value, size_t size);
    MessageStream& operator>>(double& value);
    MessageStream& operator>>(double& value, size_t size);

    MessageStream& operator<<(long double& value);
    MessageStream& operator<<(long double& value, size_t size);
    MessageStream& operator>>(long double& value);
    MessageStream& operator>>(long double& value, size_t size);

    MessageStream& operator<<(bool& value);
    MessageStream& operator<<(bool& value, size_t size);
    MessageStream& operator>>(bool& value);
    MessageStream& operator>>(bool& value, size_t size);

    MessageStream& operator<<(MessageRaw& value);
    MessageStream& operator<<(MessageRaw& value, size_t size);
 //   MessageStream& operator>>(MessageRaw& value);
 //   MessageStream& operator>>(MessageRaw& value, size_t size);

    template < typename T >
    MessageStream& Put(T* value, size_t size) {
        _write(reinterpret_cast<void*>(value), size);
        return *this;
    }

    template < typename T >
    MessageStream& Get(T* value, size_t size) {
        _read(reinterpret_cast<void*>(value), size);
        return *this;
    }

private:
    MessageStream(MessageStream& other) { }

    size_t _write(void* pdata, size_t size);
    size_t _read(void* pdata, size_t size);
    size_t _peek(void* pdata, size_t size);

private:
    MessageRet ret_;
    Mode smode_;
    size_t limit_size_;
    void* cache_;
    void* phead_;
    void* ptail_;

    mempool::MemPool* mempool_;
};

}

#endif
