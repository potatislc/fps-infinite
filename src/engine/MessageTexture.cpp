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
    if (fontAtlases[FAI_DEFAULT].texture.get() == nullptr)
    {
        printf("Failed to load texture: %s\n", SDL_GetError());
    }
}

void MessageTexture::renderMessage(SDL_Renderer* renderTarget, FontAtlasId fontAtlasId, const char* message,
                                   Utils::Vector2I position, SDL_Color color = Utils::Colors::white)
{
    FontAtlas* fontAtlas = &fontAtlases[fontAtlasId];
    SDL_SetTextureColorMod(fontAtlas->texture.get(), color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(fontAtlas->texture.get(), color.a);

    for (size_t i = 0; i < strlen(message); i++)
    {
        uint8_t atlasPos = getAtlasPos(message[i]);
        SDL_Rect charRect =
                {
                (atlasPos % (fontAtlas->texture.getSize().x / fontAtlas->charSize)) * fontAtlas->charSize,
                (atlasPos / (fontAtlas->texture.getSize().y / fontAtlas->charSize)) * fontAtlas->charSize,
                fontAtlas->charSize,
                fontAtlas->charSize
                };
        SDL_Rect destRect = {position.x + (int)i * fontAtlas->charSize, position.y, fontAtlas->charSize, fontAtlas->charSize};
        SDL_Point origin = {0, 0};
        SDL_RenderCopyEx(renderTarget, fontAtlas->texture.get(), &charRect, &destRect, 0.0, &origin, SDL_FLIP_NONE);
    }
}

SDL_Texture* MessageTexture::messageToTexture(SDL_Renderer *renderTarget, FontAtlasId fontAtlasId, const char *message,
                                              SDL_Color color = Utils::Colors::white)
{
    FontAtlas* fontAtlas = &fontAtlases[fontAtlasId];
    size_t messageLength = strlen(message);

    // Calculate the texture size based on the message length and character size
    int textureWidth = messageLength * fontAtlas->charSize;
    int textureHeight = fontAtlas->charSize;

    // Create an SDL texture to render to
    SDL_Texture* messageTexture = SDL_CreateTexture(renderTarget, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, textureWidth, textureHeight);

    if (messageTexture == nullptr)
    {
        // Handle error
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        return nullptr;
    }

    SDL_SetTextureBlendMode(messageTexture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderTarget, messageTexture);
    SDL_SetRenderDrawColor(renderTarget, 0, 0, 0, 0); // RGBA: 0,0,0,0 for transparency
    SDL_RenderClear(renderTarget);
    SDL_SetTextureColorMod(fontAtlas->texture.get(), color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(fontAtlas->texture.get(), color.a);

    for (size_t i = 0; i < messageLength; i++)
    {
        uint8_t atlasPos = getAtlasPos(message[i]);
        SDL_Rect charRect =
                {
                        (atlasPos % (fontAtlas->texture.getSize().x / fontAtlas->charSize)) * fontAtlas->charSize,
                        (atlasPos / (fontAtlas->texture.getSize().y / fontAtlas->charSize)) * fontAtlas->charSize,
                        fontAtlas->charSize,
                        fontAtlas->charSize
                };
        SDL_Rect destRect = {0 + (int)i * fontAtlas->charSize, 0, fontAtlas->charSize, fontAtlas->charSize};
        SDL_Point origin = {0, 0};
        SDL_RenderCopyEx(renderTarget, fontAtlas->texture.get(), &charRect, &destRect, 0.0, &origin, SDL_FLIP_NONE);
    }

    SDL_SetRenderTarget(renderTarget, nullptr);

    return messageTexture;
}

MessageTexture::FontAtlas MessageTexture::getFontAtlas(MessageTexture::FontAtlasId fontAtlas)
{
    return fontAtlases[fontAtlas];
}

#define ATLAS_RANGE_NUM 10
#define ATLAS_RANGE_ABC (ATLAS_RANGE_NUM + 26)
#define ATLAS_RANGE_SPEC_1 (ATLAS_RANGE_ABC + 16)

inline uint8_t MessageTexture::getAtlasPos(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }

    c = tolower(c);
    if (c >= 'a' && c <= 'z')
    {
        return c - 'a' + ATLAS_RANGE_NUM;
    }

    if (c >= ' ' && c <= '/')
    {
        return c - ' ' + ATLAS_RANGE_ABC;
    }

    if (c >= ':' && c <= '?')
    {
        return c - ':' + ATLAS_RANGE_SPEC_1;
    }

    return ATLAS_ERROR_POS; // End of atlas
}

#undef ATLAS_RANGE_NUM
#undef ATLAS_RANGE_ABC
#undef ATLAS_RANGE_SPEC_1

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
