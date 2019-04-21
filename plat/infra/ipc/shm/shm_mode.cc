#include "shm_mode.h"

namespace ipc::shm {

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
