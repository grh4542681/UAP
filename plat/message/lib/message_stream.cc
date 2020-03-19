#include "message_stream.h"

namespace message {

MessageStream::MessageStream(Mode smode, size_t size) {
    smode_ = smode;
    limit_size_ = size;
    mempool_ = mempool::Mempool::getInstance();
    cache_ = mempool_->Malloc(limit_size_);
    if (!cache_) {
        ret_ = MessageRet::EMALLOC;
    }
    phead_ = cache_;
    ptail_ = cache_;
    ret_ = MessageRet::SUCCESS;
}

MessageStream::MessageStream() {
    smode_ = Mode::In;
    limit_size_ = 1024*1024;
    mempool_ = mempool::Mempool::getInstance();
    cache_ = mempool_->Malloc(limit_size_);
    if (!cache_) {
        ret_ = MessageRet::EMALLOC;
    }
    phead_ = cache_;
    ptail_ = cache_;
    ret_ = MessageRet::SUCCESS;
}

MessageStream::~MessageStream() {
    if (cache_) {
        mempool_->Free(cache_);
    }
}

size_t MessageStream::GetSize() {
    return (reinterpret_cast<long>(ptail_) - reinterpret_cast<long>(phead_));
}
void* MessageStream::GetPointer() {
    return phead_;
}
MessageStream::Mode& MessageStream::GetStreamMode() {
    return smode_;
}

MessageStream& MessageStream::SetStreamMode(Mode smode) {
    smode_ = smode;
    return *this;
}

void MessageStream::Clean() {
    if (cache_) {
        memset(cache_, 0, limit_size_);
    }
}

MessageStream& MessageStream::operator<<(char& value) {
    _write(&value, sizeof(value));
    return *this;
}
MessageStream& MessageStream::operator>>(char& value) {
    _read(&value, sizeof(value));
    return *this;
}

MessageStream& MessageStream::operator<<(std::string& value) {
    _write(const_cast<char*>(value.c_str()), value.size());
    return *this;
}
MessageStream& MessageStream::operator>>(std::string& value) {
    _read(const_cast<char*>(value.c_str()), value.size());
    return *this;
}

MessageStream& MessageStream::operator<<(short& value) {
    _write(&value, sizeof(value));
    return *this;
}
MessageStream& MessageStream::operator>>(short& value) {
    _read(&value, sizeof(value));
    return *this;
}

MessageStream& MessageStream::operator<<(unsigned short& value) {
    _write(&value, sizeof(value));
    return *this;
}
MessageStream& MessageStream::operator>>(unsigned short& value) {
    _read(&value, sizeof(value));
    return *this;
}

MessageStream& MessageStream::operator<<(int& value) {
    _write(&value, sizeof(value));
    return *this;
}
MessageStream& MessageStream::operator>>(int& value) {
    _read(&value, sizeof(value));
    return *this;
}

MessageStream& MessageStream::operator<<(unsigned int& value) {
    _write(&value, sizeof(value));
    return *this;
}
MessageStream& MessageStream::operator>>(unsigned int& value) {
    _read(&value, sizeof(value));
    return *this;
}

MessageStream& MessageStream::operator<<(long& value) {
    _write(&value, sizeof(value));
    return *this;
}
MessageStream& MessageStream::operator>>(long& value) {
    _read(&value, sizeof(value));
    return *this;
}

MessageStream& MessageStream::operator<<(long long& value) {
    _write(&value, sizeof(value));
    return *this;
}
MessageStream& MessageStream::operator>>(long long& value) {
    _read(&value, sizeof(value));
    return *this;
}

MessageStream& MessageStream::operator<<(unsigned long long& value) {
    _write(&value, sizeof(value));
    return *this;
}
MessageStream& MessageStream::operator>>(unsigned long long& value) {
    _read(&value, sizeof(value));
    return *this;
}

MessageStream& MessageStream::operator<<(float& value) {
    _write(&value, sizeof(value));
    return *this;
}
MessageStream& MessageStream::operator>>(float& value) {
    _read(&value, sizeof(value));
    return *this;
}

MessageStream& MessageStream::operator<<(double& value) {
    _write(&value, sizeof(value));
    return *this;
}
MessageStream& MessageStream::operator>>(double& value) {
    _read(&value, sizeof(value));
    return *this;
}

MessageStream& MessageStream::operator<<(long double& value) {
    _write(&value, sizeof(value));
    return *this;
}
MessageStream& MessageStream::operator>>(long double& value) {
    _read(&value, sizeof(value));
    return *this;
}

MessageStream& MessageStream::operator<<(bool& value) {
    _write(&value, sizeof(value));
    return *this;
}
MessageStream& MessageStream::operator>>(bool& value) {
    _read(&value, sizeof(value));
    return *this;
}

MessageStream& MessageStream::operator<<(MessageRaw& value) {
//    std::string str = value.Serialization();
//    MessageStream::operator<<(str);
    return *this;
}
MessageStream& MessageStream::operator>>(MessageRaw& value) {
//    std::string str = value.Serialization();
//    MessageStream::operator<<(str);
    return *this;
}

size_t MessageStream::_write(void* pdata, size_t size) {
    if (ret_ == MessageRet::EINIT || ret_ == MessageRet::EMALLOC) {
        return 0;
    }
    if (smode_ != Mode::In) {
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

size_t MessageStream::_read(void* pdata, size_t size) {
    if (ret_ == MessageRet::EINIT || ret_ == MessageRet::EMALLOC) {
        return 0;
    }
    if (smode_ != Mode::Out) {
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

size_t MessageStream::_peek(void* pdata, size_t size) {
    if (ret_ == MessageRet::EINIT || ret_ == MessageRet::EMALLOC) {
        return 0;
    }
    if (smode_ != Mode::Out) {
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
}
