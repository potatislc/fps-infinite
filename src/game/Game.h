#pragma once

#include "SDL_render.h"
#include "engine/game_object/IGameObject.h"
#include "engine/game_object/EntityScene.h"
#include "engine/Camera3D.h"
#include "engine/Renderer.h"
#include "game/characters/Player.h"

class Game : public IGameObject
{
public:
    class Settings
    {
    public:
        float mouseSens = .002f;
    };

    static glm::vec2 cellSize;
    static Renderer::ViewPortCamera mapCamera;
    static Camera3D camera3D;
    static Settings settings;

    Game();
    ~Game() override = default;
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderer) override;

    static std::shared_ptr<Player> currentPlayer;
private:
    EntityScene<Entity3D> world;
    SDL_Texture* mapTexture = nullptr;
    SDL_Rect mapRect = {0, 0, 64, 64};
    const float mapScale = 1.f;
    const SDL_Point mapCenter = {mapRect.w / 2, mapRect.h / 2};
    const float mapRadiusSq = (float)mapCenter.x * (float)mapCenter.y;
    const float mapRenderRadiusSq = mapRadiusSq;

    SDL_Surface* projectedFloor = nullptr;
    const float floorPixelDensity = 8.f;
    const float shadowPixelDensity = 4.f;
    UniqueTexture shadowMap;
    uint32_t* shadowPixels = nullptr;
    int shadowTileIndex = 0;

#define CELLS_W (5) // Has to be odd number >= 3
    const int centerCellId = (CELLS_W * CELLS_W) / 2;

    void drawEntityCells(SDL_Renderer* renderer);
    void drawEntitiesDepth(SDL_Renderer* renderer, int cellId);
    std::vector<Entity3D*> getEntitiesDepthOrder();
    void drawEntities(SDL_Renderer* renderer, int cellId, const std::vector<Entity3D*>& entityDistances);
    void drawEntitiesToMap(SDL_Renderer* renderer);
    void drawMap(SDL_Renderer* renderer);
    void drawBackground(SDL_Renderer* renderer);
    void castShadow(SDL_Renderer* renderer, UniqueTexture& shadowTexture, glm::vec2 castPos);
    void castEntityShadows(SDL_Renderer* renderer, int subdivisions);
    void wrapInsideWorld(glm::vec3& vec);
    glm::vec2 getCellPos(int cellId);
};