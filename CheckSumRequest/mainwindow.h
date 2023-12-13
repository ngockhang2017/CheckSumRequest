#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<workerthread.h>
#include<requestmanager.h>
#include<QDebug>
#include<QFont>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void ReciverReport( QString response);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString str_URL;
    int number_of_thread, numberRamp;
};
#endif // MAINWINDOW_H
