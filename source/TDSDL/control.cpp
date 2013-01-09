#include "control.h"

Control::Control()
{
    keypress["cam_right"] = false;
    keypress["cam_left"]  = false;
    keypress["cam_down"]  = false;
    keypress["cam_up"]    = false;
}

Control::~Control()
{

}

void Control::setEntities(Resources<Entity> *_entities)
{
    this->_entities = _entities;
}

void Control::setCamera(Camera *camera)
{
    this->camera = camera;
}

void Control::cameraLeft(bool down)
{
    if (down)
    {
        keypress["cam_left"] = true;
    }
    if (!down)
    {
        keypress["cam_left"] = false;
    }
}

void Control::cameraRight(bool down)
{
    if (down)
    {
        keypress["cam_right"] = true;
    }
    if (!down)
    {
        keypress["cam_right"] = false;
    }
}

void Control::cameraDown(bool down)
{
    if (down)
    {
        keypress["cam_down"] = true;
    }
    if (!down)
    {
        keypress["cam_down"] = false;
    }
}

void Control::cameraUp(bool down)
{
    if (down)
    {
        keypress["cam_up"] = true;
    }
    if (!down)
    {
        keypress["cam_up"] = false;
    }
}

void Control::events()
{
    moveCamera();
}

void Control::moveCamera()
{
    if (keypress["cam_right"])
        camera->translate(1,0);
    if (keypress["cam_left"])
        camera->translate(-1,0);
    if (keypress["cam_down"])
        camera->translate(0,1);
    if (keypress["cam_up"])
        camera->translate(0,-1);
}
