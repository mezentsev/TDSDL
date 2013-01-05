#ifndef RESOURCES_H
#define RESOURCES_H

#include <QMap>
#include <QString>
#include "sprite.h"

template <typename T>
class Resources
{
private:
    QMap<QString, T*> map;
    int id;
public:
    Resources()
    {
        this->id = 1;
    }

    Resources(T* res, QString name)
    {
        this->map[name] = res;
        this->id = 1;
    }

    ~Resources()
    {
        qDeleteAll(this->map.begin(), this->map.end());
        this->map.clear();
    }

    // Добавить адрес ресурса и связать с именем. Если есть, то вернуть false
    bool add(T* res, QString name)
    {
        if (!this->map.contains(name))
        {
            this->map[name] = res;
            return true;
        }
        return false;
    }

    // Получить id по имени ресурса
    int getResId(QString name)
    {
        if (this->map.contains(name))
            return this->id;
        return -1;
    }

    // Получить ресурс по имени или сказать, что его нет
    T* getRes(QString name)
    {
        if (this->map.contains(name))
            return this->map[name];
        return NULL;
    }

    // Удалить ресурс или вернуть false
    bool remRes(QString name)
    {
        if (this->map.contains(name))
        {
            delete this->map[name];
            this->map.remove(name);
            return true;
        }
        return false;
    }
};
#endif // RESOURCES_H
