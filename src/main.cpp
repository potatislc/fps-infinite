#include <SDL.h>
#include <array>
#include <vector>
#include <cmath>
#include <cstdint>
#include "window.h"
#include "application.h"
#include "renderer.h"
#include "tunnel.h"

/*
enum MaterialType
{
    MT_AIR,
    MT_DIRT,
    MT_STONE,
    MT_IRON,
    MT_COPPER,
    MT_GOLD,
    MT_DIAMOND,
    MT_LENGTH
};

enum MaterialCategory
{
    MC_GAS,
    MC_LIQUID,
    MC_SOLID,
    MC_INSTANT_DEATH
};

class Material
{
public:
    MaterialType type;
    MaterialCategory category;
    const float hardness;
    float price;
};

Material air = {MT_AIR, MC_GAS, 0.0f, 0.0f};
Material dirt = {MT_DIRT, MC_SOLID, 1.0f, 0.1f};

class Layer
{
    float hp;

public:
    Material* material;
    int amount{};

    Layer(Material* materialVal, int amountVal)
    {
        material = materialVal;
        amount = amountVal;
        hp = (float)std::abs(amount) * material->hardness;
    }
};

class Rock
{
    const uint8_t visibleLayerCount = 10;
    uint8_t startingLayerIndex = visibleLayerCount / 2;
public:
    std::vector<Layer> layers;

    Rock()
    {
        // All layers before starting layer should be air
        for (int i = 0; i < startingLayerIndex; i++)
        {
            layers.emplace_back(&air, 1);
        }

        // All layers afterward are dirt for now
        for (int i = startingLayerIndex+1; i < visibleLayerCount; i++)
        {
            layers.emplace_back(&dirt, 1);
        }
    }

    Layer nextLayer()
    {
        Layer prevTopLayer = layers[startingLayerIndex];

        // Shift layers
        if (!layers.empty()) layers.erase(layers.begin() + startingLayerIndex);
        layers.emplace_back(&dirt, 1);

        return prevTopLayer;
    }
};

class Miner
{
public:
    std::size_t depth = 0;
    std::array<std::size_t, MT_LENGTH> oresMined{};

    void mine(Rock rock)
    {
        // Mine current layer
        depth++;
        Layer currentLayer = rock.nextLayer();
        oresMined[currentLayer.material->type] += currentLayer.amount;

        // How miner will react to standing on the new top layer
        switch (rock.layers[0].material->type)
        {
            default:
                // Default is an ore you can stand on and mine regularly
                break;
        }
    }
};
*/

Window window;
Application application;
Game game;
Renderer renderer;

int main(int argc, char* args[])
{
    if (!window.init()) return -1;
    if (!renderer.init(window.sdlWindow)) return -1;
    application.run(game, renderer);

    SDL_DestroyRenderer(renderer.sdlRenderer);
    SDL_DestroyWindow(window.sdlWindow);
    SDL_Quit();

    return 0;
}
