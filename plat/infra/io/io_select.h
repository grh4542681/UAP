#ifndef __IO_SELECT_H__
#define __IO_SELECT_H__

namespace io {

typedef struct _SelectEvent {
    FD fd;
} SelectEvent;

class Select {
public:
    Select();
    ~Select();

};

}

#endif
