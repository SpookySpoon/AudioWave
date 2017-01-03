#pragma once

#include <QWidget>

class CustomSlider: public QWidget
{
    Q_OBJECT
public:
    CustomSlider(QWidget* parent=nullptr);
    void setMaximum(int max);
    int getValue();
    int getMaximum();
    void setValue(int);
protected:
    void paintEvent(QPaintEvent *event)Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event)Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent* event)Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event)Q_DECL_OVERRIDE;
private:
    void mouseBrowsing(QMouseEvent* event);
    double incrementPortion=1.0;
    double proportion=1.0;
    int shadowSlide=0;
    int value=0;
    int maximum=100;
private slots:
    void incrementSlider();
    void incrementValue();
signals:
    void moved(int);
    void browsing(int);


};

