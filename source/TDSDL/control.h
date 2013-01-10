#ifndef CONTROL_H
#define CONTROL_H

#include "resources.h";
#include "entity.h"
#include "camera.h"
#include <QMap>
#include <QObject>

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

    void events();
    void moveCamera();

    void cameraLeft (bool down);
    void cameraRight(bool down);
    void cameraUp   (bool down);
    void cameraDown (bool down);

signals:
    void moveAdd(int dx, int dy){};

public slots:
    void lateAdd(int dx, int dy);
};

#endif // CONTROL_H
