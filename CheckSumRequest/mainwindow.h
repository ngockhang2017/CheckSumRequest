#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<workerthread.h>
#include<requestmanager.h>
#include<QDebug>
#include<QFont>
#include <Windows.h>
#include<QPalette>
#include<QTimer>

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
    void Get_response_from_thread(QString str, int rtt);
    void Get_Non_response_from_thread(QString str);
    void Calculate_RPS();

private:
    Ui::MainWindow *ui;
    QString str_URL;
    int number_of_thread, numberRamp, numberLoop;

    int request_per_second = 0;
    QTimer *timer_for_rps;
    int Sussecc_Counter = 0;
    int Fail_Counter = 0;
    double Error_resual = 0.0;
    int Sum_Rtt = 0, RTT = 0;
};
#endif // MAINWINDOW_H
