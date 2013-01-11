#ifndef APP_H
#define APP_H

#include <QObject>
#include <QDebug>
#include "entity.h"
#include "resources.h"
//#include "e_enemy.h"
//#include "e_tower.h"
//#include "e_ground.h"
#include "map.h"
//#include "camera.h"
//#include "control.h"
#include <QFile>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class App : public QObject{
private:
    sf::RenderWindow *screen;
    sf::View *camera;

    Resources<sf::Image> * _images;
    Resources<sf::Sprite> * _sprites;
    Resources<Entity>     * _entities;
    Resources<Animation>  * _anims;
    Resources<Map>        * _maps;
    Resources<sf::View>     * _cameras;
//    Resources<sf::Text>       * _texts;
    //Control control;

public:
    App();
    int Execute();

    bool Init();
    void Event(sf::Event *event);
    void Loop();
    void Render();
    void Cleanup();

//    void readMap(QString path);

public slots:
    void setValue(int value);
};

#endif // APP_H
