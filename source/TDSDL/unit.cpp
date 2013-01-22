#include "unit.h"

#include <QDebug>

Unit::Unit(Animation *default_anim, int x, int y, int w, int h, b2World * world, Physics::B2_BODY_TYPE type, float SCALE) : Entity(default_anim,x,y,w,h,world,type,SCALE)
{
    this->setState(LOOK_RIGHT);
}

void Unit::setControl(ORDER order)
{
    switch(this->state){
        case LOOK_LEFT:
        {
            if (order == MOVE_LEFT)
            {
                this->setState(WALK_LEFT);
            }
            if (order == MOVE_RIGHT)
            {
                this->setState(WALK_RIGHT);
            }
            if (order == STOP_RIGHT)
            {
                this->setState(LOOK_RIGHT);
            }
            if (order == JUMP)
            {
                this->setState(JUMP_LEFT);
            }
            break;
            //                if (canJump) {
            //                    if (event.key.code == sf::Keyboard::Right) {
            //                        float impulse = (7.0f - body->GetLinearVelocity().x);
            //                        body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter());
            //                    }
            //                    if (event.key.code == sf::Keyboard::Left) {
            //                        float impulse = -(7.0f + body->GetLinearVelocity().x);
            //                        body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter());
            //                    }
            //                }
            //                if (canJump && event.key.code == sf::Keyboard::Up) {
            //                    float impulse = -(7.0f + body->GetLinearVelocity().y);
            //                    body->ApplyLinearImpulse(b2Vec2(0, impulse) ,body->GetWorldCenter());
            //                }
            //                if (!canJump) {
            //                    // Сопротивление воздуха
            //                    //body->ApplyForce(b2Vec2(-0.5f * body->GetLinearVelocity().x, 0), body->GetWorldCenter());
            //                }
        }
        case LOOK_RIGHT:
        {
            if (order == MOVE_LEFT)
            {
                this->setState(WALK_LEFT);
            }
            if (order == MOVE_RIGHT)
            {
                this->setState(WALK_RIGHT);
            }
            if (order == STOP_LEFT)
            {
                this->setState(LOOK_LEFT);
            }
            if (order == JUMP)
            {
                this->setState(JUMP_RIGHT);
            }
            break;
        }
        case WALK_LEFT:
        {
            if (order == MOVE_RIGHT)
            {
                this->setState(WALK_RIGHT);
            }
            if (order == STOP_LEFT)
            {
                this->setState(LOOK_LEFT);
            }
            if (order == JUMP)
            {
                this->setState(JUMP_LEFT);
            }

            break;
        }
        case WALK_RIGHT:
        {
            if (order == MOVE_LEFT)
            {
                this->setState(WALK_LEFT);
            }
            if (order == STOP_RIGHT)
            {
                this->setState(LOOK_RIGHT);
            }
            if (order == JUMP)
            {
                this->setState(JUMP_RIGHT);
            }

            break;
        }
    break;
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
    if (this->state == FALL_LEFT)  name = "fallLeft";
    if (this->state == FALL_RIGHT) name = "fallRight";
    if (this->state == HITLER_CAPUT) name = "mostPainfulDeath";

    setAnim(name);

    if (state == JUMP_LEFT || state == JUMP_RIGHT)
    {
        b2Body * body = this->phys.getpHbody();
        body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -10));
    }
}

int Unit::getState()
{
    return this->state;
}

void Unit::doPhysics(float scale)
{
    b2Body * body = this->phys.getpHbody();

    if (body->GetLinearVelocity().y > 5)
    {
        if (this->state == JUMP_LEFT || this->state == WALK_LEFT || this->state == LOOK_LEFT)
            this->setState(FALL_LEFT);
        if (this->state == JUMP_RIGHT || this->state == WALK_RIGHT || this->state == LOOK_RIGHT)
            this->setState(FALL_RIGHT);
    }

    switch (this->state)
    {
    case WALK_LEFT:
    {
        body->SetLinearVelocity(b2Vec2(-4, body->GetLinearVelocity().y));
        break;
    }
    case WALK_RIGHT:
    {
        body->SetLinearVelocity(b2Vec2(4, body->GetLinearVelocity().y));
        break;
    }
    case FALL_LEFT:
    {
        if (body->GetLinearVelocity().y == 0)
            this->setState(LOOK_LEFT);
        break;
    }
    case FALL_RIGHT:
    {
        if (body->GetLinearVelocity().y == 0)
            this->setState(LOOK_RIGHT);
        break;
    }

        break;
    }

    float newX = phys.getpHbody()->GetPosition().x * scale;
    float newY = phys.getpHbody()->GetPosition().y * scale;
    this->setXY(newX, newY);
}
