#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i < 3; ++i) {
        WorkerThread *thread = new WorkerThread();
        connect(thread, &QThread::finished, thread, &QObject::deleteLater); // Clean up thread
        thread->start();
    }

    RequestManager requestManager;
//    connect(&requestManager, SIGNAL(responseReceived(const QString &response)), this, SLOT(ReciverReport(const QString &response)) );
    // Gửi một số request
    requestManager.sendRequest("https://reqres.in/api/users/2");
    requestManager.sendRequest("https://jsonplaceholder.typicode.com/posts/2");

//     Kết nối tín hiệu để xử lý response
           QObject::connect(&requestManager, &RequestManager::responseReceived, [](const QString &response) {
               qDebug() << "Received response:" << response;
           });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReciverReport(const QString &response)
{
    qDebug() << "Response <<< " << response << endl;
}

