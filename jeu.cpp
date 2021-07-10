#include "button.h"
#include "jeu.h"
#include "murpart.h"
#include "obstacles.h"
#include "page.h"

#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QMediaPlaylist>
#include <QPushButton>
#include <QStyle>
#include <QTimer>

Jeu::Jeu(QWidget *parent):QGraphicsView(parent)
, font("nickname demo")
{
    // charger la vue :
    setFixedSize(1200,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);
    // charger la scene de jeu
    sceneDeJeu = new QGraphicsScene(this);
    background = new QGraphicsPixmapItem();
    sfx = new SoundEffects(this);
    sceneDeJeu->setSceneRect(0,0,1200,600);
    setScene(sceneDeJeu);
    background->setZValue(0);
    millieu_scene = QPointF(600,300);
    debut_scene = QPointF(50, 500);
    //initialiser la music
    back_music = new BackMusic(this);
//    background_music = new Music("ingame_music1.mp3", this);
//    menu_music = new Music("menu_music2.mp3", this);
//    findejeu_music = new Music("gameover_music.mp3");
    //initialiser le score
    score =new Score();
    peau = "";

    creerToutPages();

    serp = NULL;
    StageCourant = 1;
    StageAttendue = 1;
}

void Jeu::keyPressEvent(QKeyEvent *event)
{
    if(serp){
        serp->keyPressEvent(event);
    }else{
        QGraphicsView::keyPressEvent(event);
    }
    if((event->key() == Qt::Key_Space || event->key() == Qt::LeftButton) && finTextPage != NULL){
        if(finTextPage->opacity() == 1)
            afficherMenu();
    }

}
void Jeu::afficherFin()
{
    fadeOutAll();
    finPage->fadeIn();
    if(!sceneDeJeu->items().contains(finPage)){      
        int rx = millieu_scene.x() - 75 - debut_scene.x();
        if(topScore < score->getScore()) topScore = score->getScore();
        if( obs == NULL){
            finPage->creerText("TOP SCORE :", rx+30, millieu_scene.y() - 80,font,35,Qt::yellow );
            finPage->creerText(QString::number(topScore), rx+180, millieu_scene.y() - 80,font,35,Qt::yellow );
        }else{
            finPage->creerText("VOTRE SCORE :", rx+30, millieu_scene.y() - 80,font,35,Qt::yellow );
            finPage->creerText(QString::number(score->getScore()), rx+180, millieu_scene.y() - 80,font,35,Qt::yellow );
        }

        Button* rejoue = creerBtn("REJOUER", 150, 40, rx , millieu_scene.y() - 20, true, finPage);
        Button* quit = new Button("RETOUR", 150, 40, Button::Buttontype::retour, finPage);
        int ry =  debut_scene.y();
        quit->setPos(rx,ry);
        connect(quit, SIGNAL(clicked()), this, SLOT(retourMenu()));
        sceneDeJeu->addItem(finPage);
        Q_UNUSED(rejoue);
        Q_UNUSED(quit);
    }
}

void Jeu::afficherNext()
{
    fadeOutAll();
    nextStgPage->fadeIn();
    serp->t->stop();
//    suprimerItem(serp);
//    serp = NULL;
    if(StageAttendue == StageCourant ){
        StageAttendue++;
    }

    if(!sceneDeJeu->items().contains(nextStgPage)){
        int nx = millieu_scene.x() + 30 - debut_scene.x();
        int ny = millieu_scene.y() - 20;
        nextStgPage->creerText("VOTRE SCORE :", nx-55, ny-60,font,35,Qt::yellow );
        nextStgPage->creerText(QString::number(score->getScore()), nx+95, ny-60,font,35,Qt::yellow );
        Button* rejouer = creerBtn("REJOUER", 150, 40, millieu_scene.x() - 180 - debut_scene.x() , ny, true, nextStgPage);
        Button* next = new Button("NEXT", 150, 40, Button::Buttontype::menu, nextStgPage);
        next->setPos(nx,ny);
        connect(next, SIGNAL(clicked(int)), this, SLOT(creerObs(int)));
        Button* retour = new Button("RETOUR", 150, 40, Button::Buttontype::retour, nextStgPage);
        int rx = millieu_scene.x() - 75 - debut_scene.x();
        int ry = debut_scene.y();
        retour->setPos(rx,ry);
        connect(retour, SIGNAL(clicked()), this, SLOT(retourMenu()));
        sceneDeJeu->addItem(nextStgPage);
        Q_UNUSED(rejouer);
        Q_UNUSED(next);
    }


}

void Jeu::afficherMenu()
{
    back_music->jeu_music->stopMusic();
    back_music->findejeu_music->stopMusic();
    back_music->menu_music->playMusic();

    fadeOutAll();
    background->setPixmap(QPixmap(":/bg/imageMenu.jpg").scaled(1200,600));
    if(!sceneDeJeu->items().contains(background)){
        sceneDeJeu->addItem(background);
    }
    if(!sceneDeJeu->items().contains(menuPage)){
        Button* stages = new Button("STAGES", 150,40,Button::Buttontype::menu, menuPage);
        int mxPos = debut_scene.x() ;
        int myPos = 200;
        stages->setPos(mxPos,myPos);
        connect(stages, SIGNAL(clicked()), this, SLOT(afficherStages()));

        Button* info = new Button("!", 40,40,Button::Buttontype::menu, menuPage);
        info->setPos(1100,10);
        connect(info, SIGNAL(clicked()), this, SLOT(afficherInfo()));

        Button* peau = new Button("Choisir Votre Serpent", 350,40,Button::Buttontype::menu, menuPage);
        int pxPos = 780 ;
        int pyPos = 540 ;

        peau->setPos(pxPos,pyPos);
        connect(peau, SIGNAL(clicked()), this, SLOT(afficherPeau()));

        Button* joue = creerBtn("JOUER", 150, 40,  mxPos + 40, myPos + 60, true, menuPage);
        Button* quit = creerBtn("QUIT", 150, 40,  mxPos + 80, myPos + 120, false, menuPage);
            sceneDeJeu->addItem(menuPage);
        Q_UNUSED(joue);
        Q_UNUSED(info);
        Q_UNUSED(quit);
    }
    menuPage->fadeIn();
}

void Jeu::afficherStages()
{
    fadeOutAll();
    stagesPage->fadeIn();

    //creer les bouttons des stages
    if(!sceneDeJeu->items().contains(stagesPage)){
    int x = 160 ;
    int y = 100;
    int h = 150;
    Button* stage = creerStg("DEBUT", h, h, 175,y, 1, stagesPage);
    Button* stage2 = creerStg("CHAMBRE", h, h, x +175 ,  y, 2, stagesPage);
    Button* stage3 = creerStg("PASSERELLE", h, h, 2*x +175, y, 3, stagesPage);
    Button* stage4 = creerStg("PASSERELLE 2", h, h, 3*x +175, y, 4, stagesPage);
    Button* stage5 = creerStg("FONDERIE", h, h, 4*x +175, y, 5, stagesPage);
    Button* stage6 = creerStg("JARDIN", h, h, 175    ,3*y, 6, stagesPage);
    Button* stage7 = creerStg("TOURBIER", h, h, x+175  ,3*y, 7, stagesPage);
    Button* stage8 = creerStg("CHEMIN DE CIEL", h, h, 2*x+175,3*y, 8, stagesPage);

    //bouton de routeur
    Button* retour = new Button("<< RETOUR", 140, 50, Button::Buttontype::retour, stagesPage);
    int rx = debut_scene.x();
    int ry = debut_scene.y();
    retour->setPos(rx,ry);
    connect(retour, SIGNAL(clicked()), this, SLOT(retourMenu()));
        sceneDeJeu->addItem(stagesPage);
    //specifier les variables qu'il sont non utilise
    Q_UNUSED(stage);
    Q_UNUSED(stage2);
    Q_UNUSED(stage3);
    Q_UNUSED(stage4);
    Q_UNUSED(stage5);
    Q_UNUSED(stage6);
    Q_UNUSED(stage7);
    Q_UNUSED(stage8);
    }
}

void Jeu::afficherPause()
{
    fadeOutAll();
    pausePage = new Page("PAUSE", font, Qt::white);
    //creer le text de pause
    pausePage->fadeIn();
    //creer les boutons
    if(!sceneDeJeu->items().contains(pausePage)){

        Button* commancer = new Button("COMMANCER", 200, 40,Button::Buttontype::menu, pausePage);
        int x = millieu_scene.x() - commancer->boundingRect().width()/2 - debut_scene.x() ;
        commancer->setPos(x, millieu_scene.y() - 20);
        if(StageCourant < StageAttendue && StageCourant != 0){
            Button* next = new Button("NEXT", 150, 40, Button::Buttontype::menu, pausePage);
            next->setPos(millieu_scene.x() - debut_scene.x() - next->boundingRect().width()/2, millieu_scene.y() - 90);
            connect(next, SIGNAL(clicked(int)), this, SLOT(creerObs(int)));
        }
        connect(commancer, SIGNAL(clicked()), this, SLOT(commancer()) );
        Button* recommancer = creerBtn("RECOMMANCER", 200, 40, x , millieu_scene.y() + 60, true, pausePage);

        //bouton de routeur
        Button* routeur = new Button("<< RETOUR", 160, 50, Button::Buttontype::retour, pausePage);
        int rx = millieu_scene.x() - routeur->boundingRect().width()/2 - debut_scene.x();
        int ry = debut_scene.y();
        routeur->setPos(rx,ry);
        connect(routeur, SIGNAL(clicked()), this, SLOT(choix()) );
            sceneDeJeu->addItem(pausePage);
        Q_UNUSED(recommancer);
        Q_UNUSED(routeur);
    }
}

void Jeu::afficherInfo()
{
    fadeOutAll(); infoPage->fadeIn();

//    if(!sceneDeJeu->items().contains(commentjouer)){
//        sceneDeJeu->addItem(commentjouer);
//    }
    if(!sceneDeJeu->items().contains(infoPage)){
        QGraphicsPixmapItem * commentjouer = new QGraphicsPixmapItem(QPixmap(":/bg/comment.png").scaled(1200,600), infoPage);
        commentjouer->setPos(-50,0);
        infoPage->text->setPos(0,0);
        Button* retour = new Button("<< RETOUR", 140, 50, Button::Buttontype::retour, infoPage);
        int rx = debut_scene.x();
        int ry = debut_scene.y();
        retour->setPos(rx,ry);
        connect(retour, SIGNAL(clicked()), this, SLOT(retourMenu()));
        sceneDeJeu->addItem(infoPage);
    }
}

void Jeu::afficherPeau()
{
    fadeOutAll(); peauPage->fadeIn();

    if(!sceneDeJeu->items().contains(peauPage)){
        int x = 160 ;
        int y = 200;
        int h = 150;
        Button* defaut = new Button("DEFAULT", h, h, 0, peauPage);
        defaut->setPos( 175, y);
        defaut->supprimerlock();
        connect(defaut, SIGNAL(clicked(QString)),this,SLOT(setPeau(QString)));
        Button* kobra = new Button("KOBRA", h, h, 0, peauPage);
        kobra->setPos( x+175, y);
        kobra->supprimerlock();
        connect(kobra, SIGNAL(clicked(QString)),this,SLOT(setPeau(QString)));
        Button* jungle = new Button("JUNGLE", h, h, 0, peauPage);
        jungle->setPos( 2*x+175, y);
        jungle->supprimerlock();
        connect(jungle, SIGNAL(clicked(QString)),this,SLOT(setPeau(QString)));
        Button* spirit = new Button("SPIRIT", h, h, 0, peauPage);
        spirit->setPos( 3*x+175, y);
        spirit->supprimerlock();
        connect(spirit, SIGNAL(clicked(QString)),this,SLOT(setPeau(QString)));

        Button* retour = new Button("<< RETOUR", 140, 50, Button::Buttontype::retour, peauPage);
        int rx = debut_scene.x();
        int ry = debut_scene.y();
        retour->setPos(rx,ry);
        connect(retour, SIGNAL(clicked()), this, SLOT(retourMenu()));
        sceneDeJeu->addItem(peauPage);
    }
}


void Jeu::debut()
{
    // controler la music
    back_music->stopAll();
    back_music->jeu_music->playMusic();
    fadeOutAll();
    supprimerToutPages();
    creerToutPages();
    if(obs == NULL ){
    background->setPixmap(QPixmap(":/bg/blackbg.jpg").scaled(1200,600));
    sceneDeJeu->addItem(background);
    }

    //initialiser le serpent
    if(serp != NULL)
    {
        sceneDeJeu->removeItem(serp);
        serp =NULL;
    }
    serp = new AnimerSerpent();
    serp->setFlag(QGraphicsItem::ItemIsFocusable);
    serp->setFocus();
    sceneDeJeu->addItem(serp);

    score->setScore(0);

//    if(serp2) serp2->deleteLater();
//    serp2 = serp;
}
void Jeu::finJeu()
{
    back_music->stopAll();
    back_music->findejeu_music->playMusic();
    serp->t->stop();
    serp->setFlag(QGraphicsItem::ItemStopsClickFocusPropagation);
    afficherFin();
}

void Jeu::commancer()
{
//    if(!serp->t->isActive()){
    fadeOutAll();
    suprimerItem(pausePage);
    suprimerItem(choixPage);
//    }

}
void Jeu::choix()
{
    fadeOutAll();
    choixPage->fadeIn();

    if(!sceneDeJeu->items().contains(choixPage)){
        Button* oui = new Button("OUI", 70, 70, Button::Buttontype::menu, choixPage);
        int rx = millieu_scene.x() - oui->boundingRect().width() - debut_scene.x() -30;
        int ry = millieu_scene.y() - oui->boundingRect().width()/2;
        oui->setPos(rx,ry);
        connect(oui, SIGNAL(clicked()), this, SLOT(retourMenu()) );
        Button* non = new Button("NON", 70, 70, Button::Buttontype::menu, choixPage);
        int nx = millieu_scene.x() + oui->boundingRect().width() - debut_scene.x() -20;
        int ny = millieu_scene.y() - oui->boundingRect().width()/2;
        non->setPos(nx,ny);
        connect(non, SIGNAL(clicked()), this, SLOT(afficherPause()) );
            sceneDeJeu->addItem(choixPage);
    }
}

void Jeu::retourAffich()
{
    if(obs != NULL){
        sceneDeJeu->removeItem(obs);
        delete obs;
        obs = NULL;
    }
    suprimerItem(serp);
    delete serp;
    serp = NULL;

    afficherMenu();

}

void Jeu::retourMenu()
{
    fadeOutAll();
    suprimerItem(serp);
    delete serp;
    serp = NULL;
    if(sceneDeJeu->items().contains(obs)){
        sceneDeJeu->removeItem(obs);
        delete obs;
        obs = NULL;
    }
    afficherMenu();
}

void Jeu::afficherGagner()
{
    fadeOutAll();
    gagnerPage->fadeIn();
    serp->t->stop();


    if(!sceneDeJeu->items().contains(gagnerPage)){
        int nx = millieu_scene.x() + 30 - debut_scene.x();
        int ny = millieu_scene.y() - 20;
        Button* rejouer = creerBtn("REJOUER", 150, 40, millieu_scene.x() - 180 - debut_scene.x() , ny, true, gagnerPage);
        Button* fin = new Button("FIN", 150, 40, Button::Buttontype::menu, gagnerPage);
        fin->setPos(nx,ny);
        connect(fin, SIGNAL(clicked()), this, SLOT(afficherFinText()));
        Button* retour = new Button("RETOUR", 150, 40, Button::Buttontype::retour, gagnerPage);
        int rx = millieu_scene.x() - 75 - debut_scene.x();
        int ry = debut_scene.y();
        retour->setPos(rx,ry);
        connect(retour, SIGNAL(clicked()), this, SLOT(retourMenu()));
        sceneDeJeu->addItem(gagnerPage);
        Q_UNUSED(rejouer);
        Q_UNUSED(fin);
    }
}

void Jeu::afficherFinText()
{
    back_music->stopAll();
    back_music->menu_music->playMusic();
    fadeOutAll();
    finTextPage->fadeIn();
    serp->t->stop();
    suprimerItem(serp);
    if(sceneDeJeu->items().contains(obs)){
        sceneDeJeu->removeItem(obs);
        delete obs;
        obs = NULL;
    }

    if(!sceneDeJeu->items().contains(finTextPage)){
        sceneDeJeu->addItem(finTextPage);
    }
}

void Jeu::setPeau(QString val)
{
    peau = val;
}

void Jeu::creerObs(int NumObs)
{
    //supprimer obstacles
    if(sceneDeJeu->items().contains(obs)){
        sceneDeJeu->removeItem(obs);
        delete obs;
        obs = NULL;
    }

    //creer les obstacles
    StageCourant = NumObs;
    if(NumObs != 0 ){
        obs = new Obstacles(NumObs);
        sceneDeJeu->addItem(obs);
        background->setPixmap(QPixmap(obs->bg).scaled(1200,600));
        background->setZValue(0);
        sceneDeJeu->addItem(background);
    }
    //debut de stage
    debut();
}

Button *Jeu::creerStg(QString text, int w, int h, int xpos, int ypos, int stg, Page *pere)
{
    Button* button;
    button = new Button(text, w, h, stg, pere);
    if(stg <= StageAttendue){
        button->supprimerlock();
    }
    button->setHoverd();
    connect(button, SIGNAL(clicked(int)),this,SLOT(creerObs(int)));

    button->setPos( xpos, ypos);
    return button;
}
Button *Jeu::creerBtn(QString text, int w, int h, int xpos, int ypos, bool debut, Page *pere)
{
    Button* button = new Button(text, w, h,Button::Buttontype::menu, pere);
    if(debut)
    {
        connect(button, SIGNAL(clicked()),this,SLOT(debut()));
    }
    else {
        connect(button, SIGNAL(clicked()),this,SLOT(close()));
    }
    button->setPos( xpos, ypos);
    return button;
}

void Jeu::suprimerItem(QGraphicsItem *item)
{
    if(sceneDeJeu->items().contains(item)){
        sceneDeJeu->removeItem(item);
    }
}

void Jeu::supprimerToutPages()
{
    suprimerItem(menuPage);
    suprimerItem(stagesPage);
    suprimerItem(nextStgPage);
    suprimerItem(choixPage);
    suprimerItem(pausePage);
    suprimerItem(finPage);
    suprimerItem(gagnerPage);
    suprimerItem(finTextPage);
    suprimerItem(infoPage);
    suprimerItem(peauPage);
}

void Jeu::creerToutPages()
{
    menuPage = new Page("JEU SERPENT", font, Qt::white);
    stagesPage = new Page("STAGES", font, Qt::white);
    nextStgPage = new Page("FELICITATION", font, Qt::white);
    choixPage = new Page("WARNING", font, Qt::red);
    pausePage = new Page("PAUSE", font, Qt::white);
    finPage = new Page("Fin De Jeu", font, Qt::white);
    gagnerPage = new Page("Complete", font, Qt::yellow);
    finTextPage = new Page("SERPENT PRO", font, "vrai", Qt::yellow);
    infoPage = new Page("INFORMATIONS", font, Qt::white);
    peauPage = new Page("LES PEAUS", font, Qt::white);
}

void Jeu::fadeOutAll()
{
    if(menuPage->opacity() != 0)
        menuPage->fadeOut();
    if(stagesPage->opacity() != 0)
        stagesPage->fadeOut();
    if(nextStgPage->opacity() != 0)
        nextStgPage->fadeOut();
    if(choixPage->opacity() != 0)
        choixPage->fadeOut();
    if(pausePage->opacity() != 0)
        pausePage->fadeOut();
    if(finPage->opacity() != 0)
        finPage->fadeOut();
    if(gagnerPage->opacity() != 0)
        gagnerPage->fadeOut();
    if(finTextPage->opacity() != 0)
        finTextPage->fadeOut();
    if(infoPage->opacity() != 0)
        infoPage->fadeOut();
    if(peauPage->opacity() != 0)
        peauPage->fadeOut();
}



