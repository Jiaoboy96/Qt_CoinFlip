#include "mypushbutton.h"

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pix;
    bool ret = pix.load(this->normalImgPath);

    if(!ret)
    {
        qDebug() << "图片加载失败";
        return;
    }

    //设定图片大小
    this->setFixedSize(pix.width(),pix.height());

    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图片大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}

//向下跳跃
void MyPushButton::zoom1()
{
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");

    //设置时间间隔
    animation->setDuration(200);
    //设置动态对象起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置动画结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();

}

//向上跳跃
void MyPushButton::zoom2()
{
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");

    //设置时间间隔
    animation->setDuration(200);
    //设置动态对象起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置动画结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

//鼠标按下事件
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->pressImgPath);
        if(!ret)
        {
            qDebug() << "图片加载失败";
            return;
        }

        //设定图片大小
        this->setFixedSize(pix.width(),pix.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图片大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //其他事件交给父类
    QPushButton::mousePressEvent(e);
}

//鼠标松开事件
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        if(!ret)
        {
            qDebug() << "图片加载失败";
            return;
        }

        //设定图片大小
        this->setFixedSize(pix.width(),pix.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图片大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //其他事件交给父类
    QPushButton::mouseReleaseEvent(e);
}

