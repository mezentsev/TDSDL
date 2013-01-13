#include "control.h"

Control::Control()
{
}

Control::~Control()
{
}

void Control::doControl(sf::Event *event)
{
    switch (event->Type)
    {
    case sf::Event::Closed:
    {
        end();
        break;
    }
    case sf::Event::KeyPressed:
    {
        switch (event->Key.Code)
        {
        case sf::Key::Escape:
        {
            end();
            break;
        }
        case sf::Key::Right:
        {
            moveCamera(false,false,false,true);
            break;
        }
        case sf::Key::Left:
        {
            moveCamera(false,false,true,false);
            break;
        }
        case sf::Key::Down:
        {
            moveCamera(false,true,false,false);
            break;
        }
        case sf::Key::Up:
        {
            moveCamera(true,false,false,false);
            break;
        }
        case sf::Key::A:
        {
            moveEntity(false,false,true,false);
            break;
        }
        case sf::Key::D:
        {
            moveEntity(false,false,false,true);
            break;
        }
        }
        break;
    }
    case sf::Event::KeyReleased:
    {
        switch (event->Key.Code)
        {
        case sf::Key::Right:
        {
            moveCamera(false,false,false,true);
            break;
        }
        case sf::Key::Left:
        {
            moveCamera(false,false,true,false);
            break;
        }
        case sf::Key::Down:
        {
            moveCamera(false,true,false,false);
            break;
        }
        case sf::Key::Up:
        {
            moveCamera(true,false,false,false);
            break;
        }
        case sf::Key::A:
        {
            moveEntity(false,false,true,false);
            break;
        }
        case sf::Key::D:
        {
            moveEntity(false,false,false,true);
            break;
        }
        }
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
