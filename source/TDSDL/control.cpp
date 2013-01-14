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
    bool esc    = (event->key.code==sf::Keyboard::Escape)?true:false;

    switch (event->type)
    {
    case sf::Event::Closed:
    {
        end();
        break;
    }
    case sf::Event::KeyPressed:
    {
        if (esc) end();
        emit moveCamera(up, down, left, right);
        break;
    }
    case sf::Event::KeyReleased:
    {
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
