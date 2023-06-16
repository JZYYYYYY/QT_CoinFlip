#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QMainWindow>
#include <QDebug>
#include <QMenuBar>
#include <QAction>
#include <QPainter>
#include <mypushbutton.h>
#include <QLabel>
#include "coin.h"
#include <QPropertyAnimation>
#include <QSound>

class GameScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameScene(QWidget *parent = nullptr);

    //调用私有变量的API
    GameScene(int levelNum);
    int getLevelIndex();
    void setGameArray(int i,int j,int value);
    int getGameArray(int i,int j);
    void setCoinBtn(int i,int j,Coin* coin);
    Coin* getCoinBtn(int i,int j);

    //画背景图
    void paintEvent(QPaintEvent*);

    //初始化游戏场景
    void initBg();

    //实现back按钮
    void backButton(QSound* backSound);

    //在场景中显示关卡数
    void showLevel();

    //创建胜利图片
    QLabel* setWinImg();

    //创建金/银币
    Coin* setCoin(int i,int j);

    //实现翻转
    void showFlip(Coin* coin,QSound* coinFlipSound);

    //判断是否胜利
    void judge();

    //显示胜利图片和音效
    void showWin(QSound *winSound, QLabel *winLabel);

    //是否胜利的标志
    bool isWin=false;

private:
    int levelIndex; //记录所选的关卡
    int gameArray[4][4]; //维护每个关卡具体数据
    Coin* coinBtn[4][4]; //维护每个关卡的每个金/银币

signals:
    //自定义信号，表示点击了back
    void ClickBack();

public slots:
};

#endif // GAMESCENE_H
