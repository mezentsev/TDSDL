#ifndef CONTROL_H
#define CONTROL_H

#include "resources.h";
#include "entity.h"
#include "camera.h"
#include <QMap>

class Control
{
private:
    Resources<Entity> *_entities;
    Camera *camera;
    QMap<QString, bool> keypress;

public:
    Control();
    ~Control();
    void setEntities(Resources<Entity> *_entities);
    void setCamera  (Camera *camera);
    void cameraLeft (bool down);
    void cameraRight(bool down);
    void cameraUp   (bool down);
    void cameraDown (bool down);

    void events();
    void moveCamera();
};

#endif // CONTROL_H
