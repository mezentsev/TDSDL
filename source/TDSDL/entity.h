#ifndef ENTITY_H
#define ENTITY_H

#include "resources.h"
#include "animation.h"
#include <SFML/Graphics.hpp>
#include <QMap>
#include <typeinfo>
#include <QObject>

class Entity : public QObject
{
    Q_OBJECT

private:
    struct Moving
    {
        bool left, right, up, down;
    };

    Moving moving;
    float speed;

    sf::Sprite *sprite;
    QMap<QString, Animation*> anim;
    float x,y;
    int state;  //Состояние объекта (возможно enum)
    sf::IntRect rect; //спрайт
    int w,h;
    QString animName;

    double _angle;
    double _scale;

public:
   // Entity(sf::Sprite* sprite, int x, int y, int w, int h, int state);
    Entity();
    ~Entity();

    //Entity * setSprite(sf::Sprite* sprite);
    Entity * setXY(float x, float y);
    Entity * setHW(int h, int w);
    float getX();
    float getY();
    int getW();
    int getH();
    int getState();
    Entity * setAngle(double angle);
    Entity * setScale(double s);

    void refresh(sf::RenderWindow *screen);
    void move(float freq);

    bool addAnim(Animation * anim, QString name); //Привязывает анимацию с именем
    Entity * setAnim(QString name); // Устанавливает анимацию с именем name
    sf::Sprite * animate(sf::RenderWindow *screen); //Проигрывает анимацию с именем this->animName

    virtual const char* get_name(){return typeid(*this).name();}

public slots:
    void setState(int state);
    void setMoving(bool up, bool down, bool left, bool right);
};

#endif // ENTITY_H
