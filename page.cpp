#include "jeu.h"
#include "page.h"

#include <QFont>
#include <QDebug>
#include <qpixmap.h>
#include <QGraphicsPixmapItem>
#include <QPixmap>

#include <bits/concept_check.h>
extern Jeu* jeu;

Page::Page(QString titre, QString font, Qt::GlobalColor couleur, QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    setOpacity(0);
    setX(-100);
    text = new QGraphicsTextItem(titre, this);
    QFont titreFont(font, 50 );
    text->setZValue(5);
    text->setFont(titreFont);
    text->setDefaultTextColor(couleur);
    int yPos = 0;

    text->setPos(40, yPos);
    setZValue(10);
    m_animation = creerAnimation("animationFactor", this, 0, 1, 600, QEasingCurve::Linear);
    m_positionAnimation = creerAnimation("positionFactor", this, 0, 1, 600, QEasingCurve::OutQuad);

    if(titre == "PAUSE" || titre == "FELICITATION" || titre == "WARNING" || titre == "Fin De Jeu" || titre == "INFORMATIONS"){
        text->setPos(550 - text->boundingRect().width()/2, yPos + text->boundingRect().height());
        transparencyBackground = new QGraphicsPixmapItem(this);
        transparencyBackground->setPos(this->mapFromScene(0,0));
        transparencyBackground->setZValue(0);
        transparencyBackground->setPixmap(QPixmap(":/bg/blackbg.jpg").scaled(1200,600));
        transparencyBackground->setOpacity(0.5);
    }
}

Page::Page(QString titre, QString font, QString fin, Qt::GlobalColor couleur, QGraphicsItem *parent)
{
    this->titre = titre;
    setOpacity(0);
    setX(-100);
    text = new QGraphicsTextItem(titre, this);
    QFont titreFont(font, 50 );
    text->setZValue(5);
    text->setFont(titreFont);
    text->setDefaultTextColor(couleur);
    int yPos = 600;
    text->setPos(550- text->boundingRect().width()/2, yPos);
    creerText("Merci d'avoir joué",550,yPos+80,font,40,Qt::red);
//    creerText("JEU ADVENTURE",550,yPos+2*80,font,40,couleur);
    creerText("CREER PAR :",550,yPos+2*80,font,40,couleur);
    creerText("Zakaria El Idrissi",550,yPos+3*80,font,30,Qt::white);
    creerText("Hamza El Filali",550,yPos+4*80,font,30,Qt::white);
    creerText("GERER PAR :",550,yPos+5*80,font,40,couleur);
    creerText("Mr. SABANE",550,yPos+6*80,font,40,Qt::white);
    creerText("() PUIEZ SUR ESPACE POUR PASSER ()",90,1200,font,20,Qt::white);
    setZValue(10);
    m_scrollAnimation = creerAnimation("scrollFactor", this, 0, 1, 10000, QEasingCurve::Linear);
    m_animation = creerAnimation("animationFactor", this, 0, 1, 600, QEasingCurve::Linear);
    m_positionAnimation = creerAnimation("positionFactor", this, 0, 1, 600, QEasingCurve::OutQuad);

    transparencyBackground = new QGraphicsPixmapItem(this);
    transparencyBackground->setPos(this->mapFromScene(0,0));
    transparencyBackground->setZValue(0);
    transparencyBackground->setPixmap(QPixmap(":/bg/blackbg.jpg").scaled(1200,600));
    transparencyBackground->setOpacity(0.5);
}

void Page::fadeOut()
{
        m_animation->setDirection(QAbstractAnimation::Backward);
        m_positionAnimation->setDirection(QAbstractAnimation::Backward);
        m_positionAnimation->start();
        m_animation->start();
}

void Page::fadeIn()
{
        m_animation->setDirection(QAbstractAnimation::Forward);
        m_positionAnimation->setDirection(QAbstractAnimation::Forward);
        m_positionAnimation->start();
        m_animation->start();
        if(m_scrollAnimation != NULL){
            qDebug() << "m_scroll animation";
            m_scrollAnimation->start();
        }

}

QPropertyAnimation *Page::creerAnimation(QByteArray propertyName, QObject *target, qreal startValeur, qreal finValeur, qreal duration, QEasingCurve easing)
{
    QPropertyAnimation* m_animation = new QPropertyAnimation(this);
    m_animation->setTargetObject(target);
    m_animation->setPropertyName(propertyName);
    m_animation->setStartValue(startValeur);
    m_animation->setEndValue(finValeur);
    m_animation->setDuration(duration);
    m_animation->setEasingCurve(easing);

    return m_animation;
}

void Page::setAnimationFactor(qreal fact)
{
    if(fact == m_animationFactor) return;
    m_animationFactor = fact;
    emit animationFactorChanged(fact);

    text->setOpacity(1* m_animation->currentValue().toReal());
    setOpacity(1* m_animation->currentValue().toReal());
}

qreal Page::animationFactor()
{
    return m_animationFactor;
}

void Page::setPositionFactor(qreal pfact)
{
    if(pfact == m_positionFactor) return ;
    m_positionFactor = pfact;
    emit positionFactorChanged(pfact);
    if(transparencyBackground != NULL)
        transparencyBackground->setX(this->mapFromScene(0,0).x());
    setX(-100+ 150* m_positionAnimation->currentValue().toReal());
}

qreal Page::positionFactor()
{
    return m_positionFactor;
}

void Page::setScrollFactor(qreal sfact)
{
    if(sfact == m_scrollFactor) return ;
    m_scrollFactor = sfact;
    emit positionFactorChanged(sfact);
    if(transparencyBackground != NULL){
        transparencyBackground->setX(this->mapFromScene(0,0).x());
        transparencyBackground->setY(this->mapFromScene(0,0).y());
    }
    setY(this->y()-1);
}

qreal Page::scrollFactor()
{
    return m_scrollFactor;
}

void Page::creerText(QString contenue, int x, int y, QFont font, int fontsize, QColor couleur)
{
    QGraphicsTextItem *txt = new QGraphicsTextItem(contenue, this);
    txt->setZValue(5);
    font.setPixelSize(fontsize);
    txt->setFont(font);
    txt->setDefaultTextColor(couleur);
    txt->setPos(x- txt->boundingRect().width()/2, y);
    Q_UNUSED(txt);
}

//void Page::setContent()
//{
//    if(titre == "JEU SERPENT"){
//        Button* stages = new Button("STAGES", 150,40,Button::Buttontype::menu, this);
//        int mxPos = debut_scene.x() ;
//        int myPos = 200;
//        stages->setPos(mxPos,myPos);
//        connect(stages, SIGNAL(clicked()), jeu, SLOT(afficherStages()));

//        Button* info = new Button("!", 40,40,Button::Buttontype::menu, this);
//        info->setPos(1100,10);
//        connect(info, SIGNAL(clicked()), jeu, SLOT(afficherInfo()));

//        Button* joue = creerBtn("JOUER", 150, 40,  mxPos + 40, myPos + 60, true, this);
//        Button* quit = creerBtn("QUIT", 150, 40,  mxPos + 80, myPos + 120, false, this);
//        Q_UNUSED(joue);
//        Q_UNUSED(quit);
//    }else if(titre == "STAGES"){
//        int x = 160 ;
//        int y = 100;
//        int h = 150;
//        Button* stage = creerStg("DEBUT", h, h, 175,y, 1, this);
//        Button* stage2 = creerStg("CHAMBRE", h, h, x +175 ,  y, 2, this);
//        Button* stage3 = creerStg("3", h, h, 2*x +175, y, 3, this);
//        Button* stage4 = creerStg("4", h, h, 3*x +175, y, 4, this);
//        Button* stage5 = creerStg("5", h, h, 4*x +175, y, 5, this);
//        Button* stage6 = creerStg("6", h, h, 175    ,3*y, 6, this);
//        Button* stage7 = creerStg("7", h, h, x+175  ,3*y, 7, this);
//        Button* stage8 = creerStg("8", h, h, 2*x+175,3*y, 8, this);

//        //bouton de routeur
//        Button* retour = new Button("<< RETOUR", 140, 50, Button::Buttontype::retour, this);
//        int rx = debut_scene.x();
//        int ry = debut_scene.y();
//        retour->setPos(rx,ry);
//        connect(retour, SIGNAL(clicked()), jeu, SLOT(retourMenu()));
//        Q_UNUSED(stage);
//        Q_UNUSED(stage2);
//        Q_UNUSED(stage3);
//        Q_UNUSED(stage4);
//        Q_UNUSED(stage5);
//        Q_UNUSED(stage6);
//        Q_UNUSED(stage7);
//        Q_UNUSED(stage8);
//    }else if(titre == "FELICITATION"){
//        int nx = millieu_scene.x() + 30 - debut_scene.x();
//        int ny = millieu_scene.y() - 20;
//        this->creerText("VOTRE SCORE :", nx-55, ny-60,font,35,Qt::yellow );
//        this->creerText(QString::number(jeu->score->getScore()), nx+95, ny-60,font,35,Qt::yellow );
//        Button* rejouer = creerBtn("REJOUER", 150, 40, millieu_scene.x() - 180 - debut_scene.x() , ny, true, this);
//        Button* next = new Button("NEXT", 150, 40, Button::Buttontype::menu, this);
//        next->setPos(nx,ny);
//        connect(next, SIGNAL(clicked(int)), jeu, SLOT(creerObs(int)));
//        Button* retour = new Button("RETOUR", 150, 40, Button::Buttontype::retour, this);
//        int rx = millieu_scene.x() - 75 - debut_scene.x();
//        int ry = debut_scene.y();
//        retour->setPos(rx,ry);
//        connect(retour, SIGNAL(clicked()), jeu, SLOT(retourMenu()));
//        Q_UNUSED(rejouer);
//    }else if(titre == "WARNING"){
//        Button* oui = new Button("OUI", 70, 70, Button::Buttontype::menu, this);
//        int rx = millieu_scene.x() - oui->boundingRect().width() - debut_scene.x() -30;
//        int ry = millieu_scene.y() - oui->boundingRect().width()/2;
//        oui->setPos(rx,ry);
//        connect(oui, SIGNAL(clicked()), jeu, SLOT(retourMenu()) );
//        Button* non = new Button("NON", 70, 70, Button::Buttontype::menu, this);
//        int nx = millieu_scene.x() + oui->boundingRect().width() - debut_scene.x() -20;
//        int ny = millieu_scene.y() - oui->boundingRect().width()/2;
//        non->setPos(nx,ny);
//        connect(non, SIGNAL(clicked()), jeu, SLOT(afficherPause()) );

//    }else if(titre == "PAUSE"){
//        Button* commancer = new Button("COMMANCER", 200, 40,Button::Buttontype::menu, this);
//        int x = millieu_scene.x() - commancer->boundingRect().width()/2 - debut_scene.x() ;
//        commancer->setPos(x, millieu_scene.y() - 20);
//        if(jeu->StageCourant < jeu->StageAttendue){
//            Button* next = new Button("NEXT", 150, 40, Button::Buttontype::menu, this);
//            next->setPos(millieu_scene.x() - debut_scene.x() - next->boundingRect().width()/2, millieu_scene.y() - 90);
//            connect(next, SIGNAL(clicked(int)), jeu, SLOT(creerObs(int)));
//        }
//        connect(commancer, SIGNAL(clicked()), jeu, SLOT(commancer()) );
//        Button* recommancer = creerBtn("RECOMMANCER", 200, 40, x , millieu_scene.y() + 60, true, this);

//        //bouton de routeur
//        Button* routeur = new Button("<< RETOUR", 160, 50, Button::Buttontype::retour, this);
//        int rx = millieu_scene.x() - routeur->boundingRect().width()/2 - debut_scene.x();
//        int ry = debut_scene.y();
//        routeur->setPos(rx,ry);
//        connect(routeur, SIGNAL(clicked()), jeu, SLOT(choix()) );
//        Q_UNUSED(recommancer);
//    }else if(titre == "Fin De Jeu"){
//        int rx = millieu_scene.x() - 75 - debut_scene.x();
//        if(jeu->topScore < jeu->score->getScore()) jeu->topScore = jeu->score->getScore();
//        this->creerText("TOP SCORE :", rx, millieu_scene.y() - 80,font,35,Qt::yellow );
//        this->creerText(QString::number(jeu->topScore), rx+150, millieu_scene.y() - 80,font,35,Qt::yellow );
//        Button* rejouer = creerBtn("REJOUER", 150, 40, rx , millieu_scene.y() - 20, true, this);
//        Button* quit = new Button("RETOUR", 150, 40, Button::Buttontype::retour, this);
//        int ry =  debut_scene.y();
//        quit->setPos(rx,ry);
//        connect(quit, SIGNAL(clicked()), jeu, SLOT(retourMenu()));
//        Q_UNUSED(rejouer);
//    }else if(titre == "Complete"){
//        int nx = millieu_scene.x() + 30 - debut_scene.x();
//        int ny = millieu_scene.y() - 20;
//        Button* rejouer = creerBtn("REJOUER", 150, 40, millieu_scene.x() - 180 - debut_scene.x() , ny, true, this);
//        Button* fin = new Button("FIN", 150, 40, Button::Buttontype::menu, this);
//        fin->setPos(nx,ny);
//        connect(fin, SIGNAL(clicked()), jeu, SLOT(afficherFinText()));
//        Button* retour = new Button("RETOUR", 150, 40, Button::Buttontype::retour, this);
//        int rx = millieu_scene.x() - 75 - debut_scene.x();
//        int ry = debut_scene.y();
//        retour->setPos(rx,ry);
//        connect(retour, SIGNAL(clicked()), jeu, SLOT(retourMenu()));
//        Q_UNUSED(rejouer);
//    }else if(titre == "INFORMATIONS"){
//        QGraphicsPixmapItem * commentjouer = new QGraphicsPixmapItem(QPixmap(":/bg/comment.png").scaled(1200,600), this);
//        commentjouer->setPos(-50,0);
//        this->text->setPos(0,0);
//        Button* retour = new Button("<< RETOUR", 140, 50, Button::Buttontype::retour, this);
//        int rx = 50;
//        int ry = debut_scene.y();
//        retour->setPos(rx,ry);
//        connect(retour, SIGNAL(clicked()), jeu, SLOT(retourMenu()));

//    }/*else if(titre == "SERPENT PRO"){

//    }*/

//}
//Button *Page::creerStg(QString text, int w, int h, int xpos, int ypos, int stg, Page *pere)
//{
//    Button* button;
//    button = new Button(text, w, h, stg, pere);
//    if(stg <= jeu->StageAttendue){
//        button->deletelock();
//    }
//    button->setHoverd();
//    connect(button, SIGNAL(clicked(int)),jeu,SLOT(creerObs(int)));

//    button->setPos( xpos, ypos);
//    return button;
//}
//Button *Page::creerBtn(QString text, int w, int h, int xpos, int ypos, bool debut, Page *pere)
//{
//    Button* button = new Button(text, w, h,Button::Buttontype::menu, pere);
//    if(debut)
//    {
//        connect(button, SIGNAL(clicked()),jeu,SLOT(debut()));
//    }
//    else {
//        connect(button, SIGNAL(clicked()),jeu,SLOT(close()));
//    }
//    button->setPos( xpos, ypos);
//    return button;
//}
