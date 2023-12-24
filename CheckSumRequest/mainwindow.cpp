#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // http://192.168.100.26:3000/fibonacci?number=13
    str_URL = "http://" + ui->lineEdit_ip->text() + ":" + ui->lineEdit_port->text() + ui->lineEdit_path->text();
    qDebug() << "URL---" << str_URL << endl;
    this->number_of_thread = ui->lineEdit_threads->text().toInt();
    this->numberRamp = ui->lineEdit_rampup->text().toInt();
    this->numberLoop = ui->lineEdit_loop->text().toUInt();

    timer_for_rps = new QTimer();
    connect(timer_for_rps, SIGNAL(timeout()), this, SLOT(Calculate_RPS()));
    timer_for_rps->start(1000);
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

void MainWindow::on_pushButton_clicked()  //RUN
{
    this->Sussecc_Counter = 0;
    this->Fail_Counter = 0;
    str_URL = "http://" + ui->lineEdit_ip->text() + ":" + ui->lineEdit_port->text() + ui->lineEdit_path->text();
    this->number_of_thread = ui->lineEdit_threads->text().toInt();
    this->numberRamp = ui->lineEdit_rampup->text().toInt();
    this->numberLoop = ui->lineEdit_loop->text().toUInt();

    //------------------------------
    const int numberOfThreads = this->number_of_thread;
    //        QString url = "http://192.168.100.26:3000/fibonacci?number=15";
    QString url = this->str_URL;
    QList<WorkerThread*> threads;
    QString infor;
    int step_timer = (this->numberRamp*1000) / numberOfThreads;
    if(step_timer == 0) step_timer = 1;//1ms
    ui->label_numberThr->setText("CPU THREADS:   " + QString::number(this->number_of_thread) + "   Threads");

    for (int i = 0; i < numberOfThreads; ++i)
    {
        WorkerThread *thread = new WorkerThread(url);
        // Get the current thread ID
        Qt::HANDLE threadId = thread->currentThreadId();
        QString threadIdString = QString::number(reinterpret_cast<quintptr>(threadId));
        QString threadIdString_2 = QString::number(reinterpret_cast<qulonglong>(threadId));
        qDebug() << "STR: "<< threadIdString;
        qDebug() << "STR_2: "<< threadIdString_2;

        connect(thread, &WorkerThread::success, this, &MainWindow::Get_response_from_thread);
        connect(thread, &WorkerThread::fail, this, &MainWindow::Get_Non_response_from_thread);
        ui->textEdit->append(infor);
        threads.append(thread);
        thread->start();

        //        ui->textEdit->append(getCPUInfo());
        ui->label_numberof_processor->setText(getCPUInfo());
        ui->label_suss_fail->setText("Success: " + QString::number(this->Sussecc_Counter) + " ---- Fail: " + QString::number(this->Fail_Counter));

    }

    for (WorkerThread *thread : threads) {
        thread->wait();
        thread->deleteLater();
    }
}

void MainWindow::Get_response_from_thread(QString str, int rtt)
{
    this->Sussecc_Counter += 1;
    ui->label_suss_fail->setText("Success: " + QString::number(this->Sussecc_Counter) + " ---- Fail: " + QString::number(this->Fail_Counter));
    Error_resual = (Fail_Counter/(Fail_Counter+Sussecc_Counter))*100;
    // Đặt màu chữ
    QPalette palette1;
    if(Error_resual == 0.0) palette1.setColor(QPalette::Text, Qt::green);
    else palette1.setColor(QPalette::Text, Qt::red);
    ui->label_error->setPalette(palette1);
    ui->label_error->setText("ERROR [%]:  " + QString::number(this->Error_resual) +"   %");

    // Đặt màu chữ
    QPalette palette;
    palette.setColor(QPalette::Text, Qt::green);
    ui->textEdit->setPalette(palette);
    ui->textEdit->append("Request success: " + str);

    Sum_Rtt += rtt;
    ui->label_RTT->setText("ROUND TRIP TIME [RTT]:     " + QString::number(Sum_Rtt/Sussecc_Counter)   +"  milisecond");
}

void MainWindow::Get_Non_response_from_thread(QString str)
{
    this->Fail_Counter += 1;
    ui->label_suss_fail->setText("Success: " + QString::number(this->Sussecc_Counter) + " ---- Fail: " + QString::number(this->Fail_Counter));
    Error_resual = (Fail_Counter/(Fail_Counter+Sussecc_Counter))*100;
    // Đặt màu chữ
    QPalette palette1;
    if(Error_resual == 0.0) palette1.setColor(QPalette::Text, Qt::green);
    else palette1.setColor(QPalette::Text, Qt::red);
    ui->label_error->setPalette(palette1);
    ui->label_error->setText("ERROR [%]:  " + QString::number(this->Error_resual) +"   %");

    // Đặt màu chữ
    QPalette palette;
    palette.setColor(QPalette::Text, Qt::red);
    ui->textEdit->setPalette(palette);
    ui->textEdit->append("Request fail: "+str);
}

void MainWindow::Calculate_RPS()
{
    this->request_per_second = Sussecc_Counter/numberRamp;
    ui->label_rps->setText("REQUEST PER SECOND [RPS]:   " + QString::number(request_per_second) + "  request");
}
