#include "playscene.h"

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int index)
{

    //保存本关 关卡号
    this->leaveIndex = index;

    //设置固定大小
    this->setFixedSize(320,588);

    //设置标题
    this->setWindowTitle("翻金币场景");

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

    //默认未胜利
    this->isWin = false;
    //qDebug() << "打开了" << index << "关";

    //翻金币的音效
    QSound * flipSound = new QSound(":/res/ConFlipSound.wav",this);
    //胜利的音效
    QSound * winSound = new QSound(":/res/LevelWinSound.wav",this);
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


    //显示具体的关卡号
    QLabel * label = new QLabel;
    label->setParent(this);
    QString str = QString("Leave: %1").arg(this->leaveIndex);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);

    //让label使用上面的字体
    label->setFont(font);

    label->setText(str);
    //设置位置和大小
    label->setGeometry(QRect(30,this->height() - 50,140,50));

    dataConfig data;
    //初始化二维数组
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
           this->gameArray[i][j] = data.mData[this->leaveIndex][i][j];
        }
    }

    //创建胜利的图片
    QLabel * winLabel = new QLabel;
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(QRect(0,0,pix.width(),pix.height()));
    winLabel->setParent(this);
    winLabel->setPixmap(pix);

    winLabel->move((this->width() - pix.width()) * 0.5, -pix.height());

    //创建金币的背景图片
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            //QLabel显示图片
            QLabel * bg = new QLabel(this);
            QPixmap pix;
            pix.load(":/res/BoardNode.png");
            //设置位置和大小
            bg->setGeometry(57 + i * 50, 200 + j * 50,pix.width(),pix.height());
            bg->setPixmap(pix);

//            bg->move(57 + i * 50, 200 + j * 50);

            QString str;
            if(this->gameArray[i][j] == 1)
            {
                //创建金币
                str = ":/res/Coin0001.png";
            }
            else
            {
                //创建银币
                str = ":/res/Coin0008.png";
            }
            MyCoin * coin = new MyCoin(str);
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];
            coin->setParent(this);
            coin->move(59 + i * 50, 204 + j * 50);

            //将创建的coin放到数组中
            coinBtn[i][j] = coin;

            connect(coin,&MyCoin::clicked,[=](){
                //播放翻金币的音效
                flipSound->play();
                //点击后，先将所有的按钮禁用，不能点击
                //PlayScene里面的isWin --- 判断整个游戏是否胜利
                //MyCoin里面的isWin属性 ---目的时为了游戏胜利后不可再次点击
                for(int i = 0; i < 4; i++)
                {
                    for(int j = 0; j < 4; j++)
                    {
                        coinBtn[i][j]->isWin = true;
                    }
                }

                coin->changeFlag();

                //同步内部维护的二维数组
                gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0;

                //继续翻动周围的硬币
                //右侧
                if(coin->posX + 1 <= 3)
                {
                    coinBtn[coin->posX + 1][coin->posY]->changeFlag();
                    gameArray[coin->posX + 1][coin->posY] = gameArray[coin->posX + 1][coin->posY] == 0 ? 1 : 0;
                }
                //左侧
                if(coin->posX - 1 >= 0)
                {
                    coinBtn[coin->posX - 1][coin->posY]->changeFlag();
                    gameArray[coin->posX - 1][coin->posY] = gameArray[coin->posX - 1][coin->posY] == 0 ? 1 : 0;
                }
                //下侧
                if(coin->posY + 1 <= 3)
                {
                    coinBtn[coin->posX][coin->posY + 1]->changeFlag();
                    gameArray[coin->posX][coin->posY + 1] = gameArray[coin->posX][coin->posY + 1] == 0 ? 1 : 0;
                }
                //上侧
                if(coin->posY - 1 >= 0)
                {
                    coinBtn[coin->posX][coin->posY - 1]->changeFlag();
                    gameArray[coin->posX][coin->posY - 1] = gameArray[coin->posX][coin->posY - 1] == 0 ? 1 : 0;
                }

                //翻完所有硬币后 将所有硬币解禁
                for(int i = 0; i < 4; i++)
                {
                    for(int j = 0; j < 4; j++)
                    {
                        coinBtn[i][j]->isWin = false;
                    }
                }

                //翻完金币判断是否胜利
                this->isWin = true;
                for(int i = 0; i < 4; i++)
                {
                    for(int j = 0; j < 4; j++)
                    {
                        if(coinBtn[i][j]->flag == false)
                        {
                            this->isWin = false;
                            break;
                        }
                    }
                }

                if(this->isWin == true)
                {
                    //播放胜利的音效
                    winSound->play();
                    //将所有硬币胜利标志设为true
                    for(int i = 0; i < 4; i++)
                    {
                        for(int j = 0; j < 4; j++)
                        {
                            coinBtn[i][j]->isWin = true;
                        }
                    }

                    //将胜利的图片显示出来
                    QPropertyAnimation * animation = new QPropertyAnimation(winLabel,"geometry");
                    animation->setDuration(1000);
                    animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                    animation->setEndValue(QRect(winLabel->x(),winLabel->y() + 114,winLabel->width(),winLabel->height()));
                    animation->setEasingCurve(QEasingCurve::OutBounce);
                    animation->start();
                }
            });

        }
    }
}

//重写绘图事件
void PlayScene::paintEvent(QPaintEvent *event)
{
    //绘制背景图片
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //绘制标题
    pix.load(":/res/Title.png");
    //缩放
    pix = pix.scaled(pix.width() * 0.5,pix.height() * 0.5);
    painter.drawPixmap(10,30,pix);


}
