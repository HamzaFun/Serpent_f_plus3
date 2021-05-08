#include "soundeffects.h"

SoundEffects::SoundEffects(QObject *parent) : QObject(parent)
, dir("qrc:/Sounds/sfx/")
{
    coin_1 = new QMediaPlayer();
    coin_1->setMedia(QUrl(dir+"coin.wav"));
    coin_2 = new QMediaPlayer();
    coin_2->setMedia(QUrl(dir+"coin1.wav"));
    click_1 = new QMediaPlayer();
    click_1->setMedia(QUrl(dir+"coin1.wav"));
    selfCollid = new QMediaPlayer();
    selfCollid->setMedia(QUrl(dir+"lose1.wav"));

    connect(this, SIGNAL(trigger(QMediaPlayer*)), this, SLOT(playMedia(QMediaPlayer*)));
}

void SoundEffects::playMedia(QMediaPlayer *media)
{
    if (media->state() == QMediaPlayer::PlayingState) {
        media->setPosition(0);
    }else if (media->state() == QMediaPlayer::StoppedState)
    {
        media->play();
    }
}

void SoundEffects::coin1s()
{
    if (coin_1->state() == QMediaPlayer::PlayingState) {
        coin_1->setPosition(0);
    }else if (coin_1->state() == QMediaPlayer::StoppedState)
    {
        coin_1->play();
    }
}
void SoundEffects::coin2s()
{
    if (coin_2->state() == QMediaPlayer::PlayingState) {
        coin_2->setPosition(0);
    }else if (coin_2->state() == QMediaPlayer::StoppedState)
    {
        coin_2->play();
    }
}
