#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QDebug>
#include <QPropertyAnimation>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);

    MyPushButton(QString normalImg, QString pressImg = "");

    //向上跳跃
    void zoom1();
    //向下跳跃
    void zoom2();

    //鼠标按下事件
    void mousePressEvent(QMouseEvent *e);
    //鼠标松开事件
    void mouseReleaseEvent(QMouseEvent *e);


    QString normalImgPath;  //默认显示图片路径
    QString pressImgPath;  //按下显示图片路径

signals:

public slots:
};

#endif // MYPUSHBUTTON_H
