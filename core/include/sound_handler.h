#ifndef SOUND_HANDLER_H
#define SOUND_HANDLER_H
#include <SDL2_mixer/SDL_mixer.h>
#include <string>

namespace sound_handler {

class SoundHandler {
public:
    void initialize();
    void teardown();
    void play_bgm(std::string);
    void resume_bgm();
    void pause_bgm();
    void play_sound(std::string);

private:
    Mix_Music* background_music_;
    Mix_Chunk* sound_effect_;
    std::string root_path_ = "../res/sounds";
};

SoundHandler& GetInstance();

} // namespace sound_handler

#endif // #define SOUND_HANDLER_H
