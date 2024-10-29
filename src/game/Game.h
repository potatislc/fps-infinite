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
    static Renderer::ViewPortCamera mapCamera;
    static Camera3D camera3D;

    Game();
    ~Game() override = default;
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderer) override;
private:
    EntityScene world;
    static std::shared_ptr<Player> currentPlayer;
    SDL_Rect mapRect = {0, 0, 64, 64};

    void drawMapEntities(SDL_Renderer* renderer, const EntityScene& entityScene);
};