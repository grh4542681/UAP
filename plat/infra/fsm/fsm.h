#ifndef __FSM_H__
#define __FSM_H__

#include <string>
#include <map>

#include "fsm_log.h"
#include "fsm_return.h"

#include "fsm_trace.h"
#include "fsm_state.h"
#include "fsm_event.h"
#include "fsm_transition.h"

namespace fsm {

template <typename EventType, typename StateType>
class Fsm {
public:
    Fsm(const StateType& state) : state_(state) { };
    ~Fsm() { };

    StateType& GetState() {
        return state_;
    }

    FsmRet AddEvent(const FsmEvent<EventType>& event) {
        auto event_it = event_map_.find(event.GetEvent());
        if (event_it != event_map_.end()) {
            event_map_.insert({event.GetEvent(), event});
        } else {
            event_it.second = event;
        }
        return FsmRet::SUCCESS;
    }
    FsmRet DelEvent(const EventType& event) {
        auto event_it = event_map_.find(event);
        if (event_it != event_map_.end()) {
            for (auto trans_it : trans_map_) {
                if (trans_it.first.get<EventType>() == event) {
                    return FsmRet::FSM_EVENT_ETRANSEXIST;
                }
            }
            event_map_.erase(event_it);
        }
        return FsmRet::SUCCESS;
    }

    FsmRet AddState(const FsmState<StateType>& state) {
        auto state_it = state_map_.find(state.GetState());
        if (state_it != state_map_.end()) {
            state_map_.insert({state.GetState(). state});
        } else {
            state_it.second = state;
        }
        return FsmRet::SUCCESS;
    }
    FsmRet DelState(const StateType& state) {
        auto state_it = state_map_find(state);
        if (state_it != state_map_.end()) {
            for (auto trans_it : trans_map_) {
                if (trans_it.first.get<StateType>() == state) {
                    return FsmRet::FSM_EVENT_ETRANSEXIST;
                }
            }
            state_map_.erase(state_it);
        }
        return *this;
    }

    FsmRet AddTransition(const FsmTransition<EventType, StateType>& trans) {
        EventType event = trans.GetEvent();
        StateType state = trans.GetState();

        auto event_it = event_map_.find(event);
        if (event_it == event_map_.end()) {
            return FsmRet::FSM_EVENT_ENOTEXIST;
        }
        auto state_it = state_map_.find(state);
        if (state_it == state_map_.end()) {
            return FsmRet::FSM_STATE_ENOTEXIST;
        }

        auto trans_it = trans_map_.find(std::pair<EventType, StateType>(event, state));
        if (trans_it == trans_map_.end()) {
            trans_map_.insert({std::pair<EventType, StateType>(event, state), trans});
        } else {
            trans_it.second() = trans;
        }
        return FsmRet::SUCCESS;
    }
    FsmRet DelTransition(const EventType& event, const StateType& state) {
        auto trans_it = trans_map_.find(std::pair<EventType, StateType>(event, state));
        if (trans_it == trans_map_.end()) {
            return FsmRet::SUCCESS;
        } else {
            trans_map_.erase(trans_it);
        }
        return FsmRet::SUCCESS;
    }
    Fsm& Clear() {
        event_map_.clear();
        state_map_.clear();
        trans_map_.clear();
        return *this;
    }

    FsmRet TriggerEvent(const EventType& event) {
        auto trans_it = trans_map_.find(std::pair<EventType, StateType>(event, state_));
        if (trans_it == trans_map_.end()) {
            return FsmRet::FSM_TRANS_ENOTEXIST;
        } else {
            if (trans_it.Check != nullptr) {
                if (!trans_it.Check()) {
                    //check error;
                    return FsmRet::FSM_TRANS_ECHECK;
                }
            }
            auto state_it = state_map_.find(state_);
            if (state_it == state_map_.end()) {
                return FsmRet::FSM_STATE_ENOTEXIST;
            } else {
                if (state_it.Exit != nullptr) {
                    if (!state_it.Exit()) {
                        return FsmRet::FSM_STATE_EEXIT;
                    }
                }
            }
        }
        return FsmRet::SUCCESS;
    }

    bool ChangeState(const StateType& state) {
        return true;
    }
private:
    StateType state_;

    std::map<EventType, FsmEvent<EventType>> event_map_;
    std::map<StateType, FsmState<StateType>> state_map_;
    std::map<std::pair<EventType, StateType>, FsmTransition<EventType, StateType>> trans_map_;
};

}

#endif
