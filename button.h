#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QPropertyAnimation>

class Button :public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(qreal opacityFactor READ opacityFactor WRITE setOpacityFactor NOTIFY opacityFactorChanged )
public:
    enum class Buttontype{
      menu, stage, invalid
    };
    Button(QString name,int width, int height, QGraphicsItem * parent = NULL);
    Button(QString name,int width, int height,int stg, QGraphicsItem * parent = NULL);

    Buttontype type;
    QGraphicsPixmapItem* locke = NULL;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void deletelock();
    void setHoverd();
    void setDecor(QPainter* painter);
    bool hovered;
    int stgNum ;

    qreal m_opacityFactor;
    QPropertyAnimation * m_opacityAnimation;
    void setOpacityFactor(qreal valeur);
    qreal opacityFactor();

signals:
    void opacityFactorChanged(qreal);
    void clicked();
    void clicked(int);
private:
    QGraphicsTextItem* text;
    int width;
    int height;
};

#endif // BUTTON_H
