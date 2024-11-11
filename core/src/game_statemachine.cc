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

static int mario_x = 10*BLOCK_SIZE;
static int mario_y = 7*BLOCK_SIZE;

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
    for (int i = 0; i < 30; i++) {
        sprite_handler::GetInstance().set_text(FONT_ARRAY[i], 32 * i, 32, 32, 255, 0, 0);
    }
    for (int i = 30; i < std::size(FONT_ARRAY); i++) {
        sprite_handler::GetInstance().set_text(FONT_ARRAY[i], 32 * (i - 30), 64);
    }

    if (getInput(MARIO_CONTROL::JUMP)) {
        transitionTo(&mLoadingState_);
    }

    int x = 10 * BLOCK_SIZE;
    int y = 5 * BLOCK_SIZE;
    int thick = 1;
    int length = 10;
    int move_speed = 20;
    SDL_Rect invisible_up = SDL_Rect{.y = y, .x = x, .w = BLOCK_SIZE, .h = thick,};
    SDL_Rect invisible_down = SDL_Rect{.y = y+BLOCK_SIZE - thick, .x = x, .w = BLOCK_SIZE, .h = thick,};
    SDL_Rect invisible_right = SDL_Rect{.y = y, .x = x+BLOCK_SIZE - thick, .w = thick, .h = BLOCK_SIZE,};
    SDL_Rect invisible_left = SDL_Rect{.y = y, .x = x, .w = thick, .h = BLOCK_SIZE,};
    SDL_Rect block = SDL_Rect{.y = y, .x = x, .w = BLOCK_SIZE, .h = BLOCK_SIZE,};

    if (getInput(MARIO_CONTROL::UP)) {
        mario_y -= move_speed;
    } else if (getInput(MARIO_CONTROL::RIGHT)) {
        mario_x += move_speed;
    } else if (getInput(MARIO_CONTROL::DOWN)) {
        mario_y += move_speed;
    } else if (getInput(MARIO_CONTROL::LEFT)) {
        mario_x -= move_speed;
    } 

    SDL_Rect mario = SDL_Rect{.y = mario_y, .x = mario_x, .w = BLOCK_SIZE, .h = BLOCK_SIZE,};

    if (SDL_HasIntersection(&mario, &invisible_up)) {
        printf("Hit Top!\n");
    }
    if (SDL_HasIntersection(&mario, &invisible_down)) {
        printf("Hit Down!\n");
    }
    if (SDL_HasIntersection(&mario, &invisible_right)) {
        printf("Hit Right!\n");
    }
    if (SDL_HasIntersection(&mario, &invisible_left)) {
        printf("Hit Left!\n");
    }

    sprite_handler::GetInstance().render_a_block("brickred.png", invisible_up);
    sprite_handler::GetInstance().render_a_block("brickred.png", invisible_down);
    sprite_handler::GetInstance().render_a_block("brickred.png", invisible_right);
    sprite_handler::GetInstance().render_a_block("brickred.png", invisible_left);
    // sprite_handler::GetInstance().render_a_block("brickred.png", block);
    sprite_handler::GetInstance().render_a_block("brickred.png", mario);
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
