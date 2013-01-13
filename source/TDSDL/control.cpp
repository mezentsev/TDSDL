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
    bool left   = (event->Key.Code==sf::Key::Left)?true:false;
    bool right  = (event->Key.Code==sf::Key::Right)?true:false;
    bool up     = (event->Key.Code==sf::Key::Up)?true:false;
    bool down   = (event->Key.Code==sf::Key::Down)?true:false;

    switch (event->Type)
    {
    case sf::Event::Closed:
    {
        end();
        break;
    }
    case sf::Event::KeyPressed:
    {
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
