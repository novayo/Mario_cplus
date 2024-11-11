#include "core/include/game_statemachine.h"

#include "core/include/constants.h"
#include "core/include/sdl_handler.h"
#include "core/include/sprite_handler.h"

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
    sprite_handler::GetInstance().load_level(11);
}

void GameSM::Login::process() {
    printf("GameState: Process %s\n", getName());
    printf("\t ===== Enter Space ===== \n");
    printf("\t [Testing] Load 1-1\n");
    sprite_handler::GetInstance().draw_background();

    // [TEST] Show text
    for (int i=0; i<30; i++) {
        sprite_handler::GetInstance().set_text(FONT_ARRAY[i], 32 * i, 32, 32, 255, 0, 0);
    }
    for (int i=30; i<std::size(FONT_ARRAY); i++) {
        sprite_handler::GetInstance().set_text(FONT_ARRAY[i], 32 * (i-30), 64);
    }

    if (getInput(MARIO_CONTROL::JUMP)) {
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
    if (getInput(MARIO_CONTROL::JUMP)) {
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
    printf("\t ===== Enter Z: Lose ===== \n");
    printf("\t ===== Enter X: Over ===== \n");
    if (getInput(MARIO_CONTROL::JUMP)) {
        transitionTo(&mGameWinState_);
    } else if (getInput(MARIO_CONTROL::ACCELERATE)) {
        transitionTo(&mGameLoseState_);
    } else if (getInput(MARIO_CONTROL::FIRE)) {
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
    if (getInput(MARIO_CONTROL::JUMP)) {
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
    if (getInput(MARIO_CONTROL::JUMP)) {
        transitionTo(&mLoadingState_);
    }
}

void GameSM::GameLose::exit() { printf("GameState: Exit %s\n", getName()); }

void GameSM::GameOver::enter() { printf("GameState: Enter %s\n", getName()); }

void GameSM::GameOver::process() {
    printf("GameState: Process %s\n", getName());
    printf("\t No live. Ready to back to Login screen\n");
    printf("\t ===== Enter Space ===== \n");
    if (getInput(MARIO_CONTROL::JUMP)) {
        transitionTo(&mLoginState_);
    }
}

void GameSM::GameOver::exit() { printf("GameState: Exit %s\n", getName()); }
