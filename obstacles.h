#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <QGraphicsRectItem>

class Obstacles : public QGraphicsRectItem
{
public:
    Obstacles(int Num,QGraphicsItem* parent=0);
    void ajouterMurPart(int x,int y, int scale);
    QString type;
    int ObsCourant;
    int maxScore;
    QString bg;
private:
    void crearObs1();
    void crearObs2();
    void crearObs3();
    void crearObs4();
    void crearObs5();
    void crearObs6();
    void crearObs7();
//    void crearObs8();
//    void crearObs9();
//    void crearObs10();

};

#endif // OBSTACLES_H
