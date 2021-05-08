#ifndef SOUNDEFFECTS_H
#define SOUNDEFFECTS_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class SoundEffects : public QObject
{
    Q_OBJECT
public:
    explicit SoundEffects(QObject *parent = nullptr);

    QString dir;
    QMediaPlayer* coin_1;
    QMediaPlayer* coin_2;
    QMediaPlayer* click_1;
    QMediaPlayer* selfCollid;

private slots:
    void playMedia(QMediaPlayer* media);
    void coin1s();
    void coin2s();
signals:
    void trigger(QMediaPlayer*);
    void coin1(QMediaPlayer*); void coin2(QMediaPlayer*); void click1(QMediaPlayer*);
    void coin1(); void coin2(); void click1();
};

#endif // SOUNDEFFECTS_H
