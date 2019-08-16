#ifndef __MESSAGE_AGENT_STATE_H__
#define __MESSAGE_AGENT_STATE_H__

namespace message {

enum class MessageAgentState : int {
    Uninitialized,
    Ready,
    ConnectServer,
    Listening,
    DisconnectServer,
    Error,
};

}

#endif
