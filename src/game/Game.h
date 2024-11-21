#pragma once

#include "SDL_render.h"
#include "engine/game_object/IGameObject.h"
#include "engine/game_object/EntityScene.h"
#include "engine/Camera3D.h"
#include "engine/Renderer.h"
#include "Player.h"

class Game : public IGameObject
{
public:
    class Settings
    {
    public:
        float mouseSens = .5f;
    };

    static Renderer::ViewPortCamera mapCamera;
    static Camera3D camera3D;
    static Settings settings;

    Game();
    ~Game() override = default;
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderer) override;
private:
    EntityScene<Entity3D> world;
    static std::shared_ptr<Player> currentPlayer;
    SDL_Rect mapRect = {0, 0, 64, 64};
    const float mapScale = 1.f;
    const SDL_Point mapCenter = {mapRect.w / 2, mapRect.h / 2};
    const float mapRadiusSq = (float)mapCenter.x * (float)mapCenter.y;

    void drawEntitiesDepth(SDL_Renderer* renderer);
    void drawEntitiesToMap(SDL_Renderer* renderer);
    void drawBackground(SDL_Renderer* renderer);
};