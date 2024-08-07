#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <map>
#include "engine/utils/Utils.h"
#include "UniqueTexture.h"

#define FONTS_TTF_PATH RESOURCES_PATH"fonts_ttf/"
#define FONTS_TEX_PATH RESOURCES_PATH"textures/fonts_tex/"

extern const std::map<const char*, SDL_Texture*> fontTextures;
extern void destroyTexture(SDL_Texture* texture);

//
// Tex
//

class MessageTexture
{
public:
    static void renderMessage(SDL_Renderer* renderTarget, SDL_Texture* fontTexture, const char* message,
                              Utils::Vector2 position, SDL_Color color); // Render a message on screen
    static UniqueTexture* messageToTexture(SDL_Renderer* renderTarget, SDL_Texture* fontTexture, const char* message,
                                           SDL_Color color); // Render a message to a texture
};

//
// TTF
//

class MessageTextureTTF
{
    TTF_Font* font;
public:
    UniqueTexture texture;
    SDL_Renderer* renderer;
    SDL_Color color;

    void setText(SDL_Renderer* renderer_, const char *fontPath, const char* message, SDL_Color color_);
    void updateText(const char* message);
};
