#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <map>
#include "engine/utils/Utils.h"

#define FONTS_TTF_PATH RESOURCES_PATH"fonts_ttf/"
#define FONTS_TEX_PATH RESOURCES_PATH"textures/fonts_tex/"

extern const std::map<const char*, SDL_Texture*> fontTextures;

//
// Tex
//

class MessageTexture
{
public:
    static void renderMessage(SDL_Renderer* renderTarget, SDL_Texture* fontTexture, const char* message,
                              Utils::Vector2 position, SDL_Color color);
};

//
// TTF
//

class MessageTextureTTF
{
    TTF_Font* font;
public:
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    SDL_Color color;

    ~MessageTextureTTF();
    void setText(SDL_Renderer* renderer_, const char *fontPath, const char* message, SDL_Color color_);
    void updateText(const char* message);
};
