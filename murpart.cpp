#include "murpart.h"

MurPart::MurPart(QString mur, int scale, QGraphicsItem* parent):QGraphicsPixmapItem(parent)
{
    murtype = "mur.png";
    if(mur != NULL)
        murtype = mur;

    setPixmap(QPixmap(":/rand/"+murtype).scaled(scale,scale));
    setPos(0,0);
    setZValue(5);
}
