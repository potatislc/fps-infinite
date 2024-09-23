#include "engine/GameScene.h"

void GameScene::start()
{
    for (const std::shared_ptr<IGameObject>& gameObject : gameObjects)
    {
        gameObject->start();
    }
}

void GameScene::update()
{
    for (const std::shared_ptr<IGameObject>& gameObject : gameObjects)
    {
        gameObject->update();
    }
}

void GameScene::draw(SDL_Renderer *renderTarget)
{
    for (const std::shared_ptr<IGameObject>& gameObject : gameObjects)
    {
        gameObject->draw(renderTarget);
    }
}

void GameScene::addGameObject(IGameObject* gameObject)
{
    gameObjects.emplace_back(gameObject);
    gameObject->start();
}
