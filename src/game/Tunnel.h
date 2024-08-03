#pragma once
#include <SDL.h>
#include <cstdint>
#include <vector>
#include "Material.h"
#include "engine/IGameObject.h"

class Tunnel : IGameObject
{
    const uint8_t activeLayersCount = 16;
    uint8_t floorLayerIndex = (activeLayersCount / 2) + 1;
    SDL_Texture* materialAtlas = nullptr;

    void drawCenterColumn(SDL_Renderer* renderTarget, uint8_t depth);
    void drawWalls(SDL_Renderer* renderTarget);
public:
    class Layer
    {
        float hp;

    public:
        Material::Type materialType;
        int amount{};

        Layer(Material::Type materialType, int amountVal);
    };

    std::vector<Layer> layers;

    Layer nextLayer();
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderTarget);
};

