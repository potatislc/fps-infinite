#pragma once

#include "AEntity.h"

class EntityScene : public AEntity
{
public:
    AEntity* parent = nullptr;
    std::vector<std::unique_ptr<AEntity>> children;

    ~EntityScene() = default;
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderTarget) override;

    void addChild(std::unique_ptr<AEntity> child);
    void removeChild(AEntity* child);
};
