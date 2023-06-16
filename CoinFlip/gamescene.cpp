#include "gamescene.h"
#include "coin.h"
#include "dataconfig.h"

GameScene::GameScene(int levelNum)
    :levelIndex(levelNum)
{
    //初始化游戏场景
    initBg();

    //准备音效资源
    QSound* backSound=new QSound(":/res/BackButtonSound.wav");
    QSound* coinFlipSound=new QSound(":/res/ConFlipSound.wav");
    QSound* winSound=new QSound(":/res/LevelWinSound.wav");

    //实现back按钮
    backButton(backSound);

    //显示当前关卡数
    showLevel();

    dataConfig config;
    //给每个关卡的二维数组赋值
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->setGameArray(i,j,config.mData[this->getLevelIndex()][i][j]);
        }
    }

    //胜利图片创建
    QLabel* winLabel=setWinImg();

    //创建金币的背景图片
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            //绘制金/银币及其背景图片
            Coin* coin=setCoin(i,j);

            //点击金/银币，翻转
            connect(coin,&Coin::clicked,[coin,this,winLabel,coinFlipSound,winSound](){
                //实现翻转
                showFlip(coin,coinFlipSound);

                //判断是否胜利
                judge();

                //显示胜利动画和音效
                if(this->isWin==true)
                {
                    showWin(winSound,winLabel);
                }
            });
        }
    }

}

int GameScene::getLevelIndex()
{
    return levelIndex;
}

void GameScene::setGameArray(int i,int j,int value)
{
    gameArray[i][j]=value;
}

int GameScene::getGameArray(int i,int j)
{
    return gameArray[i][j];
}

void GameScene::setCoinBtn(int i,int j,Coin* coin)
{
    coinBtn[i][j]=coin;
}

Coin* GameScene::getCoinBtn(int i,int j)
{
    return coinBtn[i][j];
}

//画背景图
void GameScene::paintEvent(QPaintEvent*)
{
    //背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5-5,30,pix.width(),pix.height(),pix);
}

void GameScene::initBg()
{
    //设置固定窗口大小
    this->setFixedSize(420,588);

    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("game_scene");

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

void GameScene::backButton(QSound* backSound)
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

void GameScene::showLevel()
{
    //显示当前关卡数
    QLabel* label=new QLabel;
    label->setParent(this);
    //设置字体
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    //将字体放入标签控件中
    label->setFont(font);
    QString str1=QString("level:%1").arg(QString::number(this->getLevelIndex()));
    label->setText(str1);
    label->setGeometry(30,this->height()-60,120,50);
}

void GameScene::showWin(QSound *winSound, QLabel *winLabel)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            disconnect(this->getCoinBtn(i,j),nullptr,nullptr,nullptr);
        }
    }
    winSound->play();

    //将胜利图片移动下来
    QPropertyAnimation* animation=new QPropertyAnimation(winLabel,"geometry");
    //持续时间
    animation->setDuration(1000);
    //开始位置
    animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
    //结束位置
    animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
    //缓和曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void GameScene::showFlip(Coin* coin,QSound* coinFlipSound)
{
    coinFlipSound->play();
    coin->changeFlag();

    //翻转周围金/银币
    //右侧金/银币翻转条件
    if(coin->getPosX()+1<=3)
    {
        Coin* co4=this->getCoinBtn(coin->getPosX()+1,coin->getPosY());
        co4->changeFlag();
    }
    //左侧金/银币翻转条件
    if(coin->getPosX()-1>=0)
    {
        Coin* co1=this->getCoinBtn(coin->getPosX()-1,coin->getPosY());
        co1->changeFlag();
    }
    //上侧金/银币翻转条件
    if(coin->getPosY()-1>=0)
    {
        Coin* co2=this->getCoinBtn(coin->getPosX(),coin->getPosY()-1);
        co2->changeFlag();
    }
    //下侧金/银币翻转条件
    if(coin->getPosY()+1<=3)
    {
        Coin* co3=this->getCoinBtn(coin->getPosX(),coin->getPosY()+1);
        co3->changeFlag();
    }
}

void GameScene::judge()
{
    this->isWin=true;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(this->getCoinBtn(i,j)->getFlag()==false)
            {
                this->isWin=false;
                break;
            }
        }
    }
}

Coin* GameScene::setCoin(int i,int j)
{
    //绘制背景图片
    QPixmap pix=QPixmap(":/res/BoardNode.png");
    QLabel* label=new QLabel;
    label->setGeometry(0,0,pix.width(),pix.height());
    label->setPixmap(pix);
    label->setParent(this);
    label->move(95+i*60,200+j*60);

    //创建金/银币
    QString str;
    if(this->getGameArray(i,j)==1)
    {
        //显示金币
        str=":/res/Coin0001.png";
    }
    else
    {
        //显示银币
        str=":/res/Coin0008.png";
    }

    Coin* coin=new Coin(str);
    coin->setParent(label);
    coin->move(2,4);

    //给金/银币属性赋值
    coin->setPosX(i);
    coin->setPosY(j);
    coin->setFlag(this->getGameArray(i,j)); //1正面，0反面

    //维护金/银币
    this->setCoinBtn(coin->getPosX(),coin->getPosY(),coin);

    return coin;
}

QLabel* GameScene::setWinImg()
{
    QLabel* winLabel=new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());

    return winLabel;
}
