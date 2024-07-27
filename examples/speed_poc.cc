#include <stdio.h>

#include <vector>

#include "core/include/sdl_handler.h"
#include "core/include/sound_handler.h"

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
    SDL_Rect apply(SDL_Rect& rect) const {
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

    int get_x() { return this->rect.x; }
    int get_y() { return this->rect.y; }

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
    // vx: speed in x direction
    // ax: acceleration in x direction
    float vx, ax; 

    // max_speed: speed upper limit
    float max_speed;

    // is_sprinting: whether the player is sprinting
    bool is_sprinting;

    Player(int x, int y, int r, int g, int b) : Block(x, y, r, g, b), vx(0), ax(0), max_speed(300.0f), is_sprinting(false) {}

    // Handle player input for movement and sprinting
    void apply_input(SDL_Keycode key, bool is_pressed) {
        switch (key) {
            case SDLK_LEFT:
                ax = is_pressed ? (is_sprinting ? -sprint_acceleration : -normal_acceleration) : 0;
                break;
            case SDLK_RIGHT:
                ax = is_pressed ? (is_sprinting ? sprint_acceleration : normal_acceleration) : 0;
                break;
            case SDLK_LSHIFT:
            case SDLK_RSHIFT:
                is_sprinting = is_pressed;
                max_speed = is_pressed ? sprint_max_speed : normal_max_speed;
                break;
            default:
                break;
        }
    }

    // Update player position based on speed and acceleration
    void update_position(float dt) {
        update_speed(dt);
        apply_friction();
        limit_position();
    }

private:
    float normal_acceleration = 200.0f;
    float sprint_acceleration = 400.0f;
    float normal_max_speed = 300.0f;
    float sprint_max_speed = 600.0f;
    // Update player speed based on acceleration and time delta
    void update_speed(float dt) {
        vx += ax * dt;
        if (vx > max_speed) vx = max_speed;
        if (vx < -max_speed) vx = -max_speed;
        rect.x += static_cast<int>(vx * dt);
    }

    // Apply friction to slow down the player
    void apply_friction() {
        if (ax == 0) {
            vx *= 0.9f;

            // if the speed is very small, set it to zero
            if (abs(vx) < 0.01f) vx = 0;
        }
    }

    // Limit player position to the screen boundaries
    void limit_position() {
        if (rect.x < 0) {
            rect.x = 0;
            vx = 0;
        }
        if (rect.x + SIZE > NUM_COL * SIZE) {
            rect.x = NUM_COL * SIZE - SIZE;
            vx = 0;
        }
    }
};
int main(int argc, char* argv[]) {
    // Init music player
    sound_handler::GetInstance().initialize();
    sound_handler::GetInstance().play_bgm("overworld.wav");

    // Init sdl_handler
    sdl_handler::GetInstance().initialize();
    int close = 0;
    SDL_Event event;

    printf("Generate background and player...\n");
    Player player(400, 280, 255, 0, 0);
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
    Uint32 last_time = SDL_GetTicks();
    while (!close) {
        Uint32 current_time = SDL_GetTicks();

        // Calculate delta time
        float dt = (current_time - last_time) / 1000.0f;
        last_time = current_time;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    close = 1;
                    break;
                case SDL_KEYDOWN:
                    // Detect key press
                    player.apply_input(event.key.keysym.sym, true);
                    if (event.key.keysym.sym == SDLK_SPACE) {
                        // Play sound effect
                        sound_handler::GetInstance().play_sound("coin.wav");
                    }
                    break;
                case SDL_KEYUP:
                    // Detect key release
                    player.apply_input(event.key.keysym.sym, false);
                    break;
                default:
                    break;
            }
        }

        // Update player position
        player.update_position(dt);

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
    sound_handler::GetInstance().teardown();
    sdl_handler::GetInstance().teardown();

    printf("Done.\n");
    return 0;
}
