/* Example of how SDL2 detect keyboard input. */
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    printf("Initializing SDL...\n");
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    printf("Creating window...\n");
    SDL_Window* window = SDL_CreateWindow("GAME", // creates a window
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    printf("Creating renderer...\n");
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* surface = SDL_CreateRenderer(window, -1, render_flags);
    if (!surface) {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

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

        SDL_SetRenderDrawColor(surface, 0, 0, 0, 255); // Set render color to black
        SDL_RenderClear(surface);                      // Clear the window
        SDL_RenderPresent(surface);                    // Display the window
    }

    printf("Cleaning up...\n");
    SDL_DestroyRenderer(surface);
    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("Done.\n");
    return 0;
}
