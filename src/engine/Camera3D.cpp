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

void Camera3D::drawTexture3D(SDL_Renderer* renderer, const glm::vec3& worldPoint)
{
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

/*void Camera3D::drawFloor(SDL_Renderer* renderer, UniqueTexture& floor)
{
    SDL_LockSurface(projectedFloor);
    {
        auto* pixels = (uint32_t*)projectedFloor->pixels;

        for (int i = 0; i < projectedFloorRect.w * projectedFloorRect.h; i++)
        {
            pixels[i] = SDL_MapRGB(projectedFloor->format, 0, 0, (int)(i / projectedFloorRect.w));
        }
    }
    SDL_UnlockSurface(projectedFloor);

    SDL_Texture* floorTexture = SDL_CreateTextureFromSurface(renderer, projectedFloor);
    SDL_UpdateTexture(floorTexture, &projectedFloorRect, projectedFloor->pixels, projectedFloor->pitch);
    SDL_Rect src = projectedFloorRect;
    SDL_Rect dst = projectedFloorRect;
    dst.y = (int)App::renderer.viewportCenter.y;

    SDL_RenderCopy(renderer, floorTexture, &src, &dst);
}*/

void Camera3D::drawFloor(SDL_Renderer* renderer, UniqueTexture& floorTexture)
{
    // Lock the surface for direct pixel manipulation
    SDL_LockSurface(projectedFloor);
    uint32_t* pixels = (uint32_t*)projectedFloor->pixels;
    uint32_t* floorPixels;
    int floorPitch;
    SDL_LockTexture(floorTexture.get(), nullptr, (void**)&floorPixels, &floorPitch);

    int w = projectedFloorRect.w;
    int h = projectedFloorRect.h;

    glm::vec2 cameraDir = {std::cos(rotationY), std::sin(rotationY)};
    glm::vec2 cameraRight = {-cameraDir.y, cameraDir.x};
    glm::vec2 camPos = glm::vec2(position.x, position.z);
    int texWidth = floorTexture.getRect()->w;
    int texHeight = floorTexture.getRect()->h;
    float scale = 16.0f;

    for (int y = 1; y < h; y++)
    {
        float rowDistance = (h / (float)(2 * ((h - y) - App::renderer.viewportCenter.y))) / fovScale;

        for (int x = 0; x < w; x++)
        {
            float screenX = (x / (float)w) * 2.0f - 1.0f;
            glm::vec2 floorPoint = (glm::vec2){position.x / 2, position.z / 2} +
                                   cameraDir * rowDistance +
                                   cameraRight * (screenX * rowDistance);
            int floorWidth = floorTexture.getRect()->w;
            int floorHeight = floorTexture.getRect()->h;
            int texX = static_cast<int>(floorPoint.x * 16) % floorWidth;
            int texY = static_cast<int>(floorPoint.y * 16) % floorHeight;
            if (texX < 0) texX += floorWidth;
            if (texY < 0) texY += floorHeight;
            uint32_t color = floorPixels[texY * (floorPitch / sizeof(uint32_t)) + texX];

            /*float depth = std::min(std::max(2.5f * (y / h), 0.0f), 1.0f);
            uint8_t fog = static_cast<uint8_t>((1 - depth) * 230);
            uint8_t r = (color & 0xFF0000) >> 16;
            uint8_t g = (color & 0x00FF00) >> 8;
            uint8_t b = (color & 0x0000FF);
            r = static_cast<uint8_t>(r * depth + fog);
            g = static_cast<uint8_t>(g * depth + fog);
            b = static_cast<uint8_t>(b * depth + fog);
            // Set the pixel in the screen buffer
            pixels[y * w + x] = (r << 16) | (g << 8) | b;
*/
            pixels[y * w + x] = color;
        }
    }

    /*for (int i = 0; i < w; i++)
    {
        float rowDistance = (h / (float)(2 * ((h - i) - App::renderer.viewportCenter.y))) / fovScale;

        for (int j = 0; j < h; j++)
        {
            float screenX = (j / (float)w) * 2.0f - 1.0f;
            glm::vec2 floorPoint = (glm::vec2){position.x / 2, position.z / 2} +
                                   cameraDir * rowDistance +
                                   cameraRight * (screenX * rowDistance);

            int texX = (int)(floorPoint.x * scale) % texWidth;
            int texY = (int)(floorPoint.y * scale) % texHeight;
            if (texX < 0) texX += texWidth;
            if (texY < 0) texY += texHeight;

            uint32_t color = floorPixels[texY * (floorPitch / sizeof(uint32_t)) + texX];

            // Apply fog shading based on depth (optional)
            float depth = std::min(std::max(2.5f * (std::abs(j) / h), 0.0f), 1.0f);
            uint8_t fog = static_cast<uint8_t>((1 - depth) * 230);

            uint8_t r = (color & 0xFF0000) >> 16;
            uint8_t g = (color & 0x00FF00) >> 8;
            uint8_t b = (color & 0x0000FF);

            r = static_cast<uint8_t>(r * depth + fog);
            g = static_cast<uint8_t>(g * depth + fog);
            b = static_cast<uint8_t>(b * depth + fog);

            // Set the pixel in the screen buffer
            // pixels[j * w + i] = (r << 16) | (g << 8) | b;
            pixels[j * w + i] = color;
            // pixels[i * h + j] = color;
        }
    }*/

    // Unlock the floor texture and surface
    SDL_UnlockTexture(floorTexture.get());
    SDL_UnlockSurface(projectedFloor);

    // Create a texture from the surface and render it
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
