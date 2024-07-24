#include "MessageTexture.h"

SDL_Texture *MessageTexture::Create(SDL_Renderer* renderer, TTF_Font *font, const char *message, SDL_Color color)
{
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, message, color);
    SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);

    return messageTexture;
}
