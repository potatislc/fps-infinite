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

#define CELLS_W 5
    std::array<bool, CELLS_W * CELLS_W> cellsToRender;
    const uint8_t centerCellId = (CELLS_W * CELLS_W) / 2;

    std::vector<std::pair<float, Entity3D*>> drawEntitiesDepth(SDL_Renderer* renderer, uint8_t cellId);
    void drawEntitiesToMap(SDL_Renderer* renderer, uint8_t cellId);
    void drawMap(SDL_Renderer* renderer);
    void drawBackground(SDL_Renderer* renderer);
    void castShadowToFloor(SDL_Renderer* renderer, UniqueTexture& floor, UniqueTexture& shadowTex, glm::vec2 castPos);
    void wrapInsideWorld(glm::vec3& vec);
    glm::vec2 getCellPos(uint8_t cellId);
};