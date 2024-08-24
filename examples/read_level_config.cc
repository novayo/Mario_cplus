#include "level/level_1_1.h"

int main(int argc, char* argv[]) {
    BaseLevel* current_level = new Level_1_1();

    current_level->play_background_music();

    for (auto& it : current_level->get_backgrounds()) {
        printf("%s\n", it.second.c_str());
    }
}
