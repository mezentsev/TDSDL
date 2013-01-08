#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
private:
    int x, y;

public:
    Camera();
    void moveTo   (int x,  int y);
    void translate(int dx, int dy);
    int getX();
    int getY();
};

#endif // CAMERA_H
