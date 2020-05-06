#include "chooselevelsence.h"

ChooseLevelSence::ChooseLevelSence(QWidget *parent) : QMainWindow(parent)
{

    //设置固定大小
    this->setFixedSize(320,588);

    //设置标题
    this->setWindowTitle("选择关卡");

    //设置图片
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //创建菜单栏
    QMenuBar * bar = menuBar();
    this->setMenuBar(bar);

    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");

    //创建菜单项
    QAction * quitAction = startMenu->addAction("退出");

    //点击退出按钮 实现退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //选择关卡按钮的音效
    QSound * chooseSound = new QSound(":/res/TapButtonSound.wav",this);
    //返回按钮的音效
    QSound * backSound = new QSound(":/res/BackButtonSound.wav",this);

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    connect(backBtn,&MyPushButton::clicked,[=](){
        //qDebug() << "返回主场景";
        //播放返回按钮的音效
        backSound->play();
        //延时发送返回按钮信号
        QTimer::singleShot(500,this,[=](){
            emit this->chooseSceneBack();
        });
    });

    playScene = NULL;


    //选择关卡按钮
    for(int i = 0; i < 20; i++)
    {

            MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
            menuBtn->setParent(this);
            menuBtn->move(25 + (i % 4) * 70, 130 + (i / 4) * 70);
            //menuBtn->setText("1");   //效果不好

            connect(menuBtn,&MyPushButton::clicked,[=](){
                //qDebug() << "你选择的是" << i+1 << "关";
                //播放点击关卡的音效
                chooseSound->play();

                //隐藏自身
                this->hide();

                //进入到具体的场景
                playScene = new PlayScene(i + 1);

                //将游戏场景的位置 设为 选择场景的位置
                playScene->setGeometry(this->geometry());
                playScene->show();

                connect(playScene,&PlayScene::chooseSceneBack,[=](){
                    //设置选择关卡的位置 为游戏场景的位置
                    this->setGeometry(playScene->geometry());
                    playScene->close();
                    delete playScene;
                    playScene = NULL;

                    this->show();
                });

            });

            QLabel * label = new QLabel(this);
            //设置标签大小
            label->setFixedSize(menuBtn->width(),menuBtn->height());
            //设置显示内容
            label->setText(QString::number(i+1));
            //设置位置
            label->move(25 + (i % 4) * 70, 130 + (i / 4) * 70);
            //设置水平位置
            label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

            //设置鼠标穿透
            label->setAttribute(Qt::WA_TransparentForMouseEvents);  //51
    }

}

void ChooseLevelSence::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //背景图片
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //设置标题
    pix.load(":/res/Title.png");
    //缩放
//    pix = pix.scaled(pix.width() * 0.5,pix.height() * 0.5);
    painter.drawPixmap((this->width() - pix.width()) * 0.5,30,pix);
}
