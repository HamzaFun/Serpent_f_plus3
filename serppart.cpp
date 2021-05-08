#include "serppart.h"
#include "fruit.h"
#include "jeu.h"
#include "murpart.h"
#include <QList>
#include <QDebug>
#include <QMediaPlayer>

extern Jeu* jeu;

QString SerpPart::image = "1";

SerpPart::SerpPart(QGraphicsItem* parent):QGraphicsPixmapItem(parent)
, pas(40)
{
    setZValue(1);
}

SerpPart *SerpPart::Preced()
{
    return preced;
}

void SerpPart::setPreced(SerpPart *valeur)
{
    preced = valeur;
}

SerpPart *SerpPart::Suiv()
{
    return suiv;
}

void SerpPart::setSuiv(SerpPart *valeur)
{
    suiv = valeur;
}

QString SerpPart::Direction()
{
    return direction;
}

void SerpPart::setDirection(QString valeur)
{
    direction = valeur;
}

void SerpPart::move()
{
    static int premier;
    if(direction == "DOWN"){
        this->setY(this->y()+pas);
    } else if(direction == "UP")
        this->setY(this->y()-pas);
    else if(direction == "LEFT")
        this->setX(this->x()- pas);
    else if(direction == "RIGHT")
        this->setX(this->x()+pas);
    if(premier){
        if(this->y() >= 600){
            this->setY(0);
        }
        else if(this->y() < 0){
            this->setY(600);
        }
        else if(this->x() < 0){
            this->setX(1200);
        }
        else if(this->x() >= 1200){
            this->setX(0);
        }
    }
    premier++;
    if(this->Suiv()!= NULL)
        direction = this->Suiv()->direction;
    setImage();
    if(part == "HEAD")
        checkCollidingObject();
}

void SerpPart::ajouterDerrier()
{
    int x,y;
    x=y=0;
    if(this->Suiv()->Direction() == "UP"){
        x = this->Suiv()->x();
        y = this->Suiv()->y()+ 40;
    }
    else if(this->Suiv()->Direction() == "DOWN"){
        x = this->Suiv()->x();
        y = this->Suiv()->y()- 40;
    }
    else if(this->Suiv()->Direction() == "RIGHT"){
        x = this->Suiv()->x()- 40;
        y = this->Suiv()->y();
    }
    else if(this->Suiv()->Direction() == "LEFT"){
        x = this->Suiv()->x()+ 40;
        y = this->Suiv()->y();
    }
    setPos(x,y);
}

void SerpPart::checkCollidingObject()
{
    QList <QGraphicsItem* > coll = this->collidingItems();

//
    for(int i = 0, n = coll.length(); i< n; ++i){
        Fruit* f = dynamic_cast<Fruit *>(coll[i]);
        if(f) {
            QPointF thisCenter(x()+10,y()+10);
            QPointF foodCenter(f->x()+10,f->y()+10);
            QLineF ln(thisCenter,foodCenter);
            if(ln.length() == 0){

                jeu->serp->ajoutePart(); 
                jeu->sceneDeJeu->removeItem(f);
                jeu->score->setScore(jeu->score->getScore()+ f->score);
                delete f;
                if(jeu->score->getScore() == l){
                    emit jeu->sfx->trigger(jeu->sfx->coin_2);
                    emit mangerF();
                    l += 5;
                }else{
                    emit jeu->sfx->trigger(jeu->sfx->coin_1);
                    emit manger();
                }
                if(jeu->obs != NULL){

                    if(jeu->obs->maxScore <= jeu->score->getScore()){
                        qDebug() << "next stage";
                        jeu->StageCourant++;
                        emit finStage();
                    }
                }
            }
        }
        else if(coll[i]) {
            if(typeid(*coll[i])== typeid(SerpPart) || typeid(*coll[i]) == typeid (MurPart))
            {
                emit jeu->sfx->trigger(jeu->sfx->selfCollid);
                jeu->finJeu();
            }
            return;

        }
    }
}

void SerpPart::setImage()
{
    QString path = ":/skins/"+ image;
    if(part == "HEAD"){

        if(direction == "UP"){
            path +=  "headup.png";
        }else if(direction == "DOWN"){
            path += "headDown.png";
        }else if(direction == "LEFT"){
            path += "headLeft.png";
        }else if(direction == "RIGHT"){
            setPixmap(QPixmap(QString(":/skins/%1head.png").arg(image)).scaled(40,40,Qt::KeepAspectRatio));
        }
        setZValue(2);

    }
    else if(part == "TAIL") {
        if(direction == "UP"){
            path += "tailUp.png";
        }else if(direction == "DOWN"){
            path += "tailDown.png";
        }else if(direction == "LEFT"){
            path += "tailLeft.png";
        }else if(direction == "RIGHT"){
            path += "tail.png";
        }
    }
    else if (part == "PART"){
        if(direction == this->Preced()->Direction()){
        if(direction == "LEFT" ||direction ==  "RIGHT")
            path += "left-right.png";
        else if (direction == "UP" || direction == "DOWN")
                path += "up-down.png";
        }
        else{
            if((direction == "UP" && this->Preced()->Direction() == "LEFT")
                    || (direction == "RIGHT" && this->Preced()->Direction() == "DOWN"))
                path += "leftUp-downRight.png";
            else if((direction == "UP" && this->Preced()->Direction() == "RIGHT")
                    || (direction == "LEFT" && this->Preced()->Direction() == "DOWN"))
                    path += "rightUp-downLeft.png";
            else if((direction == "LEFT" && this->Preced()->Direction() == "UP")
                    || (direction == "DOWN" && this->Preced()->Direction() == "RIGHT"))
                    path += "upLeft-rightDown.png";
            else
                path += "upRight-leftDown.png";

        }

    }
    if(path != ":/skins/"+ image){
        setPixmap(QPixmap(path).scaled(40,40));
    }
}

void SerpPart::setImage(QString valeur)
{
    image = valeur;
}

















