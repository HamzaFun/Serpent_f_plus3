#ifndef FRUIT_H
#define FRUIT_H

#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <QString>
#include <qpropertyanimation.h>

class Fruit :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
//    Q_PROPERTY(qreal blurFactor READ blurFactor WRITE setBlurFactor)
public:
    Fruit(QString name = "" ,QGraphicsItem* parent=0);
    int score;
//    QGraphicsBlurEffect* effect = NULL;
//    qreal m_blurFactor;
//    QPropertyAnimation * m_blurAnimation = NULL;
//    void setBlurFactor(qreal valeur);
//    qreal blurFactor();
//    QPropertyAnimation* creerAnimation(QByteArray propertyName, QObject *target, qreal startValeur, qreal finValeur, qreal duration, QEasingCurve easing);
//signals:
//    void blurFactorChanged(qreal);
};

#endif // FRUIT_H
