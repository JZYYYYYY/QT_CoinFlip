#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QDebug>
#include <QPropertyAnimation>
#include <QTimer>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);

    MyPushButton(QString normalImg,QString pressImg="");

    //弹跳特效
    void zoom1();
    void zoom2();

    //重写鼠标按下和释放事件
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

private:
    QString normalImgPath;
    QString pressImgPath;

signals:

public slots:
};

#endif // MYPUSHBUTTON_H
