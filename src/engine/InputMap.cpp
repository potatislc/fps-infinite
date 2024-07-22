#include "InputMap.h"

#define INPUT_KEY_CODE(key) {key, false}
#define INPUT_STR_CODE(str) {str, S_UP}

std::map<const SDL_Keycode, bool> InputMap::keyMap =
        {
            INPUT_KEY_CODE(SDLK_SPACE)
        };

std::map<const char*, InputMap::Status> InputMap::boundInputs =
        {
                INPUT_STR_CODE("Dig"),
                INPUT_STR_CODE("Special")
        };