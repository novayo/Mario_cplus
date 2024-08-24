#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "core/include/constants.h"
#include "core/include/sdl_handler.h"
#include "core/include/sprite_handler.h"
#include "level/level_1_1.h"

using namespace sprite_handler;

sprite_handler::SpriteHandler& sprite_handler::GetInstance() {
    static SpriteHandler sprite_handler_;
    return sprite_handler_;
}

void SpriteHandler::initialize() {
    font_texture_ = IMG_LoadTexture(surface_, (root_path_+"font.png").c_str());
    for (int i=0; i<std::size(FONT_ARRAY); i++) {
        fonts_attribute_[FONT_ARRAY[i]] = SDL_Rect{
            .x = FONT_IMAGE_SIZE*i,
            .y = 0,
            .w = FONT_IMAGE_SIZE,
            .h = FONT_IMAGE_SIZE,
        };
    }
}

void SpriteHandler::set_text(std::string text, int x, int y) {
    if (fonts_attribute_.find(text) == fonts_attribute_.end()) {
        printf("[WARN] Text is not supported: %s", text.c_str());
        return;
    }
    SDL_Rect pos = SDL_Rect{
        .x = x,
        .y = y,
        .w = FONT_SIZE,
        .h = FONT_SIZE,
    };
    SDL_RenderCopy(surface_, font_texture_, &fonts_attribute_[text], &pos);
}

void SpriteHandler::load_level(int num_level) {
    delete current_level_;

    switch (num_level) {
        case 11:  // 1-1
            current_level_ = new Level_1_1();
            break;
        default:
            break;
    }

    load_images_();
    set_background_color_();
}

void SpriteHandler::draw_background() {
    for (auto& it : current_level_->get_backgrounds()) {
        SDL_Rect pos = SDL_Rect{
            .y = std::get<0>(it.first) * BLOCK_SIZE - BLOCK_SIZE / 2,  // Offset 0.5 block
            .x = std::get<1>(it.first) * BLOCK_SIZE,
            .w = BLOCK_SIZE,
            .h = BLOCK_SIZE,
        };
        SDL_RenderCopy(surface_, imgs_texture_[it.second], NULL, &pos);
    }
}

void SpriteHandler::teardown() {
    // Release all images.
    for (auto& it : imgs_texture_) {
        SDL_DestroyTexture(it.second);
    }
    imgs_texture_.clear();

    SDL_DestroyTexture(font_texture_);
    fonts_attribute_.clear();

    // Release pointers.
    delete current_level_;
    current_level_ = NULL;
}

void SpriteHandler::set_root_path(std::string path) {
    root_path_ = path;
}

void SpriteHandler::set_background_color_() {
    COLOR bg_color = current_level_->get_background_color();
    sdl_handler::GetInstance().set_background_color(std::get<0>(bg_color), std::get<1>(bg_color), std::get<2>(bg_color));
}

void SpriteHandler::load_images_() {
    for (auto& it : current_level_->get_backgrounds()) {
        std::string img_name = it.second;
        if (is_img_loaded_(img_name)) {
            continue;
        }
        imgs_texture_[img_name] = IMG_LoadTexture(surface_, (root_path_+img_name).c_str());
    }
}

bool SpriteHandler::is_img_loaded_(std::string img_name) {
    return imgs_texture_.find(img_name) != imgs_texture_.end();
}
