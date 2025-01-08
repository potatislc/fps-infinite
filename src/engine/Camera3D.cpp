#include <cmath>
#include <iostream>
#include <cstring>
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
                             const glm::vec3& targetPoint, float targetRotZ, SDL_Rect& viewport)
{
    if (targetPoint.z <= 0) return;
    glm::vec3 relativePos = position - targetPoint;

    glm::vec2 forward = {std::cos(rotationZ), std::sin(rotationZ)};
    glm::vec2 right = {-forward.y, forward.x};

    float distForward = glm::dot((glm::vec2)relativePos, forward);
    // if (distForward <= 0) return;
    int textureScale = static_cast<int>((uniqueTexture.getRect()->w / distForward) * 2);
    // if (textureScale <= 1) return;
    float distRight = glm::dot((glm::vec2)relativePos, right);
    float distUp = relativePos.z;

    float screenX = (distRight / distForward);
    // if (screenX < -1 || screenX > 1) return;
    screenX = screenX * (viewport.w / 2.0f) + viewport.w / 2.0f;
    float screenY = (distUp / distForward) * viewport.h + viewport.h / 2.0f;


    int rotFrame = 0;
    glm::vec2 targetForward = {std::cos(targetRotZ), std::sin(targetRotZ)};
    float forwardDot = glm::dot(forward, targetForward);

#define CIRCLE_SECTOR .875f

    if (forwardDot < -CIRCLE_SECTOR)
    {
        rotFrame = 0; // Front
    }
    else if (forwardDot > CIRCLE_SECTOR)
    {
        rotFrame = 4; // Back
    }
    else
    {
        glm::vec2 targetRight = {-targetForward.y, targetForward.x};
        float rightDot = glm::dot(forward, targetRight);

        if (rightDot < -CIRCLE_SECTOR)
        {
            rotFrame = 2;
        }
        else if (rightDot > CIRCLE_SECTOR)
        {
            rotFrame = 6;
        }
        else
        {
            if (forwardDot > 0)
            {
                rotFrame = (rightDot > 0) ? 5 : 3;
            }
            else
            {
                rotFrame = (rightDot > 0) ? 7 : 1;
            }
        }
    }

#undef CIRCLE_SECTOR

    SDL_Rect src = {rotFrame * uniqueTexture.getRect()->h, 0, uniqueTexture.getRect()->h, uniqueTexture.getRect()->h};
    SDL_Rect dst = {
            static_cast<int>(screenX - textureScale / 2),
            static_cast<int>(screenY - textureScale / 2),
            textureScale,
            textureScale
    };

    const int maxBright = 16;
    uint8_t brightness = (dst.w < maxBright) ? dst.w * (255/maxBright) : 255;
    SDL_SetTextureColorMod(uniqueTexture.get(), brightness, brightness, brightness);
    SDL_RenderCopy(renderer, uniqueTexture.get(), &src, &dst);
}

void Camera3D::drawFloor(SDL_Renderer* renderer, SDL_Surface* floorSurface, UniqueTexture& floorTexture,
                         float pixelDensity, const uint32_t* shadowPixels)
{
    SDL_LockSurface(floorSurface);
    auto* pixels = (uint32_t*)floorSurface->pixels;

    uint32_t* floorPixels;
    int floorPitch;
    SDL_LockTexture(floorTexture.get(), nullptr, (void**)&floorPixels, &floorPitch);
    int floorTexWidth = floorTexture.getRect()->w;

    /*uint32_t* shadowPixels;
    int shadowPitch;
    SDL_LockTexture(shadowMap.get(), nullptr, (void**)&shadowPixels, &shadowPitch);
    int shadowTexWidth = shadowMap.getRect()->w;*/

    SDL_Rect surfRect = {0, 0, floorSurface->w, floorSurface->h};
    glm::vec2 cameraPos = position;
    cameraPos /= 2;
    glm::vec2 cameraDir = {std::cos(rotationZ), std::sin(rotationZ)};
    glm::vec2 cameraRight = {-cameraDir.y, cameraDir.x};
    int fogLine = surfRect.h / 5;
    SDL_Point worldTexSize = {(int)(Game::cellSize.x * pixelDensity), (int)(Game::cellSize.y * pixelDensity)};
    double borderAnim = App::timeSinceInit * 8;
    auto waterAnim = (float)(App::timeSinceInit * 2);

    float cameraHeight = position.z * (float)surfRect.h;

    // Ripple mode
    float rippleMag = 2.f;
    auto* ripplePixels = new uint32_t[floorTexWidth * floorTexWidth];
    for (int y = 0; y < floorTexWidth; y++)
    {
        float tempY = (float)y / 4 + waterAnim;
        for (int x = 0; x < floorTexWidth; x++)
        {
            float tempX = (float)x / 4 + waterAnim;
            int rippleX = (int)(x + glm::sin(tempY) * glm::cos(tempX) * rippleMag) % floorTexWidth;
            int rippleY = (int)(y + glm::sin(tempX) * glm::cos(tempY) * rippleMag) % floorTexWidth;
            if (rippleX < 0) rippleX += floorTexWidth;
            if (rippleY < 0) rippleY += floorTexWidth;
            ripplePixels[x + y * floorTexWidth] = floorPixels[rippleX + rippleY * floorTexWidth];
        }
    }

    for (int y = 1; y < surfRect.h; y++)
    {
        float rowDistance = (cameraHeight / (float)-y);
        glm::vec2 floorRow = cameraPos + cameraDir * rowDistance;
        glm::vec2 orthoRow = cameraRight * rowDistance;
        float fogStrength = glm::clamp(1.0f - (float)y / (float)fogLine, 0.0f, .8f);

        for (int x = 0; x < surfRect.w; x++)
        {
            float screenX = ((float)x / (float)surfRect.w) * 2.0f - 1.0f;
            glm::vec2 floorPoint = floorRow + orthoRow * screenX;
            /*float temp1 = (float)x / 4 + waterAnim;
            float temp2 = (float)y / 4 + waterAnim;
            floorPoint.y += glm::sin(temp1) * glm::cos(temp2) * .02f;
            floorPoint.x += glm::sin(temp2) * glm::cos(temp1) * .02f;*/
            uint32_t color;
            uint32_t shadowColor;
            int texX = static_cast<int>(floorPoint.x * pixelDensity * 2);
            int texY = static_cast<int>(floorPoint.y * pixelDensity * 2);
            texX %= worldTexSize.x;
            texY %= worldTexSize.y;
            if (texX < 0) texX += worldTexSize.x;
            if (texY < 0) texY += worldTexSize.y;

#define BORDER_WIDTH 2
            if ((texX <= BORDER_WIDTH || texY <= BORDER_WIDTH) && y >= fogLine / 4)
            {
                uint8_t worldBorderBrightness = 0x7F + (int)(std::abs(glm::sin(borderAnim + (double)x / 16)) * 0x7f);
                pixels[y * surfRect.w + x] = (worldBorderBrightness << 16) | (worldBorderBrightness << 8) | worldBorderBrightness;
                continue;
            }
#undef BORDER_WIDTH

            color = ripplePixels[(texY % floorTexWidth) * floorTexWidth + (texX % floorTexWidth)];
            shadowColor = shadowPixels[(texY % worldTexSize.x) * worldTexSize.x + (texX % worldTexSize.x)];

            uint8_t rippleR = (color >> 16) & 0xFF;
            uint8_t rippleG = (color >> 8) & 0xFF;
            uint8_t rippleB = color & 0xFF;

            uint8_t shadowR = (shadowColor >> 16) & 0xFF;

            int finalR = rippleR - shadowR;
            int finalG = rippleG - shadowR;
            int finalB = rippleB - shadowR;
            if (finalR < 0) finalR = 0;
            if (finalG < 0) finalG = 0;
            if (finalB < 0) finalB = 0;

            finalR = static_cast<uint8_t>((float)finalR - fogStrength * (float)(finalR));
            finalG = static_cast<uint8_t>((float)finalG - fogStrength * (float)(finalG));
            finalB = static_cast<uint8_t>((float)finalB - fogStrength * (float)(finalB));

            pixels[y * surfRect.w + x] = (finalB << 16) | (finalG << 8) | finalR;
        }
    }

    SDL_UnlockTexture(floorTexture.get());
    SDL_UnlockSurface(floorSurface);

    SDL_Texture* finalFloorTexture = SDL_CreateTextureFromSurface(renderer, floorSurface);
    SDL_UpdateTexture(finalFloorTexture, &surfRect, floorSurface->pixels, floorSurface->pitch);

    SDL_Rect src = surfRect;
    SDL_Rect dst = surfRect;
    dst.y = static_cast<int>(App::renderer.viewportCenter.y);

    SDL_RenderCopy(renderer, finalFloorTexture, &src, &dst);

    SDL_DestroyTexture(finalFloorTexture);
}

void Camera3D::initFloorProjectionSurface(SDL_Surface*& surface, int w, int h)
{
    SDL_Rect rect = {0, 0, w, h};
    surface = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0, 0, 0, 0);
}
