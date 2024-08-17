#pragma once

#include <string>

class IState {
public:
    IState() {};
    IState(std::string name) : name_(name) {};
    virtual void enter(){};
    virtual void process() {};
    virtual void exit() {};

    const char* getName() {
        return name_.c_str();
    }

private:
    std::string name_;
};
