#include <cmath>
#include "Camera3D.h"
#include "App.h"

Camera3D::Camera3D(float fov) : fov(fov * (float)M_PI / 180), halfFov((fov / 2) * (float)M_PI / 180)
{

}

void Camera3D::drawFov(SDL_Renderer* renderer) const
{
    SDL_Point center = {(int)App::renderer.viewportCenter.x, (int)App::renderer.viewportCenter.y};

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    int lineEndX = (int)(std::sin(halfFov) * (float)center.y);
    SDL_RenderDrawLine(renderer, center.x, center.y, center.x - lineEndX, 0);
    SDL_RenderDrawLine(renderer, center.x, center.y, center.x + lineEndX, 0);
}
