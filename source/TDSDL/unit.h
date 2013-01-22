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
        FALL_LEFT,
        FALL_RIGHT,
        HITLER_CAPUT
    };

    enum ORDER{
        MOVE_LEFT,
        MOVE_RIGHT,
        STOP_LEFT,
        STOP_RIGHT,
        JUMP
    };

    Unit(Animation * default_anim, int x, int y, int w, int h, b2World * world, Physics::B2_BODY_TYPE type, float SCALE);
    int  getState();
    void doPhysics(float scale);

public slots:
    void setControl(Unit::ORDER order);
    void setState(STATE state);

private:
    STATE state;
};

#endif // UNIT_H
