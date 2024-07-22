#pragma once
#include <SDL.h>
#include <map>

class InputMap
{
public:
    enum Status
    {
        S_UP,
        S_PRESSED,
        S_DOWN,
        S_RELEASED
    };

    static std::map<const SDL_Keycode, bool> keyMap;
    static std::map<const char*, Status> boundInputs;
};
