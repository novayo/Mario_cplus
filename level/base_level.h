#ifndef BASE_LEVEL_H
#define BASE_LEVEL_H

#include <map>
#include <tuple>

typedef std::tuple<int, int> POS;
typedef std::tuple<int, int, int> COLOR; 

class BaseLevel {
public:
    virtual void play_background_music() = 0;
    virtual void stop_background_music() = 0;
    virtual COLOR get_background_color() = 0;
    virtual const std::map<POS, std::string> get_backgrounds() = 0;
};

#endif // BASE_LEVEL_H
