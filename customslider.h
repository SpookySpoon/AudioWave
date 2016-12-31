#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H
#include <QWidget>

class CustomSlider: public QWidget
{
    Q_OBJECT
public:
    CustomSlider(QWidget* parent=nullptr);
    void onPress(QMouseEvent*);
    int progressPic=110;
    double proportion=1;
    bool pressedB=false;
    int shadowSlide=0;
protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void paintEvent(QPaintEvent *event)Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event)Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent* event)Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event)Q_DECL_OVERRIDE;
};

#endif // CUSTOMSLIDER_H
