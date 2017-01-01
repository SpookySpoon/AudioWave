#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H
#include <QWidget>

class CustomSlider: public QWidget
{
    Q_OBJECT
public:
    CustomSlider(QWidget* parent=nullptr);
    void setMaximum(int max);
    int getValue();
    void setValue(int);
protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void paintEvent(QPaintEvent *event)Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event)Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent* event)Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event)Q_DECL_OVERRIDE;
private:
    void mouseBrowsing(QMouseEvent* event);
    double incrementPortion=1.0;//NEW
    double proportion=1.0;
    int shadowSlide=0;
    int value=0;
    int maximum=100;
private slots:
    void incrementSlider();//NEW
    void incrementValue();//NEW
signals:
    void moved(int);
    void browsing(int);


};

#endif // CUSTOMSLIDER_H
