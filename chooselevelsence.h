#ifndef CHOOSELEVELSENCE_H
#define CHOOSELEVELSENCE_H

#include <QMainWindow>
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include "playscene.h"
#include <QSound>

class ChooseLevelSence : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelSence(QWidget *parent = nullptr);

    //重写绘图时间
    void paintEvent(QPaintEvent *event);


    //维护游戏场景的指针
    PlayScene * playScene;

signals:
    //自定义信号 只需要声明 不需要实现
    void chooseSceneBack();

public slots:
};

#endif // CHOOSELEVELSENCE_H
