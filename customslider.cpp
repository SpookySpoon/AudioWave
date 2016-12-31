#include <QPainter>
#include <QEvent>
#include <QDebug>
#include <QMouseEvent>
#include "customslider.h"

CustomSlider::CustomSlider(QWidget* parent):
    QWidget(parent)
{
    this->installEventFilter(this);
}

bool CustomSlider::eventFilter(QObject *, QEvent *event)
{

    switch (event->type())
    {
//        case QEvent::MouseButtonPress:
////            onPress(static_cast<QMouseEvent*>(event));
//            return true;
//        case QEvent::MouseMove:
////            onPress(static_cast<QMouseEvent*>(event));
//            return true;

        default:
            return false;
    }
}

void CustomSlider::mousePressEvent(QMouseEvent* event)
{
    shadowSlide=event->pos().x();
//    proportion=event->pos().x()/(double)width();
    repaint();
}
void CustomSlider::mouseMoveEvent(QMouseEvent *event)
{
    shadowSlide=event->pos().x();
//    proportion=event->pos().x()/(double)width();
    repaint();
}
void CustomSlider::mouseReleaseEvent(QMouseEvent* event)
{
    shadowSlide=0;
    proportion=event->pos().x()/(double)width();
    repaint();
}

void CustomSlider::paintEvent(QPaintEvent *event)
{   
    QImage dragonSlider(":/DragonSlider_OpaqueLong.png");
    dragonSlider=dragonSlider.scaled(width(),height(),Qt::IgnoreAspectRatio);

    QPainter backgroundPainter(this);
    backgroundPainter.setCompositionMode(QPainter::CompositionMode_Source);

    QBrush brush(QColor(255, 100, 0, 255));
    QBrush brush1(QColor(255, 255, 255, 100));
    backgroundPainter.setBrush(brush);
    backgroundPainter.setPen(Qt::NoPen);
    backgroundPainter.drawRect(0,0,proportion*width(),height());

    backgroundPainter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    backgroundPainter.drawImage(QPoint(0,0),dragonSlider);


    backgroundPainter.setBrush(brush1);
    backgroundPainter.drawRect(proportion*width(),0,(1-proportion)*width(),height());

    if(shadowSlide)
    {
        QPainter opaShadowPainter(this);
        QBrush brush(QColor(0, 0, 0, 100));
        opaShadowPainter.setPen(Qt::NoPen);
        opaShadowPainter.setBrush(brush);
        opaShadowPainter.drawRect(0,0,shadowSlide,height());
    }
}
