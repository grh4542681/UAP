#include <unistd.h>
#include "ipc_mode.h"
#include "shm/shm_sysv.h"

int main()
{
    printf("%s\n", typeid(ipc::shm::ShmSysV).name());
    ipc::shm::ShmSysV shm("test");
    ipc::IpcRet ret = shm.Create(0666, 1024);
    printf("%d\n", ret);
    sleep(10);
    shm.Open(ipc::IpcMode::READ_WRITE);
    sleep(10);
    shm.Close();
    sleep(20);
    shm.Destroy();
    return 0;
}
