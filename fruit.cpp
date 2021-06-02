#include "fruit.h"
#include "jeu.h"

#include <QPixmap>
Fruit::Fruit(QString name,QGraphicsItem* parent):QGraphicsPixmapItem(parent)
{
    if(name == "POMME"){
        setPixmap(QPixmap(":/rand/food.png").scaled(40,40));
        score = 1;

    }
    else{
        setPixmap(QPixmap(":/rand/food2.png").scaled(40,40,Qt::KeepAspectRatio));
        score = 2;
    }
//    effect = new QGraphicsBlurEffect();
//    effect->setBlurRadius(20);
//    setGraphicsEffect(effect);
//    m_blurAnimation = creerAnimation("blurFactor",this,0,1,300,QEasingCurve::OutCurve);

}

//void Fruit::setBlurFactor(qreal valeur)
//{
//    if(valeur == m_blurFactor) return ;
//    m_blurFactor = valeur;

//    effect->setBlurRadius(20*m_blurAnimation->currentValue().toReal());
//}


//qreal Fruit::blurFactor()
//{
//    return m_blurFactor;
//}

//QPropertyAnimation *Fruit::creerAnimation(QByteArray propertyName, QObject *target, qreal startValeur, qreal finValeur, qreal duration, QEasingCurve easing)
//{
//    QPropertyAnimation* m_animation = new QPropertyAnimation(this);
//    m_animation->setTargetObject(target);
//    m_animation->setPropertyName(propertyName);
//    m_animation->setStartValue(startValeur);
//    m_animation->setEndValue(finValeur);
//    m_animation->setDuration(duration);
//    m_animation->setEasingCurve(easing);
//    return m_animation;
//}
