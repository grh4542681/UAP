#ifndef __SHM_MODE_H__
#define __SHM_MODE_H__

namespace ipc::shm {

enum class ShmMode : int {
    READ_ONLY = 0x01,
    WRITE_ONLY = 0x02,
    READ_WRITE = 0x01 | 0x02,
    CREAT = 0x08,
    EXIST = 0x10, 
};

int operator|(ShmMode a, ShmMode b) {
    return ((int)a | (int)b);
}
int operator|(int a, ShmMode b) {
    return (a | (int)b);
}
int operator|(ShmMode a, int b) {
    return ((int)a | b);
}
bool operator==(int a, ShmMode b) {
    return (a == (int)b);
}
bool operator==(ShmMode a, int b) {
    return ((int)a == b);
}

}

#endif