#include "mycoin.h"

MyCoin::MyCoin(QString CoinImg)
{
    QPixmap pix;
    bool ret = pix.load(CoinImg);

    if(!ret)
    {
        QString str = QString("图片加载失败 %1").arg(CoinImg);
        QMessageBox::critical(this,"加载失败",str);
        return;
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //初始化按钮是否执行动画
    this->isAnimation = false;

    //初始化没有胜利
    this->isWin = false;

    //监听定时器
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //如果显示到 最后一张 停止定时器
        if(this->min > this->max)
        {
            this->min = 1;
            this->isAnimation = false;
            timer1->stop();
        }
    });

    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%8.png").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //如果显示到 最后一张 停止定时器
        if(this->max < this->min)
        {
            this->max = 8;
            this->isAnimation = false;
            timer2->stop();
        }
    });
}


void MyCoin::changeFlag()  //执行反转效果
{
    if(this->flag)
    {
        //开启 正面 翻 反面的定时器
        timer1->start(30);
        this->flag = false;
    }
    else
    {
        //开启 反面 翻 正面的定时器
        timer2->start(30);
        this->flag = true;
    }
}

//鼠标按下事件
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation || this->isWin)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}
