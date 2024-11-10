#include <cmath>
#include "Camera3D.h"
#include "App.h"

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

void Camera3D::drawTexture(SDL_Renderer* renderer, glm::vec3 worldPoint)
{
    glm::vec3 relativePoint = worldPoint - position;
    float relativeDist = glm::length(relativePoint);
    float angleY = std::atan2(relativePoint.z, relativePoint.y);
    if (angleY > rotationY + halfFov || angleY < rotationY - halfFov) return;
    float relativeAngle = rotationY - angleY;

    SDL_Rect dst = {};

    // SDL_RenderCopyEx(renderer)
}
