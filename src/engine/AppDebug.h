#pragma once

#include <cstdint>
#include <sstream>
#include "MessageTexture.h"

class AppDebug
{
    std::stringstream timeText;
    MessageTextureTTF fpsText;
public:
    void init();
    void printFps(uint64_t frameCount);
    void drawAvgFps(uint64_t frameCount);
    void drawFps(double frameTime);
};
