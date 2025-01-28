#include "InputMap.h"

#define INPUT_CODE(code) {code, false}
#define INPUT_BINDING(name, code) {name, {code, InputMap::S_UP}}

// Keyboard

std::unordered_map<SDL_Keycode, bool> InputMap::keyMap = {};

std::unordered_map<std::string, InputMap::KeyBinding> InputMap::boundKeys = {};

// Mouse

std::unordered_map<Uint8, bool> InputMap::mouseMap =
        {
                INPUT_CODE(SDL_BUTTON_LEFT)
        };

std::unordered_map<std::string, InputMap::MouseBinding> InputMap::boundMouseButtons =
        {
                INPUT_BINDING("Dig", SDL_BUTTON_LEFT)
        };

glm::vec2 InputMap::mousePosition = {0, 0};
glm::vec2 InputMap::mouseMotion = {0, 0};

// Input methods

#define SET_BINDING_STATUS(binding_status, S_ONCE, S_CONTINUOUS) binding_status = (binding_status != S_ONCE && binding_status != S_CONTINUOUS) ? S_ONCE : S_CONTINUOUS

InputMap::Status InputMap::getBoundKeyInput(const std::string& name)
{
    if (!boundKeys.contains(name))
    {
        printf("Input key: %s Not found \n", name.c_str());
        return S_UP;
    }

    const bool isKeyPressed = keyMap[boundKeys[name].key];

    if (isKeyPressed)
    {
        SET_BINDING_STATUS(boundKeys[name].status, S_PRESSED, S_DOWN);
    }
    else
    {
        SET_BINDING_STATUS(boundKeys[name].status, S_RELEASED, S_UP);
    }

    return boundKeys[name].status;
}

InputMap::Status InputMap::getBoundMouseInput(const std::string& name)
{
    if (!boundMouseButtons.count(name))
    {
        printf("Input mouse button: %s Not found \n", name.c_str());
        return S_UP;
    }

    const bool isMouseButtonPressed = mouseMap[boundMouseButtons[name].button];

    if (isMouseButtonPressed)
    {
        SET_BINDING_STATUS(boundMouseButtons[name].status, S_PRESSED, S_DOWN);
    }
    else
    {
        SET_BINDING_STATUS(boundMouseButtons[name].status, S_RELEASED, S_UP);
    }

    return boundMouseButtons[name].status;
}

void InputMap::addKeyCode(SDL_Keycode code)
{
    InputMap::keyMap[code] = false;
}

void InputMap::addKeyBinding(const std::string& name, SDL_Keycode code)
{
    if (!keyMap.contains(code)) addKeyCode(code);
    boundKeys[name] = {code, S_UP};
}

bool InputMap::isBoundKeyDown(const std::string& name)
{
    return getBoundKeyInput(name) == S_DOWN;
}

bool InputMap::isBoundKeyPressed(const std::string& name) {
    return false;
}
