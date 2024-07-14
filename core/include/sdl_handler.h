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

private:
    SDL_Renderer* surface_;
    SDL_Window* window_;
};

SDLHandler& GetInstance();

} // namespace sdl_handler

#endif // SDL_HANDLER_H
