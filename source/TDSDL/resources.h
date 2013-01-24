#ifndef RESOURCES_H
#define RESOURCES_H

#include <QMap>
#include <QString>

template <typename T>
class Resources
{
private:
    QMap<QString, T*> map;
public:
    Resources()
    {
    }

    Resources(T* res, QString name)
    {
        this->map[name] = res;
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

    int size()
    {
        return this->map.size();
    }

    typename QMap<QString, T*>::iterator getBegin()
    {
        return this->map.begin();
    }

    typename QMap<QString, T*>::iterator getEnd()
    {
        return this->map.end();
    }
};

#endif // RESOURCES_H
