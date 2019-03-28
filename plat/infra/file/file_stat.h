#ifndef __FILE_STATE_H__
#define __FILE_STATE_H__

namespace file {

enum class FileState {
    INVALID,
    NONE,
    INTEROPENED,
    INTERCLOSEED,
    EXTEROPENED,
    EXTERCLOSEED,


    UNKNOW
};

}

#endif
