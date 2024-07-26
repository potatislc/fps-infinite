#pragma once
#include <SDL.h>
#include <cstdint>
#include <vector>
#include "Material.h"
#include "engine/IGameObject.h"

class TunnelLayer
{
    float hp;

public:
    Material::Type materialType;
    int amount{};

    TunnelLayer(Material::Type materialType_, int amountVal);
};

class Tunnel : IGameObject
{
    const uint8_t activeLayersCount = 16;
    uint8_t floorLayerIndex = (activeLayersCount / 2) + 1;
    SDL_Texture* materialAtlas = nullptr;

    void drawCenterColumn(SDL_Renderer* renderTarget, uint8_t depth);
    void drawWalls(SDL_Renderer* renderTarget);
public:
    std::vector<TunnelLayer> layers;

    TunnelLayer nextLayer();
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderTarget);
};

