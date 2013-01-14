#include "unit.h"

#include <QDebug>

Unit::Unit(Animation *anim)
{
    this->addAnim(anim, "default");
    this->setDefault();
    this->setState(1);
}

void Unit::setControl(int state)
{
    if (this->state == 0)
    {
        if (state == 2 || state == 3 || state == 6)
            setState(state);
    }
    else if (this->state == 1)
    {
        if (state == 2 || state == 3 || state == 6)
            setState(state);
    }
    else if (this->state == 2)
    {
        if (state == 0 || state == 3)
            setState(state);
        if (state == 6)
            setState(4);
    }
    else if (this->state == 3)
    {
        if (state == 1 || state == 2)
            this->setState(state);
        if (state == 6)
            setState(5);
    }
    else if (this->state == 4)
    {

    }
}

void Unit::setState(int state)
{
    this->state = state;
    QString name;
    if (this->state == 0) name = "stayLeft";
    if (this->state == 1) name = "stayRight";
    if (this->state == 2) name = "runLeft";
    if (this->state == 3) name = "runRight";
    if (this->state == 4) name = "jumpLeft";
    if (this->state == 5) name = "jumpRight";
    if (this->state == 6) name = "jumpUp";
    if (this->state == 7) name = "mostPainfulDeath";
    setAnim(name);
}

int Unit::getState()
{
    return this->state;
}
