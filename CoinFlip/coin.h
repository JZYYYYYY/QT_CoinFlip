#ifndef COIN_H
#define COIN_H

#include <QPushButton>
#include <QDebug>
#include <QTimer>

class Coin : public QPushButton
{
    Q_OBJECT
public:
    //explicit Coin(QWidget *parent = nullptr);

    //参数列表 传入金币路径/银币路径
    Coin(QString btnImg);
    void initBg(QString btnImg); //初始化背景和背景图片

    //调用私有变量的API
    void setPosX(int x);
    void setPosY(int y);
    void setFlag(bool st);
    int getPosX();
    int getPosY();
    bool getFlag();

    //改变flag
    void changeFlag();
    QTimer* timer1; //正面翻反面的定时器
    QTimer* timer2; //反面翻正面的定时器
    int min=1;
    int max=8;

    void connectSignalAndFlip(); //连接监听信号和翻转槽函数,并执行槽函数

private:
    int posX; //x坐标
    int posY; //y坐标
    bool flag; //正反标识

signals:

public slots:
};

#endif // COIN_H
