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

void Camera3D::drawTexture(SDL_Renderer* renderer, glm::vec3 worldPoint) {
    glm::vec2 pointDir2D = {position.x - worldPoint.x, position.z - worldPoint.z};
    float pointAngle = std::atan2(pointDir2D.y, pointDir2D.x);
    float angleBetween = std::atan2(std::sin(pointAngle - rotationY), std::cos(pointAngle - rotationY));
    if (angleBetween > halfFov || angleBetween < -halfFov) return;
    float d = glm::length(pointDir2D);
    if ((int)d > farPlane) return; // Probably won't be needed in final product since it's rendered in cells
    float h = glm::cos(angleBetween) * d;

    int frameSize = ResourceLoader::loadedTextures.swarm.getRect()->h;
    float scale = (16.f / h) * ((float)frameSize / fovScale);

    float normalizedAngle = angleBetween / halfFov; // Range [-1, 1]
    int screenX = static_cast<int>((normalizedAngle + 1.0f) * 0.5f * (float)App::renderer.viewport.w);

    float wrappedAngle = fmod(pointAngle + 2 * M_PI, 2 * M_PI);
    int directionIndex = static_cast<int>(wrappedAngle / (M_PI / 4));
    SDL_Rect src = {directionIndex * frameSize, 0, frameSize, frameSize};

    SDL_Rect dst = {screenX - (int)scale / 2,
                    (int)(App::renderer.viewportCenter.y + (worldPoint.y * scale) - scale / 2),
                    (int)scale,
                    (int)scale};

    SDL_RenderCopy(renderer,
                   ResourceLoader::loadedTextures.swarm.get(),
                   &src,
                   &dst);
}
