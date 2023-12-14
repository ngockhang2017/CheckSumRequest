#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<workerthread.h>
#include<requestmanager.h>
#include<QDebug>
#include<QFont>
#include <Windows.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString getCPUInfo();
public slots:
    void on_pushButton_clicked();
    void Get_response_from_thread(QString str);
    void Get_Non_response_from_thread(QString str);

private:
    Ui::MainWindow *ui;
    QString str_URL;
    int number_of_thread, numberRamp;
};
#endif // MAINWINDOW_H
