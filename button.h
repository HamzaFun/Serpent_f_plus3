#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsDropShadowEffect>
#include <QGraphicsRectItem>
#include <QObject>
#include <QPropertyAnimation>

class Button :public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(qreal opacityFactor READ opacityFactor WRITE setOpacityFactor NOTIFY opacityFactorChanged )
//    Q_PROPERTY(qreal lightFactor READ lightFactor WRITE setLightFactor )
public:
    enum class Buttontype{
      menu, stage, retour/*, invalid*/
    };
    Button(QString name,int width, int height,Buttontype btnTyp, QGraphicsItem * parent = NULL);
    Button(QString name,int width, int height,int stg, QGraphicsItem * parent = NULL);

    Buttontype type;
    QString titre;
    QGraphicsPixmapItem* locke = NULL;
    QGraphicsTextItem* text;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void supprimerlock();
    void setHoverd();
    void setDecor(QPainter* painter);
    void setMonBrush(QBrush *brush);
    bool hovered;
    int stgNum ;

    QGraphicsBlurEffect* effect2;
    qreal m_opacityFactor;
    QPropertyAnimation * m_opacityAnimation;
    void setOpacityFactor(qreal valeur);
    qreal opacityFactor();

//    QPropertyAnimation* m_lightAnimation;
//    qreal m_lightFactor;
//    void setLightFactor(qreal lfact);
//    qreal lightFactor();

    QPropertyAnimation *creerAnimation(QByteArray propertyName, QObject *target, qreal startValeur, qreal finValeur, qreal duration, QEasingCurve easing);
//    void stop();
signals:
    void opacityFactorChanged(qreal);
    void clicked();
    void clicked(int);
    void clicked(QString);
};

#endif // BUTTON_H
