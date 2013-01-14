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
        if (event->Key.Code == sf::Key::Escape) emit end();
        if (event->Key.Code == sf::Key::W) emit setEntControl(6);
        if (event->Key.Code == sf::Key::A) emit setEntControl(2);
        if (event->Key.Code == sf::Key::D) emit setEntControl(3);

        emit moveCamera(up, down, left, right);
        break;
    }
    case sf::Event::KeyReleased:
    {
        if (event->Key.Code == sf::Key::A) emit setEntControl(0);
        if (event->Key.Code == sf::Key::D) emit setEntControl(1);

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
