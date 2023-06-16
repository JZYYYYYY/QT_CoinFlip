#include "chooselevelscene.h"
#include "mypushbutton.h"

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //初始化背景
    initBg();

    //准备音效
    QSound* chooseLevelSound=new QSound(":/res/TapButtonSound.wav");
    QSound* backSound=new QSound(":/res/BackButtonSound.wav");

    //back按钮
    backButton(backSound);

    //创建选择关卡的按钮
    setLevelButton(chooseLevelSound);
}

//画背景图
void ChooseLevelScene::paintEvent(QPaintEvent*)
{
    //背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5-5,30,pix.width(),pix.height(),pix);
}

void ChooseLevelScene::initBg()
{
    //设置固定窗口大小
    this->setFixedSize(420,588);

    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("choose_level_scene");

    //创建菜单栏
    QMenuBar* bar=menuBar();
    setMenuBar(bar);

    QMenu* startMenu=bar->addMenu("begin");
    QAction* quitAction=startMenu->addAction("quit");

    //实现quit
    connect(quitAction,&QAction::triggered,[this](){
        this->close();
    });
}

void ChooseLevelScene::backButton(QSound* backSound)
{
    //back按钮
    MyPushButton* backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //实现back
    connect(backBtn,&MyPushButton::clicked,[this,backSound](){
        backSound->play();
        this->ClickBack();
    });
}

void ChooseLevelScene::enterGame(QSound* chooseLevelSound,MyPushButton* menuBtn,int i)
{
    //监听每个按钮的点击事件
    connect(menuBtn,&MyPushButton::clicked,[=](){
        //播放选择关卡音效
        chooseLevelSound->play();

        //进入游戏场景
        this->hide();
        gameScene=new GameScene(i+1);
        //设置gameScene位置
        gameScene->setGeometry(this->geometry());
        gameScene->show();

        connect(gameScene,&GameScene::ClickBack,[this](){
            QTimer::singleShot(250,this,[this](){
                this->setGeometry(gameScene->geometry());
                this->show();
                delete gameScene;
                gameScene=nullptr;
            });
        });
    });
}

void ChooseLevelScene::setLevelButton(QSound* chooseLevelSound)
{
    //创建选择关卡的按钮
    for(int i=0;i<20;i++)
    {
        //空按钮图表
        MyPushButton* menuBtn=new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(60+i%4*80,130+i/4*80);

        enterGame(chooseLevelSound,menuBtn,i);

        //文字
        QLabel* label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(60+i%4*80,130+i/4*80);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        //设置使鼠标可穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}
