#ifndef __MESSAGE_IDENTITY_H__
#define __MESSAGE_IDENTITY_H__

namespace message {

class MessageIdentity {
public:
    enum class Role {
        Root,
        Administrator,
        Operator,
        Visitor,
    };

    MessageIdentity();
    ~MessageIdentity();

private:
    Role role_;
};

}

#endif
