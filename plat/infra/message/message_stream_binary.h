#ifndef __MESSAGE_STREAM_H__
#define __MESSAGE_STREAM_H__

#include <sys/types.h>
#include <ios>
#include <sstream>

namespace message {

class MessageStreamBinary {
public:
    MessageStreamBinary() {
        ss = std::stringstream(std::ios_base::in|std::ios_base::out|std::ios_base::binary);
    }
    ~MessageStreamBinary() {

    }
/*
    MessageStreamBinary& operator<<(char&& value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator<<(std::string&& value) {
        if (!value.empty()) {
            ss.write(reinterpret_cast<char*>(value.c_str()), value.size());
        }
    }
    MessageStreamBinary& operator<<(short&& value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator<<(unsigned short&& value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator<<(int&& value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator<<(unsigned int&& value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    */
    MessageStreamBinary& operator<<(long value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator>>(long& value) {
        ss.read(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    /*
    MessageStreamBinary& operator<<(unsigned long long&& value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator<<(float&& value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator<<(double&& value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator<<(long double&& value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator<<(bool&& value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    */
    /*
    MessageStreamBinary& operator<<(const void* value, size_t size) {
        if (value) {
            ss.write(reinterpret_cast<char*>(value), size);
        }
        return *this;
    }
    MessageStreamBinary& operator<<(MessageRaw&& value) {
        value.Serialization(*this);
        return *this;
    }
    */


    template < typename T >
    MessageStreamBinary& Pop(T data) {
        ss >> data;
    }

private:
    std::stringstream ss;

};

}

#endif
