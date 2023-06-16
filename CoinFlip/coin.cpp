#include "coin.h"

Coin::Coin(QString btnImg)
{
    //初始化背景和背景图片
    initBg(btnImg);

    //初始化计时器
    timer1=new QTimer(this);
    timer2=new QTimer(this);

    //连接监听信号和翻转槽函数,并执行槽函数
    connectSignalAndFlip();
}

void Coin::setPosX(int x)
{
    posX=x;
}

void Coin::setPosY(int y)
{
    posY=y;
}

void Coin::setFlag(bool st)
{
    flag=st;
}

int Coin::getPosX()
{
    return posX;
}

int Coin::getPosY()
{
    return posY;
}

bool Coin::getFlag()
{
    return flag;
}

void Coin::initBg(QString btnImg) //初始化背景和背景图片
{
    QPixmap pix;
    bool res=pix.load(btnImg);
    if(!res)
    {
        QString str=QString("图片%1加载失败").arg(btnImg);
        qDebug()<<str;
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
}

void Coin::changeFlag() //改变flag
{
    //如果是正面，翻成反面
    if(this->flag)
    {
        //开启定时器1
        timer1->start(30);
        this->flag=false;
    }
    else ////如果是反面，翻成正面
    {
        //开启定时器2
        timer2->start(30);
        this->flag=true;
    }
}

void Coin::connectSignalAndFlip() //连接监听信号和翻转槽函数,并执行槽函数
{
    //监听正面翻反面的信号，并翻转
    connect(timer1,&QTimer::timeout,[this](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //翻转结束
        if(this->min>this->max)
        {
            this->min=1;
            timer1->stop();
        }
    });

    //监听反面翻正面的信号，并翻转
    connect(timer2,&QTimer::timeout,[this](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //翻转结束
        if(this->max<this->min)
        {
            this->max=8;
            timer2->stop();
        }
    });
}
