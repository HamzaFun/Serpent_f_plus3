#ifndef BACKMUSIC_H
#define BACKMUSIC_H

#include <QMediaPlayer>
#include "music.h"

class BackMusic : public QObject
{
public:
    BackMusic(QObject* parent=0);

    Music* jeu_music;
    Music* menu_music;
    Music* findejeu_music;
    void stopAll();
};

#endif // BACKMUSIC_H
