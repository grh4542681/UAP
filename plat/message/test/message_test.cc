#include "message_id.h"

int main() {
    message::MessageId id = message::MessageId::GenMessageIdByTime();
    printf("%ld\n", id.GetId());
  //  message::MessageStreamBinary bs;
    message::MessageStreamMemory bs;
    bs << id;
    message::MessageId id2;
    bs.SetStreamMode(message::MessageStreamMode::Out);
    bs >> id2;
    printf("%ld\n", id2.GetId());
    return 0;
}
