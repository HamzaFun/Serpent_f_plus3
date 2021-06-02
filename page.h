#ifndef PAGE_H
#define PAGE_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QPropertyAnimation>

class Page : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(qreal animationFactor READ animationFactor WRITE setAnimationFactor NOTIFY animationFactorChanged )
    Q_PROPERTY(qreal positionFactor READ positionFactor WRITE setPositionFactor NOTIFY positionFactorChanged)
    Q_PROPERTY(qreal scrollFactor READ scrollFactor WRITE setScrollFactor NOTIFY scrollFactorChanged)


public:
    Page(QString titre, QString font, Qt::GlobalColor couleur, QGraphicsItem* parent=0);
    Page(QString titre, QString font, QString fin, Qt::GlobalColor couleur, QGraphicsItem* parent=0);

    QGraphicsTextItem* text = NULL;
    QString titre = "";
    QGraphicsPixmapItem* transparencyBackground = NULL;
    void fadeOut();
    void fadeIn();
    QPropertyAnimation* creerAnimation(QByteArray propertyName, QObject *target, qreal startValeur, qreal finValeur, qreal duration, QEasingCurve easing);

    qreal m_animationFactor;
    QPropertyAnimation * m_animation;
    void setAnimationFactor(qreal valeur);
    qreal animationFactor();

    qreal m_positionFactor;
    QPropertyAnimation* m_positionAnimation;
    void setPositionFactor(qreal pfact);
    qreal positionFactor();

    qreal m_scrollFactor;
    QPropertyAnimation* m_scrollAnimation = NULL;
    void setScrollFactor(qreal sfact);
    qreal scrollFactor();

    void creerText(QString contenue,int x,int y, QFont font, int fontsize , QColor couleur);

signals:
    void animationFactorChanged(qreal);
    void positionFactorChanged(qreal);
    void scrollFactorChanged(qreal);
};

#endif // PAGE_H
