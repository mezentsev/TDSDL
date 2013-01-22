#include "unit.h"

#include <QDebug>

Unit::Unit(Animation *default_anim, int x, int y, int w, int h, b2World * world, float SCALE) : Entity(default_anim,x,y,w,h,world,SCALE)
{
    this->setState(LOOK_RIGHT);
    this->phys.setShape(x, y, w, h);
    this->phys.createBody((void *)x);
}

void Unit::setControl(int state)
{
    STATE st = STATE(state);
    if (this->state == LOOK_LEFT)
    {
        if (st == WALK_LEFT || st == WALK_RIGHT || st == JUMP)
            this->setState(st);
    }
    else if (this->state == LOOK_RIGHT)
    {
        if (st == WALK_LEFT || st == WALK_RIGHT || st == JUMP)
            this->setState(st);
    }
    else if (this->state == WALK_LEFT)
    {
        if (st == LOOK_LEFT || st == WALK_RIGHT)
            this->setState(st);
        if (st == JUMP)
            this->setState(JUMP_LEFT);
    }
    else if (this->state == WALK_RIGHT)
    {
        if (st == LOOK_RIGHT || st == WALK_LEFT)
            this->setState(st);
        if (st == JUMP)
            this->setState(JUMP_RIGHT);
    }
    else if (this->state == JUMP_LEFT)
    {

    }
}

void Unit::setState(STATE state)
{
    this->state = state;
    QString name;
    if (this->state == LOOK_LEFT) name = "stayLeft";
    if (this->state == LOOK_RIGHT) name = "stayRight";
    if (this->state == WALK_LEFT) name = "runLeft";
    if (this->state == WALK_RIGHT) name = "runRight";
    if (this->state == JUMP_LEFT) name = "jumpLeft";
    if (this->state == JUMP_RIGHT) name = "jumpRight";
    if (this->state == JUMP) name = "jumpUp";
    if (this->state == HITLER_CAPUT) name = "mostPainfulDeath";
    setAnim(name);
}

int Unit::getState()
{
    return this->state;
}
