#include "message_return.h"

namespace message {

MessageRet::ECodeMapType MessageRet::ECodeMap = {
    { ECode::MESSAGE_EMSNOSPACE, "" },
    { ECode::MESSAGE_EMSNOMESSG, "" },
    { ECode::MESSAGE_EMSMODE, "" },
};

}
