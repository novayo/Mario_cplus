#ifndef BASE_LEVEL_H
#define BASE_LEVEL_H

#include <map>
#include <tuple>

typedef std::tuple<int, int> POS;
typedef std::tuple<int, int, int> COLOR;

class BaseLevel {
   public:
    virtual void play_background_music() {};
    virtual void stop_background_music() {};
    virtual COLOR get_background_color() { return COLOR(0, 0, 0); };
    virtual const std::map<POS, std::string> get_backgrounds() {
        return std::map<POS, std::string>{
            {POS(0, 0), std::string("")},
        };
    };
};

#endif // BASE_LEVEL_H
