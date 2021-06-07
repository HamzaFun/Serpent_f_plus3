#include "animerserpent.h"
#include "fruit.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QTimer>
#include <QThread>
#include <qevent.h>
#include "jeu.h"
#include "murpart.h"

extern Jeu* jeu;

AnimerSerpent::AnimerSerpent(QGraphicsItem* parent):QGraphicsRectItem(parent)
{
    serpTete = new SerpPart(this);
    serpTete->setSuiv(NULL);
    serpTete->setPreced(NULL);
    serpTete->setPos(200,200);
    serpTete->setDirection("RIGHT");
    serpTete->part = "HEAD";
    serpTete->setImage();
    serpTete->setImage(jeu->peau);
    serpQueue = serpTete;
    connect(serpTete, SIGNAL(finStage()), jeu, SLOT(afficherNext()));
    connect(serpTete, SIGNAL(gagnerJeu()), jeu, SLOT(afficherGagner()));
    t = new QTimer();
    connect(t, SIGNAL(timeout()), this, SLOT(move()));
    for(int i=0;i< 20;++i){
    ajouterFruit();
}


    connect( serpTete, SIGNAL(manger()), this, SLOT(ajouterFruit()));
    connect( serpTete, SIGNAL(mangerF()), this, SLOT(ajouterFruit2()));




    direction = "RIGHT";

    ajouterPart();
    ajouterPart();
    ajouterPart();

    text = new QGraphicsTextItem(this);
    text->setVisible(true);
    text->setDefaultTextColor(Qt::white);
    text->setPlainText("Puiez sur Espace pour continue");
    text->setPos(650,250);
    text->setFont(QFont("",14));

    setZValue(1);
}

void AnimerSerpent::keyPressEvent(QKeyEvent *event)
{
    if((event->key() == Qt::Key_Down || event->key() == Qt::Key_S ) && serpTete->Direction() != "UP") {
        direction = "DOWN";
    }
    else if(( event->key() == Qt::Key_Up || event->key() == Qt::Key_W ) && serpTete->Direction()  != "DOWN") {
        direction = "UP";
    }
    else if(( event->key() == Qt::Key_Right || event->key() == Qt::Key_D ) && serpTete->Direction()  != "LEFT") {
            direction = "RIGHT";

    }
    else if((event->key() == Qt::Key_Left || event->key() == Qt::Key_A ) && serpTete->Direction()  != "RIGHT" ) {
            direction = "LEFT";
    }
    else if(event->key() == Qt::Key_Space){
        if(t->isActive() ){
            t->stop();
            text->setVisible(true);
        }
        else{
            t->start(90);
            text->setVisible(false);
        }

    }
    else if( event->key() == Qt::Key_Escape && jeu->finPage->opacity() == 0 && jeu->nextStgPage->opacity() == 0){
        if(t->isActive()){
            t->stop();
        }
        if(jeu->pausePage->opacity() == 0 )
            jeu->afficherPause();
        else{
            if(jeu->pausePage != NULL)
            {
                jeu->pausePage->fadeOut();
                jeu->suprimerItem(jeu->pausePage);
            }
        }
    }
}

void AnimerSerpent::ajouterPart()
{
    SerpPart* part = new SerpPart(this);
    SerpPart* temp = serpTete;

    while(temp->Preced() != NULL){
        temp = temp->Preced();
    }
    temp->setPreced(part);
    part->setSuiv(temp);
    part->setPreced(NULL);
    part->ajouterDerrier();
    part->setDirection(temp->Direction());
    serpQueue = part;
    part->part = "TAIL";
    if(temp != serpTete)
        temp->part = "PART";
    part->setImage();
    temp->setImage();
}

void AnimerSerpent::animer()
{
    SerpPart* temp = serpQueue;

    while(temp != NULL){
        temp->move();
        temp = temp->Suiv();
    }
}

void AnimerSerpent::move()
{
    serpTete->setDirection(direction);
    animer();
}

void AnimerSerpent::ajouterFruit()
{
    Fruit* f1 = new Fruit("POMME", this);
    int x ;
    int y ;
//    int rand;
    int k=1;
    while(k != 0){
        k=0;
//    rand  = QRandomGenerator::global()->bounded(2);
    QList <QGraphicsItem* > coll = jeu->sceneDeJeu->items();
    x = QRandomGenerator::global()->bounded(30) *40 ;
    y = QRandomGenerator::global()->bounded(15) *40 ;

    for(int i=0; i < coll.length(); ++i){
        MurPart* m = dynamic_cast<MurPart *>(coll[i]);
        if(m)
        if((m->pos().x() == x && m->pos().y() == y) || (m->pos().x()+40 == x && m->pos().y()+40 == y) || (m->pos().x() == x && m->pos().y()+40 == y) || (m->pos().x()+40 == x && m->pos().y() == y)  ) {
            k++;
            break;
        }
    }
    }

//    if(rand >= 1 && x < 1160 && y < 560 ){
//        f1->setX(x+40);
//        f1->setY(y+40);
//    }else{
        f1->setX(x);
        f1->setY(y);
//    }

}

void AnimerSerpent::ajouterFruit2()
{
    Fruit* f1 = new Fruit("", this);
    int x ;
    int y ;
    int k=1;
    while(k != 0){
        k=0;

    QList <QGraphicsItem* > coll = jeu->sceneDeJeu->items();
    x = QRandomGenerator::global()->bounded(29) *40 ;
    y = QRandomGenerator::global()->bounded(14) *40 ;

    for(int i=0; i < coll.length(); ++i){
        if(coll[i]->pos().x() == x && coll[i]->pos().y() == y ) {
            k++;
            break;
        }
    }
    }
    f1->setX(x);
    f1->setY(y);
}




