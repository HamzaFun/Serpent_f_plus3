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
    QMediaPlayer* click_2;
    QMediaPlayer* hover_1;
    QMediaPlayer* win_1;
    QMediaPlayer* win_2;
    QMediaPlayer* selfCollid;

private slots:
    void playMedia(QMediaPlayer* media);
signals:
    void trigger(QMediaPlayer*);
};

#endif // SOUNDEFFECTS_H
