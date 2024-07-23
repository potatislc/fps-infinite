#include "InputMap.h"

#define INPUT_CODE(code) {code, false}
#define INPUT_BINDING(name, code) {name, {code, InputMap::S_UP}}

// Keyboard

std::map<const SDL_Keycode, bool> InputMap::keyMap =
        {
            INPUT_CODE(SDLK_SPACE)
        };

std::map<std::string, InputMap::KeyBinding> InputMap::boundKeys =
        {
            INPUT_BINDING("Dig", SDLK_SPACE)
        };

// Mouse

std::map<const Uint8, bool> InputMap::mouseMap =
        {
                INPUT_CODE(SDL_BUTTON_LEFT)
        };

std::map<std::string, InputMap::MouseBinding> InputMap::boundMouseButtons =
        {
                INPUT_BINDING("Dig", SDL_BUTTON_LEFT)
        };

#define SET_BINDING_STATUS(binding_status, S_ONCE, S_CONTINUOUS) binding_status = (binding_status != S_ONCE && binding_status != S_CONTINUOUS) ? S_ONCE : S_CONTINUOUS

InputMap::Status InputMap::getBoundKeyInput(const std::string& name)
{
    if (!boundKeys.count(name))
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
