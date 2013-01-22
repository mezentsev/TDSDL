#include "unit.h"

#include <QDebug>

Unit::Unit(Animation *default_anim, int x, int y, int w, int h, b2World * world, Physics::B2_BODY_TYPE type, float SCALE) : Entity(default_anim,x,y,w,h,world,type,SCALE)
{
    this->setState(LOOK_RIGHT);
}

void Unit::setControl(int state)
{
    STATE st = STATE(state);
    switch(this->state){
        case LOOK_LEFT:
        {
            if (st == WALK_LEFT || st == WALK_RIGHT || st == JUMP)
            {
                this->setState(st);
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

            break;
        }
        case LOOK_RIGHT:
        {
            if (st == WALK_LEFT || st == WALK_RIGHT || st == JUMP)
            {
                this->setState(st);
            }

            break;
        }
        case WALK_LEFT:
        {
            b2Body * body = this->phys.getpHbody();
            float impulse = -(20.0f + body->GetLinearVelocity().x);
            body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter());

            if (st == LOOK_LEFT || st == WALK_RIGHT)
            {
                this->setState(st);
            }

            if (st == JUMP)
            {
                this->setState(JUMP_LEFT);
                b2Body * body = this->phys.getpHbody();
                float impulse = -(350.0f + body->GetLinearVelocity().y);
                body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter());
            }

            break;
        }
        case WALK_RIGHT:
        {
            b2Body * body = this->phys.getpHbody();
            float impulse = (20.0f - body->GetLinearVelocity().x);
            body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter());

            if (st == LOOK_RIGHT || st == WALK_LEFT)
            {
                this->setState(st);
            }

            if (st == JUMP)
            {
                this->setState(JUMP_RIGHT);
                b2Body * body = this->phys.getpHbody();
                float impulse = -(350.0f + body->GetLinearVelocity().y);
                body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter());
            }

            break;
        }
        case JUMP:
        {

            break;
        }
    break;
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
