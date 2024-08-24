#include "core/include/constants.h"
#include "core/include/sdl_handler.h"

#include <stdio.h>

sdl_handler::SDLHandler& sdl_handler::GetInstance() {
    static SDLHandler sdl_handler_;
    return sdl_handler_;
}

void sdl_handler::SDLHandler::initialize() {
    printf("Initializing SDL...\n");
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return;
    }

    printf("Creating window...\n");
    window_ = SDL_CreateWindow("GAME", // creates a window
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               SCREEN_COL_BLOCKS_NUM * BLOCK_SIZE,  // Width
                               SCREEN_ROW_BLOCKS_NUM * BLOCK_SIZE,  // Height
                               SDL_WINDOW_SHOWN);
    if (!window_) {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    printf("Creating renderer...\n");
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    surface_ = SDL_CreateRenderer(window_, -1, render_flags);
    if (!surface_) {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window_);
        SDL_Quit();
        return;
    }
}

SDL_Renderer* sdl_handler::SDLHandler::get_surface() {
    if (surface_ == nullptr) {
        printf("[Error] Surface is not initialzed.");
        return nullptr;
    }
    return surface_;
}

void sdl_handler::SDLHandler::teardown() {
    printf("Cleaning up SDL...\n");
    SDL_DestroyRenderer(surface_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void sdl_handler::SDLHandler::reset_screen() {
    // Set screen to black
    SDL_SetRenderDrawColor(surface_, 0, 0, 0, 255);
    SDL_RenderClear(surface_);
}

void sdl_handler::SDLHandler::update_screen() {
    SDL_RenderPresent(surface_); // Display the window
}
