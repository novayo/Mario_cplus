#include "core/include/sound_handler.h"

sound_handler::SoundHandler& sound_handler::GetInstance() {
    static SoundHandler sound_handler_;
    return sound_handler_;
}

void sound_handler::SoundHandler::initialize() {
    Mix_Init(0);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

    // TODO(shiheric): Load all sounds and played by key.
}

void sound_handler::SoundHandler::teardown() {
    if (sound_effect_ != nullptr) {
        Mix_FreeChunk(sound_effect_);
    }
    if (background_music_ != nullptr) {
        Mix_FreeMusic(background_music_);
    }
    Mix_Quit();
}

void sound_handler::SoundHandler::play_bgm(std::string bg_name) {
    if (background_music_ != nullptr) {
        Mix_HaltMusic();
        Mix_FreeMusic(background_music_);
    }
    background_music_ = Mix_LoadMUS((root_path_ + bg_name).c_str());
    Mix_PlayMusic(background_music_, -1);
}

void sound_handler::SoundHandler::resume_bgm() { Mix_ResumeMusic(); }

void sound_handler::SoundHandler::pause_bgm() { Mix_PauseMusic(); }

void sound_handler::SoundHandler::play_sound(std::string sound_name) {
    if (sound_effect_ != nullptr) {
        Mix_FreeChunk(sound_effect_);
    }
    sound_effect_ = Mix_LoadWAV((root_path_ + sound_name).c_str());
    Mix_PlayChannel(-1, sound_effect_, 0);
}
