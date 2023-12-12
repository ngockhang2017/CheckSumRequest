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

    RequestManager *requestManager = new RequestManager();
    //    connect(&requestManager, SIGNAL(responseReceived(const QString &response)), this, SLOT(ReciverReport(const QString &response)) );
    // Gửi một số request
    //    requestManager->sendRequest("http://192.168.179.195:3030/");
    for(int i = 1 ; i <= 100 ; ++i)
    {
        requestManager->sendRequest("http://192.168.179.195:3030/fibonacci_NodeJs/" + QString::number(i));
    }

    connect(requestManager, SIGNAL(responseReceived(QString ) ), this, SLOT(ReciverReport(QString ) ));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReciverReport( QString response)
{
    qDebug() << "Response <<< " << response << endl;
    ui->textEdit->append(response);
}
//trong qt c++, cách tạo 100 request đến một địa chỉ và lắng nghe các response trả về. từ đó tính số lượng các request thành công và số lượng không
