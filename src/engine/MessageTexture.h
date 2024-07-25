#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

#define FONTS_PATH RESOURCES_PATH"fonts/"

class MessageTexture
{
    TTF_Font* font;
public:
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    SDL_Color color;

    ~MessageTexture();
    void setText(SDL_Renderer* renderer_, const char *fontPath, const char* message, SDL_Color color_);
    void updateText(const char* message);
};
