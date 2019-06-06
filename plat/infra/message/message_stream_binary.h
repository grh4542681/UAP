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
    MessageStreamBinary& operator<<(char value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator<<(short value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator<<(unsigned short value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator<<(int value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator<<(unsigned int value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator<<(long value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator<<(long long value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator<<(unsigned long long value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator<<(float value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator<<(double value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator<<(long double value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator<<(bool value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator<<(void* value) {
        ss.write(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }


    MessageStreamBinary& operator>>(char& value) {
        ss.read(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator>>(short& value) {
        ss.read(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator>>(unsigned short& value) {
        ss.read(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator>>(int& value) {
        ss.read(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator>>(unsigned int& value) {
        ss.read(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator>>(long& value) {
        ss.read(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator>>(long long& value) {
        ss.read(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator>>(unsigned long long& value) {
        ss.read(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator>>(float& value) {
        ss.read(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator>>(double& value) {
        ss.read(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator>>(long double& value) {
        ss.read(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator>>(bool& value) {
        ss.read(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }
    MessageStreamBinary& operator>>(void*& value) {
        ss.read(reinterpret_cast<char*>(&value), sizeof(value));
        return *this;
    }


private:
    std::stringstream ss;

};

}

#endif
