#ifndef JEU_H
#define JEU_H

#include <QGraphicsView>
#include <QMediaPlayer>
#include <QPropertyAnimation>
#include "animerserpent.h"
#include "button.h"
#include "obstacles.h"
#include "score.h"
#include "soundeffects.h"
#include "music.h"
#include "page.h"
#include "backmusic.h"

class Jeu : public QGraphicsView
{
    Q_OBJECT
public:
    Jeu(QWidget* parent=0);
    QGraphicsScene* sceneDeJeu;
    AnimerSerpent* serp;
    Score* score;
    Obstacles* obs = NULL;
    BackMusic* back_music;
    SoundEffects* sfx;

    Page* menuPage = NULL;
    Page* pausePage = NULL;
    Page* choixPage = NULL;
    Page* stagesPage = NULL;
    Page* nextStgPage = NULL;
    Page* finPage = NULL;
    Page* gagnerPage = NULL;
    Page* finTextPage = NULL;
    Page* infoPage = NULL;
    Page* peauPage = NULL;

    QString peau;
    int StageCourant;
    int StageAttendue;
    int topScore = 0;
    QPointF millieu_scene;
    QPointF debut_scene;

    void keyPressEvent(QKeyEvent *event);
    void afficherMenu();
    void afficherFin();
    void finJeu();
    void suprimerItem(QGraphicsItem* item);
private:
    QGraphicsPixmapItem* background;
//    QMediaPlayer* creerMusic(QString music);

    Button* creerStg(QString text, int w, int h, int xpos, int ypos, int stg, Page* pere);
    Button* creerBtn(QString text, int w, int h, int xpos, int ypos, bool debut, Page* pere);
    QString font;
    void supprimerToutPages();
    void creerToutPages();
    void fadeOutAll();
public slots:
    void debut();
    void creerObs(int);
    void afficherStages();
    void afficherNext();
    void afficherPause();
    void afficherInfo();
    void afficherPeau();
    void choix();
    void retourAffich();
    void commancer();
    void retourMenu();
    void afficherGagner();
    void afficherFinText();
    void setPeau(QString);
signals:
    void opacityFactorChanged(qreal);
};

#endif // JEU_H
