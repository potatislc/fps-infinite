#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <map>
#include "engine/utils/Utils.h"
#include "UniqueTexture.h"

#define FONTS_TTF_PATH RESOURCES_PATH"fonts_ttf/"
#define FONTS_TEX_PATH RESOURCES_PATH"textures/fonts_tex/"

//
// Tex
//

#define ATLAS_ERROR_POS 63

class MessageTexture
{
public:
    struct FontAtlas
    {
        UniqueTexture texture;
        int charSize;
    }; // Atlas can be at max 255 characters

    enum FontAtlasId
    {
        FAI_DEFAULT,
        FAI_LENGTH
    };

    static void loadFontAtlases();
    static void renderMessage(SDL_Renderer* renderTarget, FontAtlasId fontAtlasId, const char* message,
                              Utils::Vector2I position, SDL_Color color); // Render a message on screen
    static SDL_Texture* messageToTexture(SDL_Renderer* renderTarget, FontAtlasId fontAtlasId, const char* message,
                                           SDL_Color color); // Render a message to a texture
    static FontAtlas getFontAtlas(FontAtlasId fontAtlas);
private:
    static FontAtlas fontAtlases[FAI_LENGTH];

    static inline uint8_t getAtlasPos(char c); // Atlas can be at max 255 characters
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
