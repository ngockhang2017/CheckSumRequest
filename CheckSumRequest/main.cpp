#include "mainwindow.h"
#include <QCoreApplication>
#include <Windows.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    CoInitialize(nullptr);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
