#pragma once

#include <QAbstractSlider>

class CustomSlider: public QAbstractSlider
{
    Q_OBJECT
public:
    CustomSlider(QWidget* parent=nullptr);
    void resetSlider(int max);
protected:
    void paintEvent(QPaintEvent *event)Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event)Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent* event)Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event)Q_DECL_OVERRIDE;
private:
    void mouseBrowsing(QMouseEvent* event);
    double incrementPortion=1.0;
    double proportion=1.0;
    int shadowSliderWidth=0;
private slots:
    void incrementSlider();
};

