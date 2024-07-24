#include <SDL.h>
#include "AppDebug.h"
#include "MessageTexture.h"
#include "Application.h"

void AppDebug::printFps(uint64_t frameCount)
{
    float avgFPS = (float)frameCount / ((float)SDL_GetTicks64() / 1000.f);
    if( avgFPS > 2000000 )
    {
        avgFPS = 0;
    }

    printf("FPS: %f\n", avgFPS);
}

void AppDebug::drawFps(uint64_t frameCount)
{
    float avgFPS = (float)frameCount / ((float)SDL_GetTicks64() / 1000.f);
    if( avgFPS > 2000000 )
    {
        avgFPS = 0;
    }

    timeText.str( "" );
    timeText << "Average Frames Per Second " << avgFPS;

    SDL_Rect rect = {0, 0, 128, 128};
    SDL_Point origin = {0, 0};
    SDL_RenderCopyEx(fpsText.renderer, fpsText.texture, &rect, &rect, 0.0, &origin, SDL_FLIP_NONE);
}

void AppDebug::init()
{
    SDL_Color color = {0, 200, 0};
    fpsText.setText(Application::renderer.sdlRenderer, FONTS_PATH"PixelifySans-Regular.ttf", "Test", color);
}
