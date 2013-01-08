#include "camera.h"

Camera::Camera()
{
    this->x = 0;
    this->y = 0;
}

void Camera::moveTo(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Camera::translate(int dx, int dy)
{
    this->x = this->x + x;
    this->y = this->y + y;
}
