#ifndef ANIMERSERPENT_H
#define ANIMERSERPENT_H

#include "serppart.h"
#include <QGraphicsRectItem>
#include <QObject>
#include <QMediaPlayer>

class AnimerSerpent :public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    AnimerSerpent(QGraphicsItem* prent=0);
    void keyPressEvent(QKeyEvent *event);
    void ajouterPart();
    void animer();
    QTimer* t;
    SerpPart* serpTete;

public slots:
    void move();
    void ajouterFruit();
    void ajouterFruit2();

private:
    SerpPart* serpQueue;
    QString direction;
    QGraphicsTextItem* text;

};

#endif // ANIMERSERPENT_H
