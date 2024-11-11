#pragma once

#include <string>

#include "utils/interface_state.h"
#include "utils/statemachine.h"

class State : public IState {
   public:
    State() {};
    State(std::string name, StateMachine* sm) : IState(name), sm_(sm) {};

    void transitionTo(IState* dest_state) {
        printf("transitionTo: %s \n", dest_state->getName());
        sm_->key_input.clear();
        sm_->getState()->exit();
        sm_->setState(dest_state);
        sm_->getState()->enter();
    }

    // TODO: should use enum
    bool getInput(int k) {
        bool ret = false;
        if (sm_->key_input.find(k) != sm_->key_input.end()) {
            ret = true;
            sm_->key_input.erase(k);
        }
        return ret;
    }

   private:
    StateMachine* sm_;
};
