#include "skeletal.h"

Skeletal::Skeletal(QString path, float x, float y, float angle, float scale, float sizex, float sizey):
    x(x), y(y), angle(angle), scale(scale)
{
    this->screen = new sf::RenderTexture();
    this->screen->create(sizex, sizey);
    this->path = path;
    this->data = new SCML::Data(path.toStdString());
    this->data->log();

    this->fs.load(data);
    printf("Loaded %zu images.\n", fs.images.size());

    for(std::map< int, SCML::Data::Entity * >::iterator e = data->entities.begin(); e != data->entities.end(); e++)
    {
        SCML_SFML::Entity * entity = new SCML_SFML::Entity(data, e->first);
        entity->setFileSystem(&fs);
        entity->setScreen(screen);
        entity->startAnimation(0);
        entities.push_back(entity);
    }

    printf("Loaded %zu entities.\n", entities.size());
    //this->screen->clear(sf::Color::Red);
}

Skeletal::Skeletal(Skeletal *skeletal)
{
    *this = *skeletal;
}

Skeletal::~Skeletal()
{
    for(QList< SCML_SFML::Entity * >::iterator e = this->entities.begin(); e != this->entities.end(); e++)
    {
        delete (*e);
    }

    this->entities.clear();
    fs.clear();
    data->clear();
    delete screen;
    delete data;
}

sf::RenderTexture * Skeletal::animate(sf::Time dt)
{
    this->screen->clear(sf::Color::Transparent);

    for(QList< SCML_SFML::Entity * >::iterator e = this->entities.begin(); e != this->entities.end(); e++)
    {
        (*e)->update(dt.asMilliseconds());
        (*e)->draw(x, y, angle, scale, scale);
    }

    this->screen->display();

    return screen;
}

sf::Vector2u Skeletal::getSize()
{
    return this->screen->getSize();
}

void Skeletal::setXY(float x, float y)
{
    this->x = x;
    this->y = y;
}
