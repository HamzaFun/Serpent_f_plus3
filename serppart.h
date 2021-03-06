#ifndef SERPPART_H
#define SERPPART_H

#include <QGraphicsPixmapItem>

class SerpPart :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    SerpPart(QGraphicsItem* parent=0);

    SerpPart* Preced();
    void setPreced(SerpPart* valeur);

    SerpPart* Suiv();
    void setSuiv(SerpPart* valeur);

    QString Direction();
    void setDirection(QString valeur);

    void move();
    void ajouterDerrier();
    void verifierCollObject();

    QString part;
    void setImage();

    static QString image;

    int pas;
    int l=5;

private:
    SerpPart* suiv;
    SerpPart* preced;
    QString direction;
public slots:
    static void setImage(QString valeur);

signals :
    void manger();
    void mangerF();
    void finStage();
    void gagnerJeu();
};

#endif // SERPPART_H
