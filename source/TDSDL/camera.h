#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>

class Camera
{
private:
    int x, y;

public:
    Camera();
    int getX();
    int getY();

    void moveTo   (int x,  int y);
    void translate(int dx, int dy);

public slots:
    void lateAdd(int dx, int dy);
};

#endif // CAMERA_H
