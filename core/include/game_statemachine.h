#pragma once

#include "utils/statemachine.h"
#include "utils/state.h"

class GameSM : public StateMachine {
public:
    GameSM();

    void start() override {
        printf("GameSM: start\n");
        getState()->enter();
    }

    void process() const override {
        StateMachine::process();
    }

    class Init : public State {
    public:
        Init() {};
        Init(StateMachine* sm) : State("Init", sm) {};
        void enter() override;
        void process() override;
        void exit() override;
    };

    class Login : public State {
    public:
        Login() {};
        Login(StateMachine* sm) : State("Login", sm) {};
        void enter() override;
        void process() override;
        void exit() override;
    };

    class Loading : public State {
    public:
        Loading() {};
        Loading(StateMachine* sm) : State("Loading", sm) {};
        void enter() override;
        void process() override;
        void exit() override;
    };

    class GameStart : public State {
    public:
        GameStart() {};
        GameStart(StateMachine* sm) : State("GameStart", sm) {};
        void enter() override;
        void process() override;
        void exit() override;
    };

    class GameWin : public State {
    public:
        GameWin() {};
        GameWin(StateMachine* sm) : State("GameWin", sm) {};
        void enter() override;
        void process() override;
        void exit() override;
    };

    class GameLose : public State {
    public:
        GameLose() {};
        GameLose(StateMachine* sm) : State("GameLose", sm) {};
        void enter() override;
        void process() override;
        void exit() override;
    };

    class GameOver : public State {
    public:
        GameOver() {};
        GameOver(StateMachine* sm) : State("GameOver", sm) {};
        void enter() override;
        void process() override;
        void exit() override;
    };
};
