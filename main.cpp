#include "mianscence.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MianScence w;
    w.show();

    return a.exec();
}
