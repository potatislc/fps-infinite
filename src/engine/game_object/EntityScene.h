#pragma once

#include "AEntity.h"

class EntityScene : public AEntity
{
public:
    AEntity* parent = nullptr;
    std::vector<std::shared_ptr<AEntity>> children;

    ~EntityScene() = default;
    void start() override;
    void update() override;
    void draw(SDL_Renderer* renderTarget) override;

    void addChild(const std::shared_ptr<AEntity>& child);
    void removeChild(AEntity* child);
};
