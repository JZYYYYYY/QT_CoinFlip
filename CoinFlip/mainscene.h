#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <QPainter>
#include <QDebug>
#include "chooselevelscene.h"
#include <QTimer>
#include <QSound>

namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = nullptr);

    //画背景图
    void paintEvent(QPaintEvent*);

    //初始化背景
    void initBg();

    //实现start按钮
    void startButton(QSound* startSound);

    ~MainScene();

    ChooseLevelScene* chooseLevelScene=nullptr;
private:
    Ui::MainScene *ui;
};

#endif // MAINSCENE_H
