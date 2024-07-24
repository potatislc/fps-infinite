#include <iostream>
#include "MessageTexture.h"

void MessageTexture::setText(SDL_Renderer *renderer_, const char *fontPath, const char *message, SDL_Color color)
{
    font = TTF_OpenFont(fontPath, 8);
    if(!font)
    {
        std::cout << "Can't open font: " << TTF_GetError() << std::endl;
    }
    renderer = renderer_;
    updateText(message, color);
}

void MessageTexture::updateText(const char *message, SDL_Color color)
{
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, message, color);
    if(surfaceMessage == nullptr)
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }

    texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);
}
