#pragma once

#include <cstdint>
#include <sstream>
#include "MessageTexture.h"

class AppDebug
{
    std::stringstream timeText;
    MessageTexture fpsText;
public:
    void init();
    void printFps(uint64_t frameCount);
    void drawFps(uint64_t frameCount);
};