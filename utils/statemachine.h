#pragma once

#include <unordered_set>

#include "utils/interface_state.h"

class StateMachine {
   public:
    StateMachine() {};
    std::unordered_set<int> key_input{}; // TODO: optimize

    virtual void start() {
        printf("StateMachine: start\n");
        mState_->enter();
    }

    virtual void process() const { mState_->process(); }

    void setInitState(IState* initState) { mState_ = initState; }

    void setState(IState* destState) { mState_ = destState; }

    IState* getState() { return mState_; }

   private:
    IState* mState_;
};
