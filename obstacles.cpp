#include "murpart.h"
#include "obstacles.h"

Obstacles::Obstacles(int Num,QGraphicsItem* parent):QGraphicsRectItem(parent)
{
    ObsCourant = Num;
    switch(Num){
    case 1:
        crearObs1();
        maxScore = 2;
        break;
    case 2:
        crearObs2();
        maxScore = 3;
        break;
    case 3:
        crearObs3();
        maxScore = 4;
        break;
    case 4:
        crearObs4();
        maxScore = 4;
        break;
    case 5:
        crearObs5();
        maxScore = 4;
        break;
    case 6:
        crearObs6();
        maxScore = 4;
        break;
    case 7:
        crearObs7();
        maxScore = 4;
        break;
//    case 8:
//        crearObs8();
//        maxScore = 4;
//        break;
//    case 9:
//        crearObs9();
//        maxScore = 4;
//        break;
//    case 10:
//        crearObs10();
//        maxScore = 4;
//        break;
    default:
        break;
    }

}

void Obstacles::ajouterMurPart(int x, int y, int scale)
{
    if(scale == 0) scale = 40;
    MurPart* part = new MurPart(NULL, scale, this);
    part->setOpacity(0.5);
    part->setPos(x,y);
}

void Obstacles::crearObs1()
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

void Obstacles::crearObs2()
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

void Obstacles::crearObs3()
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

void Obstacles::crearObs4()
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

void Obstacles::crearObs5()
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

void Obstacles::crearObs6()
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

void Obstacles::crearObs7()
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
