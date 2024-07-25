#include <SDL.h>
#include "AppDebug.h"
#include "MessageTexture.h"
#include "Application.h"

void AppDebug::printFps(uint64_t frameCount)
{
    float avgFPS = (float)frameCount / ((float)SDL_GetTicks64() / 1000.f);

    printf("FPS: %f\n", avgFPS);
}

void AppDebug::drawFps(uint64_t frameCount)
{
    float avgFPS = (float)frameCount / ((float)SDL_GetTicks64() / 1000.f);

    timeText.str("");
    timeText << "FPS: " << avgFPS;

    fpsText.updateText(timeText.str().c_str());
    SDL_Rect rect = {0, 0, 256, 64};
    SDL_Point origin = {0, 0};
    SDL_RenderCopyEx(fpsText.renderer, fpsText.texture, &rect, &rect, 0.0, &origin, SDL_FLIP_NONE);
}

void AppDebug::init()
{
    SDL_Color color = {0, 200, 0};
    fpsText.setText(Application::renderer.sdlRenderer, FONTS_PATH"PixelifySans-Regular.ttf", "Test", color);
}
