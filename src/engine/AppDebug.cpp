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
    static const float timeWindow = 2.0f; // 2-second window
    static float frameTimes[120]; // Buffer to hold frame times (assuming a max of 60 FPS for 2s)
    static int frameIndex = 0;
    static int numFrames = 0;
    static float accumulatedTime = 0.0f;

    // Calculate the time taken for this frame in seconds
    float frameTime = SDL_GetTicks64() / 1000.f - accumulatedTime;
    accumulatedTime += frameTime;

    // Update the circular buffer
    frameTimes[frameIndex] = frameTime;
    frameIndex = (frameIndex + 1) % 120;

    if (numFrames < 120) {
        numFrames++;
    }

    // Calculate the average FPS over the last 2 seconds
    float totalTime = 0.0f;
    for (int i = 0; i < numFrames; ++i) {
        totalTime += frameTimes[i];
    }
    float avgFPS = (numFrames / totalTime);

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
