#include <SDL.h>
#include "AppDebug.h"
#include "MessageTexture.h"
#include "App.h"

void AppDebug::printFps(uint64_t frameCount)
{
    float avgFPS = (float)frameCount / ((float)SDL_GetTicks64() / 1000.f);

    printf("FPS: %f\n", avgFPS);
}

void AppDebug::drawAvgFps(uint64_t frameCount)
{
    float avgFPS = (float)frameCount / ((float)SDL_GetTicks64() / 1000.f);

    timeText.str("");
    timeText << "FPS: " << avgFPS;
    MessageTexture::renderMessage(App::renderer.sdlRenderer, MessageTexture::FAI_DEFAULT, timeText.str().c_str(), (Utils::Vector2I){0, 0}, (SDL_Color){255, 255, 255, 255});
}

void AppDebug::init()
{
    SDL_Color color = {0, 200, 0};
    // fpsText.setText(Application::renderer.sdlRenderer, FONTS_TTF_PATH"PixelifySans-Regular.ttf", "Test", color);
}

void AppDebug::drawFps(double frameTime)
{
    double FPS = fmin(1 / frameTime, App::targetFps);

    timeText.str("");
    timeText << "FPS: " << FPS;
    MessageTexture::renderMessage(App::renderer.sdlRenderer, MessageTexture::FAI_DEFAULT, timeText.str().c_str(), (Utils::Vector2I){0, 0}, (SDL_Color){255, 255, 255, 255});
}
