#include <SDL2/SDL_timer.h>
#include <stdio.h>

#include <condition_variable>
#include <mutex>
#include <thread>

#include "core/include/game_statemachine.h"
#include "core/include/sdl_handler.h"
#include "core/include/sprite_handler.h"

std::condition_variable cv;
std::mutex m;
std::unique_lock<std::mutex> lock(m);
bool is_process_alive = true;

void update_screen() {
    // This function is running in update_thread.
    while (is_process_alive) {
        cv.wait(lock);
        printf("Update screen...\n");
        sdl_handler::GetInstance().update_screen();
    }
    printf("Teardown update_thread...\n");
}

int main(int argc, char* argv[]) {
    sdl_handler::GetInstance().initialize();
    SDL_Renderer* surface = sdl_handler::GetInstance().get_surface();

    sprite_handler::GetInstance().initialize();

    // Create a thread for updating screen
    std::thread update_thread(update_screen);

    printf("Entering main loop...\n");
    int close = 0;
    SDL_Event event;
    Uint32 start_time = SDL_GetTicks(); // Get the start time

    GameSM game_sm = GameSM();
    game_sm.start();
    while (!close) {
        // 60 FPS
        if (SDL_GetTicks() - start_time < 1000 / 60.0) {
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

        cv.notify_all();  // Notify update_thread to process.
    }

    // Teardown threads
    is_process_alive = false;
    update_thread.join();

    sdl_handler::GetInstance().teardown();
    sprite_handler::GetInstance().teardown();

    printf("Done.\n");
    return 0;
}
