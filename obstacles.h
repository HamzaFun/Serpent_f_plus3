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
    void creerObs1();
    void creerObs2();
    void creerObs3();
    void creerObs4();
    void creerObs5();
    void creerObs6();
    void creerObs7();
    void creerObs8();
//    void crearObs9();
//    void crearObs10();

};

#endif // OBSTACLES_H
