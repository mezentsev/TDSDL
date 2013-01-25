#include "unit.h"

#include <QDebug>

Unit::Unit(Animation *default_anim, int x, int y, sf::ConvexShape shape, b2World * world, Physics::B2_BODY_TYPE type, float SCALE) : Entity(default_anim,x,y,shape,world,type,SCALE)
{
    this->setState(LOOK_RIGHT);
    this->moving = NO;
    jump_hight = 4;
}

void Unit::setControl(ORDER order)
{
    switch(order)
    {
    case MOVE_LEFT:
    {
        this->move_left();
        break;
    }
    case MOVE_RIGHT:
    {
        this->move_right();
        break;
    }
    case JUMP:
    {
        this->jump();
        break;
    }
    case STOP_LEFT:
    {
        this->stop_left();
        break;
    }
    case STOP_RIGHT:
    {
        this->stop_right();
        break;
    }
    }
}

void Unit::setState(STATE state)
{
    this->state = state;
    QString name;
    if (this->state == LOOK_LEFT)  name = "stayLeft";
    if (this->state == LOOK_RIGHT) name = "stayRight";
    if (this->state == WALK_LEFT)  name = "runLeft";
    if (this->state == WALK_RIGHT) name = "runRight";
    if (this->state == JUMP_LEFT)  name = "jumpLeft";
    if (this->state == JUMP_RIGHT) name = "jumpRight";
    if (this->state == HITLER_CAPUT) name = "mostPainfulDeath";

    setAnim(name);
}

int Unit::getState()
{
    return this->state;
}

void Unit::doPhysics(float scale)
{
    b2Body * body = this->phys.getpHbody();

    //старт прыжка
    if (!this->phys.isContact())
    {
        if (this->state == WALK_LEFT || this->state == LOOK_LEFT)
            this->setState(JUMP_LEFT);
        if (this->state == WALK_RIGHT || this->state == LOOK_RIGHT)
            this->setState(JUMP_RIGHT);
    }
    //приземление
    if (this->phys.isContact())
    {
        if (this->state == JUMP_LEFT)
        {
            if (this->moving == NO)
                this->setState(LOOK_LEFT);
            if (this->moving == LEFT)
                this->setState(WALK_LEFT);
        }
        if (this->state == JUMP_RIGHT)
        {
            if (this->moving == NO)
                this->setState(LOOK_RIGHT);
            if (this->moving == RIGHT)
                this->setState(WALK_RIGHT);
        }
    }
//    if (!this->phys.isContact())
//        qDebug()<<111;
//    else qDebug()<<222;

    //движение
    if (moving == LEFT)
        body->SetLinearVelocity(b2Vec2(-4, body->GetLinearVelocity().y));
    if (moving == RIGHT)
        body->SetLinearVelocity(b2Vec2(4, body->GetLinearVelocity().y));

    //обновление координат
    float newX = body->GetPosition().x * scale;
    float newY = body->GetPosition().y * scale;
    float newAngle = remainder(body->GetAngle()*180/b2_pi,360.f);
    this->setXY(newX, newY);
    this->setAngle(newAngle);
}



void Unit::move_left()
{
    this->moving = LEFT;
    if (this->state == LOOK_LEFT || this->state == LOOK_RIGHT || this->state == WALK_RIGHT)
        this->setState(WALK_LEFT);
    if (this->state == JUMP_RIGHT)
        this->setState(JUMP_LEFT);
}

void Unit::move_right()
{
    this->moving = RIGHT;
    if (this->state == LOOK_LEFT || this->state == LOOK_RIGHT || this->state == WALK_LEFT)
        this->setState(WALK_RIGHT);
    if (this->state == JUMP_LEFT)
        this->setState(JUMP_RIGHT);
}

void Unit::stop_left()
{
    if (this->state == WALK_LEFT || this->state == JUMP_LEFT)
    {
        moving = NO;
//        this->phys.getpHbody()->SetLinearVelocity(b2Vec2(0, this->phys.getpHbody()->GetLinearVelocity().y));
        if (this->state == WALK_LEFT)
            this->setState(LOOK_LEFT);
    }
}

void Unit::stop_right()
{
    if (this->state == WALK_RIGHT || this->state == JUMP_RIGHT)
    {
        moving = NO;
//        this->phys.getpHbody()->SetLinearVelocity(b2Vec2(0, this->phys.getpHbody()->GetLinearVelocity().y));
        if (this->state == WALK_RIGHT)
            this->setState(LOOK_RIGHT);
    }
}

void Unit::jump()
{
    if (this->state != JUMP_LEFT && this->state != JUMP_RIGHT)
    {
        b2Body * body = this->phys.getpHbody();
        float v0 = sqrt(2 * this->jump_hight * fabs(this->phys.getGravity()));
        body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -v0));
    }
}
