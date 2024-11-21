#include <cmath>
#include <iostream>
#include "Camera3D.h"
#include "App.h"
#include "ResourceLoader.h"
#include "glm/gtc/constants.hpp"

Camera3D::Camera3D(glm::vec3 position, float rotationY, float fov, int farPlane) :
    Entity3D(position, rotationY), fov(fov * (float) M_PI / 180), halfFov((fov / 2) * (float) M_PI / 180), farPlane(farPlane)
{
    fovScale = tan(halfFov);
}


void Camera3D::drawFovLines(SDL_Renderer* renderer) const
{
    SDL_Point center = {(int)App::renderer.viewportCenter.x, (int)App::renderer.viewportCenter.y};

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    int lineEndX = (int)(std::sin(halfFov) * (float)center.y);
    SDL_RenderDrawLine(renderer, center.x, center.y, center.x - lineEndX, 0);
    SDL_RenderDrawLine(renderer, center.x, center.y, center.x + lineEndX, 0);
    // SDL_RenderDrawLine(renderer, 0, center.y, App::renderer.viewport.w, center.y);
    // SDL_RenderDrawLine(renderer, center.x, center.y, center.x, 0);
}

void Camera3D::drawTexture(SDL_Renderer* renderer, const glm::vec3& worldPoint) {
    glm::vec2 pointDir2D = {position.x - worldPoint.x, position.z - worldPoint.z};
    float pointAngle = std::atan2(pointDir2D.y, pointDir2D.x);
    float angleBetween = std::atan2(std::sin(pointAngle - rotationY), std::cos(pointAngle - rotationY));
    float d = glm::length(pointDir2D);
    float h = glm::cos(angleBetween) * d;

    int frameSize = ResourceLoader::loadedTextures.swarm.getRect()->h;
    float scale = (16.f / h) * ((float)frameSize / fovScale);

    float normalizedAngle = angleBetween / halfFov; // Range [-1, 1]
    int screenX = static_cast<int>((normalizedAngle + 1.0f) * 0.5f * (float)App::renderer.viewport.w);

    SDL_Rect src = {(int)((pointAngle + M_PI) / (M_PI / 4)) * frameSize, 0, frameSize, frameSize};

    SDL_Rect dst = {screenX - (int)scale / 2,
                    (int)(App::renderer.viewportCenter.y + (worldPoint.y * scale) - scale / 2),
                    (int)scale,
                    (int)scale};

    SDL_RenderCopy(renderer,
                   ResourceLoader::loadedTextures.swarm.get(),
                   &src,
                   &dst);
}

void Camera3D::drawFloor(SDL_Renderer* renderer, SDL_Texture* floor)
{
    SDL_LockSurface(floorSurface);
    {
        auto* pixels = (uint32_t*)floorSurface->pixels;

        for (int i = 0; i < floorRect.w * floorRect.h; i++)
        {
            pixels[i] = SDL_MapRGB(floorSurface->format, 0, 0, (int)(i / floorRect.w));
        }
    }
    SDL_UnlockSurface(floorSurface);

    SDL_Texture* floorTexture = SDL_CreateTextureFromSurface(renderer, floorSurface);
    SDL_UpdateTexture(floorTexture, &floorRect, floorSurface->pixels, floorSurface->pitch);
    SDL_Rect src = floorRect;
    SDL_Rect dst = floorRect;
    dst.y = (int)App::renderer.viewportCenter.y;

    SDL_RenderCopy(renderer, floorTexture, &src, &dst);
}

void Camera3D::initFloorSurface()
{
    floorRect = {0, 0, App::renderer.viewport.w, (int)App::renderer.viewportCenter.y};
    floorSurface = SDL_CreateRGBSurface(0, floorRect.w, floorRect.h, 32, 0, 0, 0, 0);
}
