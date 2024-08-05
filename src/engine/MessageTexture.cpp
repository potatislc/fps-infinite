#include <iostream>
#include "MessageTexture.h"
#include "ResourceLoader.h"

const std::map<const char*, SDL_Texture*> fontTextures =
{
    {"Default", ResourceLoader::loadTexture(FONTS_TEX_PATH"font.png")}
};


//
// Tex
//

void MessageTexture::renderMessage(SDL_Renderer* renderTarget, SDL_Texture* fontTexture, const char* message,
                                   Utils::Vector2 position, SDL_Color color = Utils::DefaultColors::white)
{

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

    texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);
}

MessageTextureTTF::~MessageTextureTTF()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}
