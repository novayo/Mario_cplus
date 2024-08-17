#include "core/include/game_statemachine.h"

#include "core/include/sdl_handler.h"

static GameSM::Init mInitState_;
static GameSM::Login mLoginState_;
static GameSM::Loading mLoadingState_;
static GameSM::GameStart mGameStartState_;
static GameSM::GameWin mGameWinState_;
static GameSM::GameLose mGameLoseState_;
static GameSM::GameOver mGameOverState_;

GameSM::GameSM() {
    mInitState_ = GameSM::Init(this);
    mLoginState_ = GameSM::Login(this);
    mLoadingState_ = GameSM::Loading(this);
    mGameStartState_ = GameSM::GameStart(this);
    mGameWinState_ = GameSM::GameWin(this);
    mGameLoseState_ = GameSM::GameLose(this);
    mGameOverState_ = GameSM::GameOver(this);

    setInitState(&mInitState_);
}

void GameSM::Init::enter() { printf("GameState: Enter %s\n", getName()); }

void GameSM::Init::process() {
    printf("GameState: Process %s\n", getName());
    transitionTo(&mLoginState_);
}

void GameSM::Init::exit() { printf("GameState: Exit %s\n", getName()); }

void GameSM::Login::enter() {
    printf("GameState: Enter %s\n", getName());
    printf("\t Showing Login Scene\n");
}

void GameSM::Login::process() {
    printf("GameState: Process %s\n", getName());
    printf("\t ===== Enter Space ===== \n");
    if (getInput(0)) { // TODO: 0 == space
        transitionTo(&mLoadingState_);
    }
}

void GameSM::Login::exit() { printf("GameState: Exit %s\n", getName()); }

void GameSM::Loading::enter() {
    printf("GameState: Enter %s\n", getName());
    printf("\t Showing Loading Scene\n");
}

void GameSM::Loading::process() {
    printf("GameState: Enter %s\n", getName());
    printf("\t Showing Loading Scene\n");
    printf("\t ===== Enter Space ===== \n");
    if (getInput(0)) { // TODO: 0 == space
        transitionTo(&mGameStartState_);
    }
}

void GameSM::Loading::exit() {
    printf("GameState: Exit %s\n", getName());
    printf("\t Showing Loading Scene\n");
}

void GameSM::GameStart::enter() {
    printf("GameState: Enter %s\n", getName());
    printf("\t Playing background music\n");
}

void GameSM::GameStart::process() {
    printf("GameState: Process %s\n", getName());
    printf("\t Playing game\n");
    printf("\t ===== Enter Space: Win ===== \n");
    printf("\t ===== Enter a: Lose ===== \n");
    printf("\t ===== Enter b: Over ===== \n");
    if (getInput(0)) { // TODO: 0 == space
        transitionTo(&mGameWinState_);
    } else if (getInput(1)) { // TODO: 1 == a
        transitionTo(&mGameLoseState_);
    } else if (getInput(2)) { // TODO: 2 == b
        transitionTo(&mGameOverState_);
    }
}

void GameSM::GameStart::exit() {
    printf("GameState: Exit %s\n", getName());
    printf("\t Stop background music\n");
}

void GameSM::GameWin::enter() { printf("GameState: Enter %s\n", getName()); }

void GameSM::GameWin::process() {
    printf("GameState: Process %s\n", getName());
    printf("\t Render Game Win Animation + Play sound effects\n");
    printf("\t ===== Enter Space ===== \n");
    if (getInput(0)) { // TODO: 0 == space
        transitionTo(&mLoadingState_);
    }
}

void GameSM::GameWin::exit() {
    printf("GameState: Exit %s\n", getName());
    printf("\t Stop play sound effects\n");
}

void GameSM::GameLose::enter() { printf("GameState: Enter %s\n", getName()); }

void GameSM::GameLose::process() {
    printf("GameState: Process %s\n", getName());
    printf("\t Lose Animation + Play sound effects\n");
    printf("\t ===== Enter Space ===== \n");
    if (getInput(0)) { // TODO: 0 == space
        transitionTo(&mLoadingState_);
    }
}

void GameSM::GameLose::exit() { printf("GameState: Exit %s\n", getName()); }

void GameSM::GameOver::enter() { printf("GameState: Enter %s\n", getName()); }

void GameSM::GameOver::process() {
    printf("GameState: Process %s\n", getName());
    printf("\t No live. Ready to back to Login screen\n");
    printf("\t ===== Enter Space ===== \n");
    if (getInput(0)) { // TODO: 0 == space
        transitionTo(&mLoginState_);
    }
}

void GameSM::GameOver::exit() { printf("GameState: Exit %s\n", getName()); }
