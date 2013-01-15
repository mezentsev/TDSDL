#include "control.h"
#include <QDebug>

Control::Control()
{
}

Control::~Control()
{
}

void Control::doControl(sf::Event *event)
{
    bool left   = (event->key.code==sf::Keyboard::Left)?true:false;
    bool right  = (event->key.code==sf::Keyboard::Right)?true:false;
    bool up     = (event->key.code==sf::Keyboard::Up)?true:false;
    bool down   = (event->key.code==sf::Keyboard::Down)?true:false;

    switch (event->type)
    {
    case sf::Event::Closed:
    {
        end();
        break;
    }
    case sf::Event::KeyPressed:
    {
        if (event->key.code == sf::Keyboard::Escape) emit end();
        if (event->key.code == sf::Keyboard::W) emit setEntControl(6);
        if (event->key.code == sf::Keyboard::A) emit setEntControl(2);
        if (event->key.code == sf::Keyboard::D) emit setEntControl(3);

        emit moveCamera(up, down, left, right);
        break;
    }
    case sf::Event::KeyReleased:
    {
        if (event->key.code == sf::Keyboard::A) emit setEntControl(0);
        if (event->key.code == sf::Keyboard::D) emit setEntControl(1);

        emit moveCamera(up, down, left, right);
        break;
    }
    case sf::Event::MouseWheelMoved:
    {
        break;
    }
    case sf::Event::MouseMoved:
    {
        break;
    }
    case sf::Event::MouseButtonPressed:
    {
        break;
    }
    case sf::Event::MouseButtonReleased:
    {
        break;
    }
    }
}
