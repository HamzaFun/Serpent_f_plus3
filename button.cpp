#include "button.h"
#include "jeu.h"

#include <QBrush>
#include <QColor>
#include <QCursor>
#include <QFont>
#include <QList>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QRegion>
extern Jeu* jeu;
Button::Button(QString name, int width, int height, Buttontype btnTyp, QGraphicsItem* parent):QGraphicsRectItem(parent)
{
    stgNum = 0;
    setRect(0,0,width,height);
    type = btnTyp;
    titre = name;

    QFont font;    
    font.setBold(true);
    font.setWeight(100);
    font.setPixelSize(30);
    font.setFamily("nickname demo");
    text = new QGraphicsTextItem(name,this);
    text->setFont(font);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);
    text->setDefaultTextColor(Qt::white);

    effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(0);
    effect->setOffset(0,0);
    effect->setColor(Qt::blue);
    setGraphicsEffect(effect);

    m_opacityAnimation = creerAnimation("opacityFactor",this,0,1,800,QEasingCurve::OutCurve);
//    m_opacityAnimation->start();
//    m_lightAnimation = creerAnimation("lightFactor", this, 0.3, 0.3, 2000, QEasingCurve::Linear);
//    m_lightAnimation->setKeyValueAt(0.5,1);
//    m_lightAnimation->setLoopCount(-1);
//    m_lightAnimation->start();

    hovered = false;
    setAcceptHoverEvents(true);
}
Button::Button(QString name,int width, int height, int stg, QGraphicsItem* parent):QGraphicsRectItem(parent)
{

    stgNum = stg;
    setRect(0,0,width,height);
    type = Buttontype::stage;
    titre = name;
    QFont font;
    font.setBold(true);
    font.setWeight(110);
    font.setPixelSize(20);
    font.setFamily("nickname demo");
    QPen pen;
    pen.setColor(Qt::black);
    text = new QGraphicsTextItem(name,this);

    text->setDefaultTextColor(Qt::white);
    text->setFont(font);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height() - text->boundingRect().height();
    text->setPos(xPos,yPos);

//    listImages = {"bg1.png", "bg2.png", "bg3.png", "bg4.png", "bg5.png", "bg6.png","bg7.png"};
    effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(0);
    effect->setOffset(0,0);
    effect->setColor(Qt::blue);
    setGraphicsEffect(effect);

//    m_lightAnimation = creerAnimation("lightFactor", this, 0.3, 0.3, 2000, QEasingCurve::Linear);
//    m_lightAnimation->setKeyValueAt(0.5,1);
//    m_lightAnimation->setLoopCount(-1);
    hovered = false;
    setAcceptHoverEvents(true);

    locke = new QGraphicsPixmapItem(this);
    locke->setPixmap(QPixmap(":/rand/lock.png").scaled(50,50,Qt::KeepAspectRatio));
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
//    stop();
    if(event)
    {
        if(stgNum != 0)
            emit clicked(stgNum);
        else {
            if(titre == "REJOUER") emit clicked(jeu->StageCourant);
            if(titre == "NEXT") emit clicked(++jeu->StageCourant);
            if(titre == "DEFAULT"){
                emit clicked("");
            }else if(titre == "KOBRA") emit clicked("1");
            else if(titre == "JUNGLE") emit clicked("2");
            else if(titre == "SPIRIT") emit clicked("3");
        }
        if(type == Button::Buttontype::stage) emit jeu->sfx->trigger(jeu->sfx->click_1);
        else
            emit jeu->sfx->trigger(jeu->sfx->click_2);
        emit clicked();
    }

}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //change color
    if(event){
//        m_lightAnimation->start();
        emit jeu->sfx->trigger(jeu->sfx->hover_1);
        hovered = true;
        text->setY( text->y()+2);
        update();
    }
}


void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    //change color
    if(event){
//        stop();
        hovered = false;
        text->setY(text->y()-2);
        if(effect != NULL)
            effect->setBlurRadius(0);
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
        pen.setColor(Qt::white);
        if(hovered){
            pen.setWidth(2);
            setCursor(QCursor(Qt::PointingHandCursor));
        }
        brush.setStyle(Qt::SolidPattern);
        setMonBrush(&brush);
        if(titre == "JEU SERPENT" || titre == "STAGES" || titre == "OUI" || titre == "NON"){
            painter->setBrush(brush);
        }
        break;
    case Button::Buttontype::retour :
        pen.setWidth(4);
        path->addRoundedRect(boundingRect(), 20, 10);
        brush.setColor(QColor("#268be0"));
        pen.setColor(Qt::white);
        brush.setStyle(Qt::SolidPattern);
        if(hovered){
            pen.setWidth(2);
            brush.setColor(QColor("#2a96f2"));
            setCursor(QCursor(Qt::PointingHandCursor));
        }
        painter->setBrush(brush);
        break;
    case Button::Buttontype::stage :
        pen.setWidth(6);
        path->addRoundedRect(boundingRect(), 30, 30);
        brush.setColor(QColor("#0b5097"));
        pen.setColor(Qt::white);
        brush.setStyle(Qt::SolidPattern);
        painter->setClipPath(*path);
        painter->setBackground(brush);
//        if(parentItem()->opacity() == 1){
        if(hovered){
            pen.setWidth(3);
            painter->drawPixmap(0,0, QPixmap(":/bg/bg"+QString::number(stgNum)+".png").scaled(150,150,Qt::KeepAspectRatioByExpanding));
            setCursor(QCursor(Qt::PointingHandCursor));
        }else{
            painter->drawPixmap(0,0, QPixmap(":/bg/bg"+QString::number(stgNum)+".png").scaled(190,190,Qt::KeepAspectRatioByExpanding));
        }
//        }
        break;
        case Button::Buttontype::invalid :
        break;
    }
    painter->setPen(pen);
    painter->drawPath(*path);

}

void Button::setMonBrush(QBrush *brush)
{
    if(hovered){
    if(titre == "OUI"){
        brush->setColor(QColor("#dd1f1f"));
    }
    else if(titre == "NON" ){
        brush->setColor(QColor("#1ec94a"));
    }else{
        brush->setColor(QColor("#086fd8"));
    }
    }else{
        if(titre == "OUI"){
            brush->setColor(Qt::black);
        }
        else if(titre == "NON" ){
            brush->setColor(QColor("#19ac3f"));
        }else{
            brush->setColor(QColor("#094583"));
        }

    }
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

//void Button::setLightFactor(qreal lfact)
//{
//    if(lfact == m_lightFactor) return;
//    m_lightFactor = lfact;

//    effect->setBlurRadius( 50*m_lightAnimation->currentValue().toReal() );

//}

//qreal Button::lightFactor()
//{
//    return m_lightFactor;
//}
QPropertyAnimation *Button::creerAnimation(QByteArray propertyName, QObject *target, qreal startValeur, qreal finValeur, qreal duration, QEasingCurve easing)
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

//void Button::stop()
//{
//    if(m_lightAnimation->state() == QAbstractAnimation::Running)
//        m_lightAnimation->stop();
//}
