#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QPixmap>
#include <QMessageBox>
#include <QString>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:

    MyCoin(QString CoinImg);

    int posX;  //X坐标
    int posY;  //Y坐标
    bool flag; //正反标志

    void changeFlag();  //执行反转效果
    QTimer * timer1;   //正面翻反面 定时器
    QTimer * timer2;   //反面翻正面 定时器
    int min = 1;  //最小图片
    int max = 8;  //最大图片

    //创建是否执行动画
    bool isAnimation;
    //鼠标按下事件
    void mousePressEvent(QMouseEvent *e);

    //是否胜利
    bool isWin;
signals:

public slots:
};

#endif // MYCOIN_H
