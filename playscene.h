#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include "mycoin.h"
#include "dataconfig.h"
#include <QPropertyAnimation>
#include <QSound>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int index);

    //重写绘图事件
    void paintEvent(QPaintEvent *event);

    //关卡号
    int leaveIndex;

    //游戏二维数组 维护里面金币或者银币
    int gameArray[4][4];

    //金币按钮数组
    MyCoin * coinBtn[4][4];

    //是否胜利
    bool isWin;

signals:
    void chooseSceneBack();

public slots:
};

#endif // PLAYSCENE_H
