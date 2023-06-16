#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QPainter>
#include <QLabel>
#include <QDebug>
#include "gamescene.h"
#include <QTimer>
#include <QSound>

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    //画背景图
    void paintEvent(QPaintEvent*);

    //初始化背景
    void initBg();

    //实现back按钮
    void backButton(QSound* backSound);

    //创建选择关卡按钮
    void setLevelButton(QSound* chooseLevelSound);

    //监听进入游戏事件
    void enterGame(QSound* chooseLevelSound,MyPushButton* menuBtn,int i);

    //游戏场景对象指针
    GameScene* gameScene=nullptr;

signals:
    //自定义信号，表示点击了back
    void ClickBack();

public slots:
};

#endif // CHOOSELEVELSCENE_H
