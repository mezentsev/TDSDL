#ifndef SOUND_H
#define SOUND_H

#include <QString>

class Sound
{
private:
    int volume;
    bool pause;
    QString path;
    Sound * next; //Следующий трэк
    Sound * prev; //Предыдущий трэк
public:
    Sound(QString path, int vol);
    ~Sound();

    bool play();
    bool stop();
    bool setVol(int vol);
};

#endif // SOUND_H
