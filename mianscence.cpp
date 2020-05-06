#include "mianscence.h"
#include "ui_mianscence.h"
#include <QPainter>
#include <QTimer>
#include "mypushbutton.h"

MianScence::MianScence(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MianScence)
{
    ui->setupUi(this);

    //点击开始-退出 退出游戏
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //设置固定大小
    this->setFixedSize(320,588);

    //设置标题
    this->setWindowTitle("翻金币游戏");

    //设置图片
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //开始按钮
    MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.7);

    //准备出开始按钮的音效
    QSound * startSound = new QSound(":/res/TapButtonSound.wav",this);
    //startSound->setLoops(-1); //设置循环次数  -1是无线循环

    //创建出 第二个选择关卡场景
    chooseScence = new ChooseLevelSence;

    //监听第二个选择场景返回按钮发出的信号
    connect(chooseScence,&ChooseLevelSence::chooseSceneBack,[=](){
        //选择关卡隐藏
        chooseScence->hide();
        //自身位置设为 关卡场景位置
        this->setGeometry(chooseScence->geometry());
        //自身显示
        this->show();
    });

    connect(startBtn,&MyPushButton::clicked,this,[=](){
        //qDebug() << "点击按钮";
        //播放开始按钮
        startSound->play();
        //点击开始按钮，执行弹跳效果
        startBtn->zoom1();
        startBtn->zoom2();

        //延时
        QTimer::singleShot(500,this,[=](){
            //将自身隐藏
            this->hide();

            //设置选中关卡场景的位置
            chooseScence->setGeometry(this->geometry());

            //进入第二个 选择关卡场景中
            chooseScence->show();
        });


    });
}

void MianScence::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //背景图片
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //设置标题
    pix.load(":/res/Title.png");
    //缩放
    pix = pix.scaled(pix.width() * 0.5,pix.height() * 0.5);
    painter.drawPixmap(10,30,pix);

}

MianScence::~MianScence()
{
    delete ui;
}
