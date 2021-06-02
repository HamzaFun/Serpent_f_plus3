#include "soundeffects.h"

SoundEffects::SoundEffects(QObject *parent) : QObject(parent)
, dir("qrc:/Sounds/sfx/")
{
    coin_1 = new QMediaPlayer();
    coin_1->setMedia(QUrl(dir+"coin.wav"));
    coin_2 = new QMediaPlayer();
    coin_2->setMedia(QUrl(dir+"coin1.wav"));
    click_1 = new QMediaPlayer();
    click_1->setMedia(QUrl(dir+"click1.wav"));
    click_2 = new QMediaPlayer();
    click_2->setMedia(QUrl(dir+"click7.wav"));
    hover_1 = new QMediaPlayer();
    hover_1->setMedia(QUrl(dir+"hover1.mp3"));
    win_1 = new QMediaPlayer();
    win_1->setMedia(QUrl(dir+"win1.wav"));
    win_2 = new QMediaPlayer();
    win_2->setMedia(QUrl(dir+"win1.wav"));
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
