#include "fruit.h"
#include "jeu.h"

#include <QPixmap>
Fruit::Fruit(QString name,QGraphicsItem* parent):QGraphicsPixmapItem(parent)
{
    if(name == "POMME"){
        setPixmap(QPixmap(":/rand/food.png").scaled(40,40));
        score = 1;

    }
    else{
        setPixmap(QPixmap(":/rand/food2.png").scaled(40,40,Qt::KeepAspectRatio));
        score = 2;
    }
}



