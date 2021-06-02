#include "backmusic.h"

BackMusic::BackMusic(QObject* parent):QObject(parent)
{
    jeu_music = new Music("ingame_music1.mp3", this);
    menu_music = new Music("menu_music2.mp3", this);
    findejeu_music = new Music("gameover_music.mp3");
}

void BackMusic::stopAll()
{
    jeu_music->stopMusic();
    findejeu_music->stopMusic();
    menu_music->stopMusic();
}
