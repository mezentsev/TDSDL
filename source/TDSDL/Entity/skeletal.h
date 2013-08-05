#ifndef SKELETAL_H
#define SKELETAL_H

#include "skeletal/SCML_SFML.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include <QString>
#include <QList>
#include <QMap>
#include <QDebug>

class Skeletal
{
private:
    QString path;
    SCML_SFML::FileSystem fs;
    SCML::Data * data;
    float x, y, angle, scale;
    sf::RenderTexture * screen;

    QList< SCML_SFML::Entity * > entities;

    void load(SCML::Data);
public:
    Skeletal(QString path, float x, float y, float angle = 0.0f, float scale = 1.0f, float sizex = 500.f, float sizey = 500.0f);
    Skeletal(Skeletal * skeletal);
    ~Skeletal();
    sf::RenderTexture * animate(sf::Time);
    sf::Vector2u getSize();
    void setXY(float, float);
};

#endif // SKELETAL_H
