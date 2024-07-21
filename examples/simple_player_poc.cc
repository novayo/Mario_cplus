#include <stdio.h>

#include <vector>

#include "core/include/sdl_handler.h"
#include "core/include/sound_handler.h"

const int SIZE = 40;
const int NUM_ROW = 15; // 800*600 => 600 / SIZE = 15
const int NUM_COL = 20; // 800*600 => 800 / SIZE = 20

class Block {
   public:
    int r, g, b;
    Block(int x, int y, int r, int g, int b) {
        this->rect.x = x;
        this->rect.y = y;
        this->rect.w = SIZE;
        this->rect.h = SIZE;
        this->r = r;
        this->g = g;
        this->b = b;
        this->surface = sdl_handler::GetInstance().get_surface();
    }

    void move_left() { this->rect.x -= SIZE; }

    void move_right() { this->rect.x += SIZE; }

    int get_x() { return this->rect.x; }

    void draw() {
        SDL_SetRenderDrawColor(surface, this->r, this->g, this->b, 255);
        SDL_RenderFillRect(surface, &this->rect);
    }

   private:
    SDL_Rect rect;
    SDL_Renderer* surface;
};

int main(int argc, char* argv[]) {
    // Init music player
    sound_handler::GetInstance().initialize();
    sound_handler::GetInstance().play_bgm("overworld.wav");

    // Init sdl_handler
    sdl_handler::GetInstance().initialize();
    int close = 0;
    SDL_Event event;

    // Init player and blocks
    printf("Generate backgroud and player...\n");
    Block player(400, 280, 255, 255, 0);
    std::vector<Block> bg_blocks;
    for (int j = 0; j <= NUM_ROW; j++) {
        bool draw_black = j % 2 == 0;
        for (int i = 0; i <= NUM_COL; i++) {
            if (draw_black) {
                bg_blocks.push_back(Block(i * SIZE, j * SIZE, 0, 0, 0));
            } else {
                bg_blocks.push_back(Block(i * SIZE, j * SIZE, 255, 255, 255));
            }
            draw_black = !draw_black;
        }
    }

    // Start the game
    printf("Entering main loop...\n");
    while (!close) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    close = 1;
                    break;
                case SDL_KEYDOWN:
                    // Detect key press
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                            printf("Input: Left\n");
                            if (player.get_x() == 0) {
                                for (Block& block : bg_blocks) {
                                    block.move_right();
                                }
                            } else {
                                player.move_left();
                            }
                            break;
                        case SDLK_RIGHT:
                            printf("Input: Right\n");
                            if (player.get_x() == 400) {
                                for (Block& block : bg_blocks) {
                                    block.move_left();
                                }
                            } else {
                                player.move_right();
                            }
                            break;
                        case SDLK_SPACE:
                            // Play sound effect
                            sound_handler::GetInstance().play_sound("coin.wav");
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

        // Update screen
        sdl_handler::GetInstance().reset_screen();

        for (Block& block : bg_blocks) {
            block.draw();
        }
        player.draw();

        sdl_handler::GetInstance().update_screen();
    }

    sound_handler::GetInstance().teardown();
    sdl_handler::GetInstance().teardown();

    printf("Done.\n");
    return 0;
}
