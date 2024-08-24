#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <unordered_map>

#include "core/include/sdl_handler.h"
#include "level/base_level.h"

namespace sprite_handler {

class SpriteHandler {
public:
    void load_level(int num_game);
    void draw_background();  // TODO(shiheric): some block could change.
    void teardown();
    void set_root_path(std::string path);

private:
    bool is_img_loaded_(std::string);
    void load_images_();
    void set_background_color_();
    BaseLevel* current_level_;
    std::unordered_map<std::string, SDL_Texture*> imgs_texture_;
    SDL_Renderer* surface_ = sdl_handler::GetInstance().get_surface();
    std::string root_path_ = "res/images/";
};

SpriteHandler& GetInstance();

}  // namespace sprite_handler
