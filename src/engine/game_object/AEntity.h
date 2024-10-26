#pragma once

#include <memory>
#include <vector>
#include "SDL_render.h"
#include "IGameObject.h"

class AEntity : public IGameObject
{
public:
    AEntity* parent = nullptr;

    virtual ~AEntity() = default;
    virtual void start() override = 0;
    virtual void update() override = 0;
    virtual void draw(SDL_Renderer* renderTarget) override = 0;
};

