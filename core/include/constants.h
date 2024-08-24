#pragma once

#include <string>

constexpr int SCREEN_ROW_BLOCKS_NUM = 14;
constexpr int SCREEN_COL_BLOCKS_NUM = 16;
constexpr int BLOCK_SIZE = 64;  // 64*64 px
constexpr int FONT_SIZE = 32;  // Font size on screen
constexpr int FONT_IMAGE_SIZE = 8;  // 8*8 px in font.png
const std::string FONT_ARRAY[54] = {" ", "+", ",", "-", ".", "/", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ":", ";", "<", "=", ">", "?", "@", "A", "B", "C", "D", "E", "F", "G", "h", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "\"", "_", "->", "x", "!"};
