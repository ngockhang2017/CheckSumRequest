#include "mainwindow.h"
#include "ui_mainwindow.h"

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

//trong qt c++, cách tạo 100 request đến một địa chỉ và lắng nghe các response trả về. từ đó tính số lượng các request thành công và số lượng không
void MainWindow::on_pushButton_clicked()  //RUN
{
    this->str_URL = "http://" + ui->lineEdit_ip->text() + ":" + ui->lineEdit_port->text() + "/" + ui->lineEdit_path->text();
    this->number_of_thread = ui->lineEdit_threads->text().toInt();
    this->numberRamp = ui->lineEdit_rampup->text().toInt();//số lượng request tăng trong một thời gian rampup

//    for (int i = 0; i < number_of_thread; ++i)
//    {
//        WorkerThread *thread = new WorkerThread();
//        thread->timer_ramp_up = this->numberRamp;
//        thread->url_str = this->str_URL;

//        connect(thread->mRequestManager, &RequestManager::responseReceived, this, &MainWindow::Get_response_from_thread);
//        connect(thread->mRequestManager, &RequestManager::responseNon_Received, this, &MainWindow::Get_Non_response_from_thread);

//        connect(thread, &QThread::finished, thread, &QObject::deleteLater); // Clean up thread
//        thread->start();
//    }
    QList<WorkerThread *>listThreads;
    for (int i = 0; i < number_of_thread; ++i)
    {
        WorkerThread *thread = new WorkerThread();
        thread->timer_ramp_up = this->numberRamp;
        thread->url_str = "http://192.168.43.195:3030/fibonacci/12";// this->str_URL;

        connect(thread->mRequestManager, &RequestManager::responseReceived, this, &MainWindow::Get_response_from_thread);
        connect(thread->mRequestManager, &RequestManager::responseNon_Received, this, &MainWindow::Get_Non_response_from_thread);

        connect(thread, &QThread::finished, thread, &QObject::deleteLater); // Clean up thread
        thread->start();
        listThreads.append(thread);
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
