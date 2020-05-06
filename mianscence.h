#ifndef MIANSCENCE_H
#define MIANSCENCE_H

#include <QMainWindow>
#include "chooselevelsence.h"
#include <QSound>

namespace Ui {
class MianScence;
}

class MianScence : public QMainWindow
{
    Q_OBJECT

public:
    explicit MianScence(QWidget *parent = 0);
    ~MianScence();

    void paintEvent(QPaintEvent *event);

    ChooseLevelSence * chooseScence;

private:
    Ui::MianScence *ui;
};

#endif // MIANSCENCE_H
