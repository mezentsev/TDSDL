#ifndef UNIT_H
#define UNIT_H

#include "entity.h"

class Unit : public Entity
{
    Q_OBJECT
public:
    enum STATE{
        LOOK_LEFT,
        LOOK_RIGHT,
        WALK_LEFT,
        WALK_RIGHT,
        JUMP_LEFT,
        JUMP_RIGHT,
        JUMP,
        HITLER_CAPUT
    };

    Unit(Animation * default_anim, int x, int y, int w, int h, b2World * world, Physics::B2_BODY_TYPE type, float SCALE);
    int  getState();

public slots:
    void setControl(int state);
    void setState(STATE state);

private:
    STATE state;
};

#endif // UNIT_H
