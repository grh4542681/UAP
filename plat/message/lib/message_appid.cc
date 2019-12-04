#include "message_appid.h"

namespace message {

MessageAppid::AppidMapType MessageAppid::AppidMap = {
    { Appid::Unknow, "Unknow application ID." },

    { Appid::MessageInternal, "Message internal application ID." },
};

}
