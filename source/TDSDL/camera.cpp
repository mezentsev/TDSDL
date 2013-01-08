#include "camera.h"

Camera::Camera()
{
    this->x = 5;
    this->y = 0;
}

void Camera::moveTo(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Camera::translate(int dx, int dy)
{
    this->x = this->x + dx;
    this->y = this->y + dy;
}

int Camera::getX()
{
    return this->x;
}

int Camera::getY()
{
    return this->y;
}
