#include "murpart.h"
#include "obstacles.h"

Obstacles::Obstacles(int Num,QGraphicsItem* parent):QGraphicsRectItem(parent)
{
    ObsCourant = Num;
    switch(Num){
    case 1:
        creerObs1();
        maxScore = 2;
        break;
    case 2:
        creerObs2();
        maxScore = 2;
        break;
    case 3:
        creerObs3();
        maxScore = 2;
        break;
    case 4:
        creerObs4();
        maxScore = 2;
        break;
    case 5:
        creerObs5();
        maxScore = 2;
        break;
    case 6:
        creerObs6();
        maxScore = 2;
        break;
    case 7:
        creerObs7();
        maxScore = 2;
        break;
    case 8:
        creerObs8();
        maxScore = 2;
        break;
    default:
        break;
    }

}

void Obstacles::ajouterMurPart(int x, int y, int scale)
{
    if(scale == 0) scale = 40;
    MurPart* part = new MurPart(NULL, scale, this);
    part->setOpacity(0);
    part->setPos(x,y);
}

void Obstacles::creerObs1()
{
    int scale = 80;
    bg = ":/bg/back1.png";
    int s=80;
    s=0;
    for(int i =0; i < 8; ++i){
        ajouterMurPart(0,   s, scale);
        ajouterMurPart(1120, s, scale);
        s+=80;
    }
}

void Obstacles::creerObs2()
{
    int scale = 80;
    bg = ":/bg/back2.png";
    int s=0;
    for(int i =0; i < 15; ++i){
        if(i < 6 || i > 8)
            ajouterMurPart(s,0, scale);
        s+=80;
    }
    s=80;
    for(int i =0; i < 4; ++i){
        ajouterMurPart(0,s, scale);
        ajouterMurPart(1120,s, scale);
        s+=80;
    }

}

void Obstacles::creerObs3()
{
    int scale = 80;
    bg = ":/bg/back3.png";
    int s=0;
    for(int i=0; i < 8; ++i){
        ajouterMurPart(400,s, scale);
        s +=80;
    }
    s=0;
    for(int i=0; i < 4; ++i){
        ajouterMurPart(800,s, scale);
        s +=80;
    }
    s=800;
    for(int i=0; i < 5; ++i){
        ajouterMurPart(s,320, scale);
        s +=80;
    }
}

void Obstacles::creerObs4()
{
    int scale = 80;
    bg = ":/bg/back4.png";
    int s=0;
    for(int i = 0; i < 5; ++i){
        ajouterMurPart(560,s, scale);
        s+=80;
    }
    s=0;
    for(int i = 0; i < 8; ++i){
        ajouterMurPart(0,s, scale);
        ajouterMurPart(1120,s, scale);
        s+=80;
    }
    s=560;
    for(int i = 0; i < 5; ++i){
        ajouterMurPart(s,320, scale);
        s+=80;
    }
    s=0;
    for(int i = 0; i < 3; ++i){
        ajouterMurPart(880,s, scale);
        s+=80;
    }
}

void Obstacles::creerObs5()
{
    int scale = 80;
    bg = ":/bg/back5.png";
    int s=0;
    for(int i =0; i < 8; ++i){
        ajouterMurPart(0,s, scale);
        s+=80;
    }
    s=0;
    for(int i =0; i < 9; ++i){
        ajouterMurPart(s,240, scale);
        s+=80;
    }
    s=80*7;
    for(int i =0; i < 9; ++i){
        ajouterMurPart(s,0, scale);
        ajouterMurPart(s,520, scale);
        s+=80;
    }
}

void Obstacles::creerObs6()
{
    int scale = 80;
    bg = ":/bg/back6.png";
    int s=0;

    for(int i =0; i < 6; ++i){
        ajouterMurPart(480,s+160, scale);
        ajouterMurPart(0,s+80, scale);
        ajouterMurPart(960,s, scale);
        ajouterMurPart(720,s, scale);
        ajouterMurPart(240,s, scale);
        s+=80;
    }
    ajouterMurPart(720,440, scale);
    ajouterMurPart(240,440, scale);
    ajouterMurPart(240,520, scale);
    ajouterMurPart(0,520, scale);
}

void Obstacles::creerObs7()
{
    int scale = 80;
    bg = ":/bg/back7.png";
    int s=0;
    for(int i = 0; i < 3; i++){
        ajouterMurPart(s,0, scale);
        ajouterMurPart(960+s,0, scale);
        ajouterMurPart(s,520, scale);
        ajouterMurPart(960+s,520, scale);
        s+=80;
    }
    s=0;
    for(int i =0; i < 8; ++i){
        ajouterMurPart(560, s, scale);
        s+=80;
    }
    s=0;
    for(int i =0; i < 15; ++i){
        ajouterMurPart(s,  240, scale);
        s+=80;
    }
}
void Obstacles::creerObs8()
{
    int scale = 80;
    bg = ":/bg/back8.png";
    int s=0;
    for(int i =0; i < 15; ++i){
        ajouterMurPart(s,0, scale);
        ajouterMurPart(s,520, scale);
        s+=80;
    }
    s=240;
    for(int i =0; i < 12; ++i){
        ajouterMurPart(s,160, scale);
        ajouterMurPart(s-240,400, scale);
        s+=80;
    }
    ajouterMurPart(s-240,400, scale);
}
