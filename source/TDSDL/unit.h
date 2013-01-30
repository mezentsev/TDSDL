﻿#ifndef UNIT_H
#define UNIT_H

#include "entity.h"
#include <QString>

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
        HITLER_CAPUT
    };

    enum ORDER{
        MOVE_LEFT,
        MOVE_RIGHT,
        STOP_LEFT,
        STOP_RIGHT,
        JUMP
    };

    enum MOVING{
        LEFT, RIGHT, UP, DOWN, NO
    };

    Unit(Animation * default_anim, int x, int y, sf::ConvexShape shape, QList<sf::ConvexShape> physShapes, b2World * world, Physics::B2_BODY_TYPE type, float SCALE);
    int  getState();
    void doPhysics(float scale);

public slots:
    void setControl(Unit::ORDER order);
    void setState(Unit::STATE state);

private:
    STATE state;
    MOVING moving;
    float jump_hight;
    float rate;

    void move_left();
    void move_right();
    void stop_left();
    void stop_right();
    void jump();
};

#endif // UNIT_H
