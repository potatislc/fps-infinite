#include <cmath>
#include "Camera3D.h"

Camera3D::Camera3D(float fov) : fov(fov * (float)M_PI / 180), halfFov((fov / 2) * (float)M_PI / 180)
{

}
