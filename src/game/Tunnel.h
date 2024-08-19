#pragma once
#include <SDL.h>
#include <cstdint>
#include <vector>
#include <memory>
#include "Material.h"
#include "engine/IGameObject.h"
#include "engine/UniqueTexture.h"

class Tunnel : IGameObject
{
    const uint8_t activeLayersCount = 16;
    uint8_t floorLayerIndex = 5;
    UniqueTexture materialAtlas;

    void drawCenterColumn(SDL_Renderer* renderTarget);
    void drawWalls(SDL_Renderer* renderTarget);
public:
    enum LayerBehaviorType
    {
        LBT_NONE,
        LBT_SPARKLE,
        LBT_LENGTH
    };

    class Layer
    {
        float hp;
    public:
        Material::Type materialType;
        int amount{};
        LayerBehaviorType behaviorType;

        Layer(Material::Type materialType, int amountVal);
    };

    class LayerBehavior : IGameObject
    {
        std::unique_ptr<Layer> layer;
    };

    std::vector<Layer> layers;
    std::vector<LayerBehavior> layerBehaviors;

    Layer nextLayer();
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderTarget);
};