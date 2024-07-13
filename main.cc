#include <SDL2/SDL_timer.h>
#include <stdio.h>

#include "core/include/sdl_handler.h"

int main(int argc, char* argv[]) {
    sdl_handler::GetInstance().initialize();
    SDL_Renderer* surface = sdl_handler::GetInstance().get_surface();

    printf("Entering main loop...\n");
    int close = 0;
    SDL_Event event;
    Uint32 start_time = SDL_GetTicks(); // Get the start time

    while (!close) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    close = 1;
                    break;
                default:
                    break;
            }
        }

        sdl_handler::GetInstance().reset_screen();
        sdl_handler::GetInstance().update_screen();
    }

    sdl_handler::GetInstance().teardown();

    printf("Done.\n");
    return 0;
}