#include "button.h"

#include <QBrush>
#include <QColor>
#include <QCursor>
#include <QFont>
#include <QPainter>
#include <QPainterPath>
#include <QPen>

Button::Button(QString name,int width, int height, QGraphicsItem* parent):QGraphicsRectItem(parent)
{
    stgNum = 0;
    setRect(0,0,width,height);
    type = Buttontype::menu;
    QFont font;    
    font.setBold(true);
    font.setWeight(100);
    text = new QGraphicsTextItem(name,this);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);
    text->setDefaultTextColor(Qt::white);
    text->setFont(font);

    m_opacityAnimation = new QPropertyAnimation(this);
    m_opacityAnimation->setTargetObject(this);
    m_opacityAnimation->setPropertyName("opacityFactor");
    m_opacityAnimation->setStartValue(0);
    m_opacityAnimation->setEndValue(1);
    m_opacityAnimation->setDuration(800);
    m_opacityAnimation->setEasingCurve(QEasingCurve::OutCurve);
//    m_opacityAnimation->start();

    hovered = false;
    setAcceptHoverEvents(true);
}
Button::Button(QString name,int width, int height, int stg, QGraphicsItem* parent):QGraphicsRectItem(parent)
{
    stgNum = stg;
    setRect(0,0,width,height);
    type = Buttontype::stage;

    QFont font;
    font.setBold(true);
    font.setWeight(100);
    text = new QGraphicsTextItem(name,this);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);
    text->setDefaultTextColor(Qt::white);
    text->setFont(font);

    setAcceptHoverEvents(true);
    hovered = false;

    locke = new QGraphicsPixmapItem(this);
    locke->setPixmap(QPixmap(":/svgs/lock.png").scaled(30,30,Qt::KeepAspectRatio));
    locke->setPos(pos().x()+15, pos().y()+15);
    locke->setZValue(10);

}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    setDecor(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event)
    {
        emit clicked(stgNum);
        emit clicked();
    }

}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //change color
    if(event){
        hovered = true;

        update();
    }
}


void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    //change color
    if(event){
        hovered = false;
        update();
    }
}

void Button::deletelock()
{
    if(locke != NULL){
    delete locke;
    locke = NULL;
    }
}

void Button::setHoverd()
{
    if(locke != NULL){
    setOpacity(80);
    setAcceptedMouseButtons(Qt::NoButton);
    setAcceptHoverEvents(false);
    }
    else{
        setOpacity(100);
        setAcceptedMouseButtons(Qt::AllButtons);
        setAcceptHoverEvents(true);
        deletelock();
    }
}

void Button::setDecor(QPainter* painter)
{
    QPainterPath* path = new QPainterPath();
    QBrush brush;
    QPen pen;

    switch(type){
    case Button::Buttontype::menu :
        pen.setWidth(4);
        path->addRoundedRect(boundingRect(), 20,20);
        brush.setColor(QColor("#240b36"));
        pen.setColor(Qt::white);
        brush.setStyle(Qt::SolidPattern);
        if(hovered){
            pen.setWidth(2);
//            pen.setColor(Qt::white);
            brush.setColor(QColor("#240bf6"));
            setCursor(QCursor(Qt::PointingHandCursor));
        }
        break;
    default:
        break;
    }
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawPath(*path);

}

void Button::setOpacityFactor(qreal valeur)
{
    if(valeur == m_opacityFactor) return;
        m_opacityFactor = valeur;
    emit opacityFactorChanged(m_opacityFactor);

    this->setOpacity(m_opacityAnimation->currentValue().toReal());
}

qreal Button::opacityFactor()
{
    return m_opacityFactor;
}

