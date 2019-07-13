#ifndef __SEM_EVENTFD_H__
#define __SEM_EVENTFD_H__

#include <sys/eventfd.h>
#include "sem/sem.h"

namespace ipc::sem {

class SemEventfd : public Sem {
public:
    SemEventfd();
    ~SemEvebtfd();
private:
};

}

#endif
