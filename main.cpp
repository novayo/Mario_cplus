#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

int main(int argc, char *argv[]) {
    printf("Initializing SDL...\n");
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    
    printf("Creating window...\n");
    SDL_Window* win = SDL_CreateWindow("GAME", // creates a window
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       800, 600, SDL_WINDOW_SHOWN);
    if (!win) {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    printf("Creating renderer...\n");
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend) {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
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
                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255); // Set render color to black
        SDL_RenderClear(rend);                      // Clear the window
        SDL_RenderPresent(rend);                    // Display the window

        // Check if 5 seconds have passed
        if (SDL_GetTicks() - start_time > 5000) {
            close = 1;
        }
    }

    printf("Cleaning up...\n");
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

    printf("Done.\n");
    return 0;
}
