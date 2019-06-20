#ifndef __MESSAGE_CTRL_H__
#define __MESSAGE_CTRL_H__

namespace message {

class MessageCtrl {
public:
    MessageCtrl();
    ~MessageCtrl();

    static MessageCtrl* getInstance();
private:
    static MessageCtrl* pInstance;
};

}

#endif
