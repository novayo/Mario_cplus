/* Example of how SDL2 detect keyboard input. */
#include <SDL2/SDL.h>
#include <stdio.h>

#include "core/include/sdl_handler.h"

int main(int argc, char* argv[]) {
    sdl_handler::SDLHandler& sdl_handler = sdl_handler::GetInstance();
    sdl_handler.initialize();

    printf("Entering main loop...\n");
    int close = 0;
    SDL_Event event;

    while (!close) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    close = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                            printf("Input: Left\n");
                            break;
                        case SDLK_RIGHT:
                            printf("Input: Right\n");
                            break;
                        case SDLK_UP:
                            printf("Input: Up\n");
                            break;
                        case SDLK_DOWN:
                            printf("Input: Down\n");
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }

        sdl_handler.reset_screen();
        sdl_handler.update_screen();
    }

    sdl_handler.teardown();
    printf("Done.\n");
    return 0;
}
