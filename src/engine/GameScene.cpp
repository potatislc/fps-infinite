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
    for (const auto& gameObject : gameObjects)
    {
        if (gameObject == nullptr)
        {
            gameObjects.push_back(gameObject);
            // break;
        }
        else
        {
            gameObject->update();
        }
    }
}

void GameScene::draw(SDL_Renderer *renderTarget)
{
    for (const auto& gameObject : gameObjects)
    {
        if (gameObject != nullptr) gameObject->draw(renderTarget);
    }
}

void GameScene::addGameObject(IGameObject* gameObject)
{
    gameObjects.emplace_back(gameObject);
    gameObject->start();
}
