#pragma once
#include <SDL.h>
#include <unordered_map>
#include <string>
#include "glm/vec2.hpp"

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

    static std::unordered_map<SDL_Keycode, bool> keyMap;
    static std::unordered_map<std::string, KeyBinding> boundKeys;

    static std::unordered_map<uint8_t, bool> mouseMap;
    static std::unordered_map<std::string, MouseBinding> boundMouseButtons;
    static glm::vec2 mousePosition;
    static glm::vec2 mouseMotion;

    static void addKeyBinding(const std::string& name, SDL_Keycode code);
    static void addMouseBinding(const std::string& name, uint8_t code);
    static Status getBoundKeyInput(const std::string& name);
    static Status getBoundMouseInput(const std::string& name);

    static bool isBoundKeyPressed(const std::string& name);
    static bool isBoundKeyDown(const std::string& name);
    static bool isBoundKeyReleased(const std::string& name);

    static bool isBoundMouseButtonPressed(const std::string& name);
    static bool isBoundMouseButtonDown(const std::string& name);
    static bool isBoundMouseButtonReleased(const std::string& name);

private:
    static void addKeyCode(SDL_Keycode code);
    static void addMouseCode(uint8_t code);
};
