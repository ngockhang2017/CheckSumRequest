#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getCPUInfo() {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    return QString("Number of Processors: %1").arg(sysInfo.dwNumberOfProcessors);
}

//trong qt c++, cách tạo 100 request đến một địa chỉ và lắng nghe các response trả về. từ đó tính số lượng các request thành công và số lượng không
void MainWindow::on_pushButton_clicked()  //RUN
{
    const int numberOfThreads = 50;
    QString url = "http://192.168.43.50:3000/fibonacci?number=20";
    QList<WorkerThread*> threads;
    QString infor;
    for (int i = 0; i < numberOfThreads; ++i)
    {
//        ui->textEdit->append("infor");
        WorkerThread *thread = new WorkerThread(url);
        QObject::connect(thread, &WorkerThread::success, [=](const QString& str)
        {
            qDebug() << "Thread" << thread->currentThreadId() << "Success:" << str;
//            ui->textEdit->append(str);
        });
        QObject::connect(thread, &WorkerThread::fail, [=](const QString& str) {
            qDebug() << "Thread" << thread->currentThreadId() << "Fail:" << str;
        });
        ui->textEdit->append(infor);
        threads.append(thread);
        thread->start();

        ui->textEdit->append(getCPUInfo());

    }

    for (WorkerThread *thread : threads) {
        thread->wait();
        thread->deleteLater();
    }
}

void MainWindow::Get_response_from_thread(QString str)
{
    ui->textEdit->append(str);
}

void MainWindow::Get_Non_response_from_thread(QString str)
{
    ui->textEdit->append(str);
}
