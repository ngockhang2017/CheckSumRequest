#include "workerthread.h"

WorkerThread::WorkerThread()
{

}

void WorkerThread::run() {

    for (int i = 0; i < 5; ++i) {
        qDebug() << "Thread" << currentThreadId() << "Working" << i;
        sleep(1); // Simulate work
    }
}
