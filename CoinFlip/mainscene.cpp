#include "mainscene.h"
#include "ui_mainscene.h"
#include "mypushbutton.h"

MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //配置主场景
    initBg();

    //准备开始按钮的音效
    QSound* startSound=new QSound(":/res/TapButtonSound.wav",this);

    startButton(startSound);

    chooseLevelScene=new ChooseLevelScene;

    //监听选择关卡界面的back按钮的信号
    connect(chooseLevelScene,&ChooseLevelScene::ClickBack,[this](){
        QTimer::singleShot(250,this,[this](){
            this->setGeometry(chooseLevelScene->geometry());
            chooseLevelScene->hide();
            this->show();
        });
    });

}

void MainScene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画背景上图表
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}

void MainScene::initBg()
{
    //设置固定窗口大小
    this->setFixedSize(420,588);

    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("coin_flip_main_scene");

    //quit实现
    connect(ui->actionquit,&QAction::triggered,[this](){
        this->close();
    });
}

void MainScene::startButton(QSound* startSound)
{
    //start按钮
    MyPushButton* startBtn=new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    connect(startBtn,&QPushButton::clicked,[startBtn,this,startSound](){
        //播放开始按钮音效
        startSound->play();

        //按钮点击特效
        startBtn->zoom1();
        startBtn->zoom2();

        //延时操作
        QTimer::singleShot(450,this,[this](){
            //设置chooseLevelScene场景位置
            chooseLevelScene->setGeometry(this->geometry());

            //进入选择关卡场景
            this->hide();
            chooseLevelScene->show();
        });
    });
}

MainScene::~MainScene()
{
    delete ui;
}
