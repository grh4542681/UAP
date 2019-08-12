#ifndef __SEM_EVENT_FD_H__
#define __SEM_EVENT_FD_H__

#include "sem/sem.h"

#include "event_fd.h"

namespace ipc::eventfd {

class SemEventFD : public sem::Sem {
public:
    SemEventFD();
    SemEventFD(std::string name);
    ~SemEventFD();

    EventFD& GetEFD();

    bool IsExist();
    IpcRet Create([[maybe_unused]] size_t semnum, [[maybe_unused]] mode_t mode);
    IpcRet Destroy();
    IpcRet Open(IpcMode mode) {
        return IpcRet::ENONSUPPORT;
    }
    IpcRet Close() {
        return IpcRet::ENONSUPPORT;
    }

protected:
    IpcRet _p(size_t sem_index, timer::Time* overtime);
    IpcRet _v(size_t sem_index);

private:
    EventFD fd_;
};

}


#endif
