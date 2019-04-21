#include "file_mode.h"

namespace file {

int operator|(FileMode a, FileMode b) {
    return ((int)a | (int)b);
}
int operator|(int a, FileMode b) {
    return (a | (int)b);
}
int operator|(FileMode a, int b) {
    return ((int)a | b); 
}
bool operator==(int a, FileMode b) {
    return (a == (int)b);
}
bool operator==(FileMode a, int b) {
    return ((int)a == b); 
}

}
