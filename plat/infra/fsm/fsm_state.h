#ifndef __FSM_STATE_H__
#define __FSM_STATE_H__

#include <string>
#include <functional>

namespace fsm {

template <typename StateType, typename = typename std::enable_if<std::is_enum<StateType>::value>::type>
class FsmState {
public:
    FsmState(StateType state) : state_(state) {

    }
    ~FsmState() {

    }

public:
    std::function<bool(FsmState& prev)> Enter = nullptr;
    std::function<bool(FsmState& next)> Exit = nullptr;
    std::function<void(FsmState& curr)> Update= nullptr;
private:
    StateType state_;
    std::string describe_;
};

}

#endif
