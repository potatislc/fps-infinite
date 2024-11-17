#include <cmath>
#include <iostream>
#include "Camera3D.h"
#include "App.h"
#include "ResourceLoader.h"
#include "glm/gtc/constants.hpp"

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
    SDL_RenderDrawLine(renderer, 0, center.y, App::renderer.viewport.w, center.y);
    SDL_RenderDrawLine(renderer, center.x, center.y, center.x, 0);
}

void Camera3D::drawTexture(SDL_Renderer* renderer, glm::vec3 worldPoint) {
    SDL_Point center = {(int)App::renderer.viewportCenter.x, (int)App::renderer.viewportCenter.y};
    glm::vec2 worldPoint2D = {worldPoint.x, worldPoint.z};
    glm::vec2 position2D = {position.x, position.z};
    glm::vec2 pointDir = glm::normalize(position2D - worldPoint2D);
    glm::vec2 camDir = glm::normalize(glm::vec2(glm::cos(rotationY), glm::sin(rotationY)));
    /*SDL_SetRenderDrawColor(renderer, 32, 200, 200, 255);
    SDL_RenderDrawLine(renderer, center.x, center.y, center.x + pointDir.x * 16, center.y + pointDir.y * 16);
    SDL_SetRenderDrawColor(renderer, 200, 200, 30, 255);
    SDL_RenderDrawLine(renderer, center.x, center.y, center.x + camDir.x * 16, center.y + camDir.y * 16);*/
    // SDL_RenderDrawPoint(renderer, center.x + worldPoint2D.x - position2D.x, center.y + worldPoint2D.y - position2D.y);
    float pointAngle = std::atan2(pointDir.y, pointDir.x);
    float camAngle = std::atan2(camDir.y, camDir.x);
    float angleBetween = std::atan2(std::sin(pointAngle - camAngle), std::cos(pointAngle - camAngle));
    if (std::abs(angleBetween) > halfFov) return;
    float d = glm::distance(worldPoint2D, position2D);
    float h = glm::cos(angleBetween) * d;
    // if (h <= 0) return;


    int scale = (int)((16.f / h) * 16.f);

    float normalizedAngle = angleBetween / halfFov; // Range [-1, 1]
    int screenX = (int)((normalizedAngle + 1.0f) * 0.5f * (float)App::renderer.viewport.w);

    SDL_Rect dst = {screenX - scale / 2, // Center horizontally
                    (int)App::renderer.viewportCenter.y - scale / 2, // Center vertically
                    scale,
                    scale};

    SDL_RenderCopy(renderer,
                   ResourceLoader::loadedTextures.playerMapIcon.get(),
                   ResourceLoader::loadedTextures.playerMapIcon.getRect(),
                   &dst);
}
