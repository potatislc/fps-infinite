#pragma once

#include <SDL.h>
#include <sstream>
#include "engine/IGameObject.h"
#include "game/miner/Miner.h"

class UiGameplay : IGameObject
{
    class CollectionParticle
    {
        Utils::Vector2 position;
        const Utils::Vector2 targetPosition;
    };

    class CollectionParticleHandler
    {

    };

    Tunnel* tunnel;
    static SDL_Renderer* sdlRenderer;
    static std::stringstream minerDepthText;
    static UniqueTexture minerDepthMessage;
    static UniqueTexture materialIcons;
    static std::array<UniqueTexture, Material::T_LENGTH> materialsMinedMessage;
    static void onMinerDug(uint depth, Material::Type materialType, uint materialAmount);
public:
    UiGameplay(Tunnel* tunnel, Miner* miner);
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderTarget) override;
};
