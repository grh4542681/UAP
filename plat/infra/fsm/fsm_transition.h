#ifndef __FSM_TRANSITION_H__
#define __FSM_TRANSITION_H__

#include <string>

namespace fsm {

template <typename EventType, typename StateType> class Fsm;

template <typename EventType, typename StateType, 
            typename = typename std::enable_if<std::is_enum<EventType>::value && std::is_enum<StateType>::value>::type>
class FsmTransition {
public:
    FsmTransition(EventType event, StateType state, StateType to_state)
            : event_(event), state_(state), to_state_(to_state) {

    }
    ~FsmTransition() {

    }

    EventType& GetEvent() {
        return event_;
    }
    StateType& GetState() {
        return state_;
    }
public:
    std::function<bool(Fsm<EventType, StateType>*)> Check = nullptr;
    std::function<bool(Fsm<EventType, StateType>*)> Complete = nullptr;
private:
    EventType event_;
    StateType state_;
    StateType to_state_;
    std::string describe_;
};

}

#endif
