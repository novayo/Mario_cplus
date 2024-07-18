#include <SDL2_mixer/SDL_mixer.h>
#include <stdio.h>

#include <vector>

#include "core/include/sdl_handler.h"

const int SIZE = 40;
const int NUM_ROW = 15; // 800*600 => 600 / SIZE = 15
const int NUM_COL = 50; // 800*600 => 800 / SIZE = 50

class Camera {
   public:
    SDL_Rect viewport;
    Camera(int width, int height) {
        viewport.x = 0;
        viewport.y = 0;
        viewport.w = width;
        viewport.h = height;
    }

    // update the camera position based on the player position
    void update(int playerX, int playerY, int screenWidth, int screenHeight) {
        viewport.x = playerX + SIZE / 2 - screenWidth / 2;
        viewport.y = playerY + SIZE / 2 - screenHeight / 2;

        // avoid camera to go out of the screen
        if (viewport.x < 0)
            viewport.x = 0;
        if (viewport.y < 0)
            viewport.y = 0;

        // assume the screen is 800x600
        if (viewport.x + viewport.w > NUM_COL * SIZE)
            viewport.x = NUM_COL * SIZE - viewport.w;
        if (viewport.y + viewport.h > NUM_ROW * SIZE)
            viewport.y = NUM_ROW * SIZE - viewport.h;
    }

    // apply the camera to a rect
    SDL_Rect apply(SDL_Rect rect) const {
        SDL_Rect relativeRect = rect;
        relativeRect.x -= viewport.x;
        relativeRect.y -= viewport.y;
        return relativeRect;
    }
};

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

    void draw(const Camera& camera) {
        SDL_Rect relativeRect = camera.apply(this->rect);
        SDL_SetRenderDrawColor(surface, this->r, this->g, this->b, 255);
        SDL_RenderFillRect(surface, &relativeRect);
    }

   protected:
    SDL_Rect rect;
    SDL_Renderer* surface;
};

class Player : public Block {
   public:
    Player(int x, int y, int r, int g, int b) : Block(x, y, r, g, b) {}

    void move_left() {
        Block::move_left();
        if (rect.x < 0)
            rect.x = 0;
    }

    void move_right() {
        Block::move_right();
        if (rect.x + SIZE > NUM_COL * SIZE)
            rect.x = NUM_COL * SIZE - SIZE;
    }
};

int main(int argc, char* argv[]) {
    // Init music player
    Mix_Init(0);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_Music* background_music = Mix_LoadMUS("../res/sounds/overworld.wav");
    Mix_PlayMusic(background_music, -1);

    // Load sound effect
    Mix_Chunk* sound_effect = Mix_LoadWAV("../res/sounds/coin.wav");

    // Init sdl_handler
    sdl_handler::GetInstance().initialize();
    int close = 0;
    SDL_Event event;

    printf("Generate backgroud and player...\n");
    Player player(400, 280, 255, 255, 0);
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

    // Initialize camera
    Camera camera(800, 600);

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
                            player.move_left();
                            break;
                        case SDLK_RIGHT:
                            printf("Input: Right\n");
                            player.move_right();
                            break;
                        case SDLK_SPACE:
                            // Play sound effect
                            Mix_PlayChannel(-1, sound_effect, 0);
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

        // Update camera
        camera.update(player.get_x(), player.get_y(), 800, 600);

        // Update screen
        sdl_handler::GetInstance().reset_screen();

        for (Block& block : bg_blocks) {
            block.draw(camera);
        }
        player.draw(camera);

        sdl_handler::GetInstance().update_screen();
    }

    // De-init music player
    Mix_FreeChunk(sound_effect);
    Mix_FreeMusic(background_music);
    Mix_Quit();
    sdl_handler::GetInstance().teardown();

    printf("Done.\n");
    return 0;
}
