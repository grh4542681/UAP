#include "fsm_return.h"

namespace fsm {

FsmRet::ECodeMapType FsmRet::ECodeMap = {
    { ECode::FSM_EVENT_ETRANSEXIST, "There exists a trans corresponding to event" },
    { ECode::FSM_STATE_ETRANSEXIST, "There exists a trans corresponding to state" },
};

}
