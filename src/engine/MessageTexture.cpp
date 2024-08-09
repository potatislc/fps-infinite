#include <iostream>
#include "MessageTexture.h"
#include "ResourceLoader.h"

//
// Tex
//

MessageTexture::FontAtlas MessageTexture::fontAtlases[FAI_LENGTH] =
    {
            {UniqueTexture(), 8} // Default font
    };

void MessageTexture::loadFontAtlases()
{
    fontAtlases[FAI_DEFAULT].texture.set(ResourceLoader::loadTexture(FONTS_TEX_PATH"font.png"));
    printf("Test: %d\n", fontAtlases[FAI_DEFAULT].texture.getSize().x);
}

void MessageTexture::renderMessage(SDL_Renderer* renderTarget, FontAtlasId fontAtlasId, const char* message,
                                   Utils::Vector2I position, SDL_Color color = Utils::Colors::white)
{
    FontAtlas fontAtlas = fontAtlases[fontAtlasId];
    for (int i = 0; i < strlen(message); i++)
    {
        uint8_t atlasPos = getAtlasPos(message[i]) * fontAtlas.charSize;
        SDL_Rect charRect =
                {
                atlasPos % fontAtlas.texture.getSize().x,
                atlasPos / fontAtlas.texture.getSize().y,
                fontAtlas.charSize,
                fontAtlas.charSize
                };
        SDL_Rect destRect = {position.x + i * fontAtlas.charSize, position.y, fontAtlas.charSize, fontAtlas.charSize};
        SDL_Point origin = {0, 0};
        SDL_RenderCopyEx(renderTarget, fontAtlas.texture.get(), &charRect, &destRect, 0.0, &origin, SDL_FLIP_NONE);
    }
}

SDL_Texture* MessageTexture::messageToTexture(SDL_Renderer *renderTarget, FontAtlasId fontAtlasId, const char *message,
                                              SDL_Color color = Utils::Colors::white)
{
    return nullptr;
}

MessageTexture::FontAtlas MessageTexture::getFontAtlas(MessageTexture::FontAtlasId fontAtlas)
{
    return fontAtlases[fontAtlas];
}

inline uint8_t MessageTexture::getAtlasPos(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';  // '0' maps to 0, '1' maps to 1, ..., '9' maps to 9
    }
    else if (c >= 'a' && c <= 'z')
    {
        return c - 'a' + 10;  // 'a' maps to 10, 'b' to 11, ..., 'z' maps to 35
    }

    return ATLAS_ERROR_POS; // End of page
}

//
// TTF
//

void MessageTextureTTF::setText(SDL_Renderer *renderer_, const char *fontPath, const char *message, SDL_Color color_)
{
    font = TTF_OpenFont(fontPath, 16);
    if(!font)
    {
        std::cout << "Can't open font: " << TTF_GetError() << std::endl;
    }
    renderer = renderer_;
    color = color_;
    updateText(message);
}

void MessageTextureTTF::updateText(const char *message)
{
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, message, color);
    if(surfaceMessage == nullptr)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }

    texture.set(SDL_CreateTextureFromSurface(renderer, surfaceMessage));
    SDL_FreeSurface(surfaceMessage);
}
