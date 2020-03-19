#ifndef __MESSAGE_AUTHENTICATE_H__
#define __MESSAGE_AUTHENTICATE_H__

#include "message_identity.h"

namespace message {

class MessageAuthenticate {
public:
    MessageAuthenticate();
    ~MessageAuthenticate();

    bool Authenticate(MessageIdentity&& identity) {
        
    }
private:
    MessageIdentity::Role role_;
};

}

#endif
