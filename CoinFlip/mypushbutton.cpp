#include "mypushbutton.h"

MyPushButton::MyPushButton(QString normalImg,QString pressImg)
    :
      normalImgPath(normalImg),
      pressImgPath(pressImg)
{
    QPixmap pix;
    bool res=pix.load(normalImg);
    if(!res)
    {
        qDebug() << "图片加载失败";
    }

    this->setFixedSize(pix.width(),pix.height());

    this->setStyleSheet("QPushButton{border:0px;}");

    this->setIcon(pix);

    this->setIconSize(pix.size());
}

void MyPushButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation* animation=new QPropertyAnimation(this,"geometry");
    //设置动画间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}

void MyPushButton::zoom2()
{
    //创建动画对象
    QPropertyAnimation* animation=new QPropertyAnimation(this,"geometry");
    //设置动画间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent* e)
{
    if(this->pressImgPath!="")
    {
        QPixmap pix;
        bool res=pix.load(this->pressImgPath);
        if(!res)
        {
            qDebug() << "图片加载失败";
        }

        this->setFixedSize(pix.width(),pix.height());

        this->setStyleSheet("QPushButton{border:0px;}");

        this->setIcon(pix);

        this->setIconSize(pix.size());
    }

    //让父类执行其他内容
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent* e)
{
    if(this->pressImgPath!="")
    {
        QPixmap pix;
        bool res=pix.load(this->normalImgPath);
        if(!res)
        {
            qDebug() << "图片加载失败";
        }

        this->setFixedSize(pix.width(),pix.height());

        this->setStyleSheet("QPushButton{border:0px;}");

        this->setIcon(pix);

        this->setIconSize(pix.size());
    }

    //让父类执行其他内容
    return QPushButton::mouseReleaseEvent(e);
}
