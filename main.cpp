#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font  = a .font();
    font.setPointSize(10);
    a.setFont(QFont("微软雅黑",9));

    MainWindow w;
    w.show();

    return a.exec();
}
