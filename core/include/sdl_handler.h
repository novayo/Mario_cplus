#ifndef SDL_HANDLER_H
#define SDL_HANDLER_H
#include <SDL2/SDL.h>

namespace sdl_handler {

class SDLHandler {
public:
    void initialize();
    void teardown();
    SDL_Renderer* get_surface();
    void reset_screen();
    void update_screen();
    void set_background_color(uint8_t r, uint8_t g, uint8_t b);

private:
    SDL_Renderer* surface_;
    SDL_Window* window_;
    uint8_t bg_color_[3] = {0, 0, 0};  // Default black
};

SDLHandler& GetInstance();

} // namespace sdl_handler

#endif // SDL_HANDLER_H
