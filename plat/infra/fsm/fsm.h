#ifndef __FSM_H__
#define __FSM_H__

#include <string>
#include <map>

#include "fsm_trace.h"
#include "fsm_state.h"
#include "fsm_event.h"
#include "fsm_transition.h"

namespace fsm {

template <typename EventType, typename StateType>
class Fsm {
public:
    Fsm() { };
    ~Fsm() { };

    bool TranState(StateType state);
    bool ExecEvent(EventType event);

    bool AddEvent(const FsmEvent<EventType>& event) {
        auto event_it = event_map_.find(event.GetEvent());
        if (event_it != event_map_.end()) {
            event_map_.insert({event.GetEvent(), event});
        } else {
            event_it.second = event;
        }
        return true;
    }
    Fsm& DelEvent(EventType& event) {
        auto event_it = event_map_.find(event);
        if (event_it != event_map_.end()) {
            event_map_.erase(event_it);
        }
        return *this;
    }
    Fsm& ClearEvent() {
        event_map_.clear();
        return *this;
    }

    bool AddState(const FsmState<StateType>& state) {
        auto state_it = state_map_.find(state.GetState());
        if (state_it != state_map_.end()) {
            state_map_.insert({state.GetState(). state});
        } else {
            state_it.second = state;
        }
        return true;
    }
    Fsm& DelState(StateType& state) {
        auto state_it = state_map_find(state);
        if (state_it != state_map_.end()) {
            state_map_.erase(state_it);
        }
        return *this;
    }
    Fsm& ClearState() {
        state_map_.clear();
        return *this;
    }

    bool AddTransition(const FsmTransition<EventType, StateType>& trans) {
        EventType event = trans.GetEvent();
        StateType state = trans.GetState();

        auto event_it = event_map_.find(event);
        if (event_it == event_map_.end()) {
            return false;
        }
        auto state_it = state_map_.find(state);
        if (state_it == state_map_.end()) {
            return false;
        }

        auto trans_it = trans_map_.find(std::pair<EventType, StateType>(event, state));
        if (trans_it == trans_map_.end()) {
            trans_map_.insert({std::pair<EventType, StateType>(event, state), trans});
        } else {
            trans_it.second() = trans;
        }
        return true;
    }

private:
    std::map<EventType, FsmEvent<EventType>> event_map_;
    std::map<StateType, FsmState<StateType>> state_map_;
    std::map<std::pair<EventType, StateType>, FsmTransition<EventType, StateType>> trans_map_;
};

}

#endif
