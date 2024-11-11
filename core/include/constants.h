#pragma once

#include <SDL2/SDL_keycode.h>

#include <string>
#include <unordered_map>

constexpr int SCREEN_ROW_BLOCKS_NUM = 14;
constexpr int SCREEN_COL_BLOCKS_NUM = 16;
constexpr int BLOCK_SIZE = 64;     // 64*64 px
constexpr int FONT_SIZE = 32;      // Font size on screen
constexpr int FONT_IMAGE_SIZE = 8; // 8*8 px in font.png
const std::string FONT_ARRAY[54] = {
    " ", "+", ",", "-", ".", "/", "0", "1", "2", "3", "4", "5", "6", "7",  "8", "9",  ":", ";",
    "<", "=", ">", "?", "@", "A", "B", "C", "D", "E", "F", "G", "h", "I",  "J", "K",  "L", "M",
    "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "\"", "_", "->", "x", "!"};

class MARIO_CONTROL {
   public:
    static constexpr int UP = 0;
    static constexpr int RIGHT = 1;
    static constexpr int DOWN = 2;
    static constexpr int LEFT = 3;
    static constexpr int JUMP = 4;
    static constexpr int ACCELERATE = 5;
    static constexpr int FIRE = 6;
};

static std::unordered_map<int32_t, int> INPUT_MAP{
    {SDLK_UP, MARIO_CONTROL::UP},      {SDLK_RIGHT, MARIO_CONTROL::RIGHT},
    {SDLK_DOWN, MARIO_CONTROL::DOWN},  {SDLK_LEFT, MARIO_CONTROL::LEFT},
    {SDLK_SPACE, MARIO_CONTROL::JUMP}, {SDLK_z, MARIO_CONTROL::ACCELERATE},
    {SDLK_x, MARIO_CONTROL::FIRE},
};

extern std::unordered_map<int32_t, int> INPUT_MAP;
