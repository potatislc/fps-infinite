#pragma once
#include <SDL.h>
#include <map>
#include <string>

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

    struct KeyBinding
    {
        SDL_Keycode key;
        Status status;
    };

    struct MouseBinding
    {
        uint8_t button;
        Status status;
    };

    static std::map<const SDL_Keycode, bool> keyMap;
    static std::map<std::string, KeyBinding> boundKeys;

    static std::map<const uint8_t, bool> mouseMap;
    static std::map<std::string, MouseBinding> boundMouseButtons;

    static Status getBoundKeyInput(const std::string& name);
    static Status getBoundMouseInput(const std::string& name);
};
