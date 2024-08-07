#include <iostream>
#include "MessageTexture.h"
#include "ResourceLoader.h"

//
// Tex
//

UniqueTexture MessageTexture::fontTextures[] =
    {
        UniqueTexture() // Default font
    };

MessageTexture::MessageTexture()
{
    fontTextures[0].set(ResourceLoader::loadTexture(FONTS_TEX_PATH"font.png"));
}

void MessageTexture::renderMessage(SDL_Renderer* renderTarget, SDL_Texture* fontTexture, const char* message,
                                   Utils::Vector2 position, SDL_Color color = Utils::Colors::white)
{
    for (int i = 0; i < strlen(message); i++)
    {

    }
}

SDL_Texture* MessageTexture::messageToTexture(SDL_Renderer *renderTarget, SDL_Texture *fontTexture, const char *message,
                                              SDL_Color color = Utils::Colors::white)
{
    return nullptr;
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
