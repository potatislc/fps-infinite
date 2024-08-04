#pragma once

class IGameObject
{
public:
    virtual ~IGameObject() = default;
    virtual void start() = 0;
    virtual void update() = 0;
    virtual void draw(SDL_Renderer* renderTarget) {};
};

