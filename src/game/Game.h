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
        float mouseSens = 10.f;
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

    void drawMapEntities(SDL_Renderer* renderer, const EntityScene<Entity3D>& entityScene);
};