#include <QTimer>
#include <QPainter>
#include <QEvent>
#include <QDebug>
#include <QMouseEvent>
#include "customslider.h"

CustomSlider::CustomSlider(QWidget* parent):
    QAbstractSlider(parent)
{
}

void CustomSlider::mousePressEvent(QMouseEvent* event)
{
    mouseBrowsing(event);
}
void CustomSlider::mouseMoveEvent(QMouseEvent *event)
{
    mouseBrowsing(event);
}
void CustomSlider::mouseReleaseEvent(QMouseEvent* event)
{
    shadowSliderWidth=0;
    proportion=event->pos().x()/(double)width();
    setValue(maximum()*(double)proportion);
    repaint();
}

void CustomSlider::paintEvent(QPaintEvent *)
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

    if(shadowSliderWidth)
    {
        QPainter opaShadowPainter(this);
        QBrush brush(QColor(0, 0, 0, 100));
        opaShadowPainter.setPen(Qt::NoPen);
        opaShadowPainter.setBrush(brush);
        opaShadowPainter.drawRect(0,0,shadowSliderWidth,height());
    }
}
void CustomSlider::incrementSlider()
{
    proportion+=incrementPortion;
    repaint();
}
void CustomSlider::resetSlider(int max)
{
    setValue(0);
    proportion=0.0;
    incrementPortion=1/(double)max/5.0;
    setMaximum(max);
    repaint();
}

void CustomSlider::mouseBrowsing(QMouseEvent* event)
{
    shadowSliderWidth=std::min(std::max(event->pos().x(),0),width());
    repaint();
    emit sliderMoved(maximum()*shadowSliderWidth/(double)width());
}
