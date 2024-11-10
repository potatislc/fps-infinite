#include <cmath>
#include "Camera3D.h"
#include "App.h"
#include "ResourceLoader.h"

Camera3D::Camera3D(glm::vec3 position, float rotationY, float fov) :
    Entity3D(position, rotationY), fov(fov * (float) M_PI / 180), halfFov((fov / 2) * (float) M_PI / 180)
{

}

void Camera3D::drawFovLines(SDL_Renderer* renderer) const
{
    SDL_Point center = {(int)App::renderer.viewportCenter.x, (int)App::renderer.viewportCenter.y};

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    int lineEndX = (int)(std::sin(halfFov) * (float)center.y);
    SDL_RenderDrawLine(renderer, center.x, center.y, center.x - lineEndX, 0);
    SDL_RenderDrawLine(renderer, center.x, center.y, center.x + lineEndX, 0);
}

void Camera3D::drawTexture(SDL_Renderer* renderer, glm::vec3 worldPoint) {
    glm::vec3 relativePos = position - worldPoint;

    float cosAngle = glm::cos(-rotationY);
    float sinAngle = glm::sin(-rotationY);
    float rotatedX = relativePos.x * cosAngle - relativePos.z * sinAngle;
    float rotatedZ = relativePos.x * sinAngle + relativePos.z * cosAngle;

    // Ignore points that are too close or behind the camera
    if (rotatedZ <= 0.1f) return;

    // Project to screen position with FOV scaling
    float FOV_SCALE = 20.f;
    int screenX = (App::renderer.viewport.w / 2) + (rotatedX / rotatedZ) * FOV_SCALE;

    SDL_Rect* srcRect = ResourceLoader::loadedTextures.playerMapIcon.getRect();

    // Scale sprite size based on inverse depth to simulate correct perspective
    float depthFactor = 1.0f / rotatedZ;
    int spriteHeight = static_cast<int>(srcRect->h * depthFactor * 2);
    int spriteWidth = static_cast<int>(srcRect->w * depthFactor * 2);

    SDL_Rect dst = {screenX - spriteWidth / 2,
                    (App::renderer.viewport.h / 2) - spriteHeight / 2,
                    spriteWidth,
                    spriteHeight};

    SDL_RenderCopy(renderer,
                   ResourceLoader::loadedTextures.playerMapIcon.get(),
                   srcRect,
                   &dst);
}
