#include <stdlib.h>
#include <unistd.h>

#include "ipc_mode.h"
#include "msg/msg_shm.h"

int main()
{
    ipc::msg::MsgShm ms("msgshm_test");
    ms.Create(1024,0777);
    ms.Open(ipc::IpcMode::READ_WRITE);
    sleep(15);
    ms.Close();
    ms.Destroy();
    return 0;
}
