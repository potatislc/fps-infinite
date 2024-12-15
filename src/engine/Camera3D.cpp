#include <cmath>
#include <iostream>
#include "Camera3D.h"
#include "App.h"
#include "ResourceLoader.h"
#include "glm/gtc/constants.hpp"
#include "game/Game.h"

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

void Camera3D::drawTexture3D(SDL_Renderer* renderer, UniqueTexture& uniqueTexture,
                             const glm::vec3& worldPoint, SDL_Rect& viewport)
{
    if (worldPoint.z <= 0) return;
    glm::vec3 relativePos = position - worldPoint;

    glm::vec2 forward = {std::cos(rotationY), std::sin(rotationY)};
    glm::vec2 right = {-forward.y, forward.x};

    float distForward = glm::dot((glm::vec2)relativePos, forward);
    float distRight = glm::dot((glm::vec2)relativePos, right);
    float distUp = relativePos.z;

    float screenX = (distRight / distForward) * (viewport.w / 2.0f) + viewport.w / 2.0f;
    float screenY = (distUp / distForward) * viewport.h + viewport.h / 2.0f;

    int textureScale = static_cast<int>((uniqueTexture.getRect()->w / distForward));

    SDL_Rect src = {0, 0, uniqueTexture.getRect()->h, uniqueTexture.getRect()->h};
    SDL_Rect dst = {
            static_cast<int>(screenX - textureScale / 2),
            static_cast<int>(screenY - textureScale / 2),
            textureScale,
            textureScale
    };

    SDL_RenderCopy(renderer, uniqueTexture.get(), &src, &dst);
}

void Camera3D::drawFloor(SDL_Renderer* renderer, UniqueTexture& floorTexture)
{
    SDL_LockSurface(projectedFloor);
    auto* pixels = (uint32_t*)projectedFloor->pixels;
    uint32_t* floorPixels;
    int floorPitch;
    SDL_LockTexture(floorTexture.get(), nullptr, (void**)&floorPixels, &floorPitch);
    int floorPixelsWidth = floorPitch / (int)sizeof(uint32_t);
    int w = projectedFloorRect.w;
    int h = projectedFloorRect.h;
    glm::vec2 cameraPos = position;
    cameraPos /= 2;
    glm::vec2 cameraDir = {std::cos(rotationY), std::sin(rotationY)};
    glm::vec2 cameraRight = {-cameraDir.y, cameraDir.x};
    int floorWidth = floorTexture.getRect()->w;
    int floorHeight = floorTexture.getRect()->h;
    float scale = 4.f;
    int fogLine = h / 5;

    float cameraHeight = position.z * (float)h;

    for (int y = 1; y < h; y++)
    {
        float rowDistance = (cameraHeight / (float)-y);
        glm::vec2 floorRow = cameraPos + cameraDir * rowDistance;
        glm::vec2 orthoRow = cameraRight * rowDistance;
        float fogStrength = glm::clamp(1.0f - (float)y / (float)fogLine, 0.0f, .8f);

        for (int x = 0; x < w; x++)
        {
            float screenX = ((float)x / (float)w) * 2.0f - 1.0f;
            glm::vec2 floorPoint = floorRow + orthoRow * screenX;
            int texX = static_cast<int>(floorPoint.x * scale) % floorWidth;
            int texY = static_cast<int>(floorPoint.y * scale) % floorHeight;
            if (texX < 0) texX += floorWidth;
            if (texY < 0) texY += floorHeight;
            uint32_t color = floorPixels[texY * floorPixelsWidth + texX];

            if (y < fogLine)
            {
                uint8_t r = (color >> 16) & 0xFF;
                uint8_t g = (color >> 8) & 0xFF;
                uint8_t b = color & 0xFF;

                r = static_cast<uint8_t>((float)r + fogStrength * (float)(255 - r));
                g = static_cast<uint8_t>((float)g + fogStrength * (float)(255 - g));
                b = static_cast<uint8_t>((float)b + fogStrength * (float)(255 - b));
                pixels[y * w + x] = (r << 16) | (g << 8) | b;
            }
            else
            {
                pixels[y * w + x] = floorPixels[texY * floorPixelsWidth + texX];
            }
        }
    }

    SDL_UnlockTexture(floorTexture.get());
    SDL_UnlockSurface(projectedFloor);

    SDL_Texture* finalFloorTexture = SDL_CreateTextureFromSurface(renderer, projectedFloor);
    SDL_UpdateTexture(finalFloorTexture, &projectedFloorRect, projectedFloor->pixels, projectedFloor->pitch);

    SDL_Rect src = projectedFloorRect;
    SDL_Rect dst = projectedFloorRect;
    dst.y = static_cast<int>(App::renderer.viewportCenter.y);

    SDL_RenderCopy(renderer, finalFloorTexture, &src, &dst);

    SDL_DestroyTexture(finalFloorTexture);
}


void Camera3D::initFloorSurface()
{
    projectedFloorRect = {0, 0, App::renderer.viewport.w, (int)App::renderer.viewportCenter.y};
    projectedFloor = SDL_CreateRGBSurface(0, projectedFloorRect.w, projectedFloorRect.h, 32, 0, 0, 0, 0);
}
