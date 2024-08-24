#include <SDL2/SDL_timer.h>
#include <stdio.h>

#include "core/include/game_statemachine.h"
#include "core/include/sdl_handler.h"
#include "core/include/sprite_handler.h"

int main(int argc, char* argv[]) {
    sdl_handler::GetInstance().initialize();
    SDL_Renderer* surface = sdl_handler::GetInstance().get_surface();

    printf("Entering main loop...\n");
    int close = 0;
    SDL_Event event;
    Uint32 start_time = SDL_GetTicks(); // Get the start time

    GameSM game_sm = GameSM();
    game_sm.start();
    while (!close) {
        // 60 FPS
        if (SDL_GetTicks() - start_time < 1000/60.0) {
            continue;
        }
        start_time = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    close = 1;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_SPACE) {
                        game_sm.key_input.insert(0); // TODO: should use Enum
                    } else if (event.key.keysym.sym == SDLK_a) {
                        game_sm.key_input.insert(1); // TODO: should use Enum
                    } else if (event.key.keysym.sym == SDLK_b) {
                        game_sm.key_input.insert(2); // TODO: should use Enum
                    }
                    break;
                default:
                    break;
            }
        }

        sdl_handler::GetInstance().reset_screen();

        game_sm.process();

        sdl_handler::GetInstance().update_screen();
    }

    sdl_handler::GetInstance().teardown();
    sprite_handler::GetInstance().teardown();

    printf("Done.\n");
    return 0;
}
