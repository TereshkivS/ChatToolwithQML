#include "mainwindow.h"
#include "socketreadwrite.h"
#include "service.h"
#include "servicemessage.h"

#include <QTimer>
#include <QThread>
#include <QHostInfo>


MainWindow::MainWindow(QWidget *parent)
{

}

MainWindow::~MainWindow()
{
    int socket = client.getExistingSocket();
    char buf[SMALL_MESSAGE];
    strcpy(buf, SM.DisconnectMessage().toStdString().c_str());
    int buflen = strlen(buf);
    Socketreaderwriter::write(socket, buf, buflen);
    if(-1 == shutdown(socket, SD_BOTH)){
        qDebug() << "Cannot shutdown socket";
    }
    closesocket(socket);
}

void MainWindow::setPort(const QString &a)
{
    if (a != port) {
        port = a;
        emit portChanged();
    }
}

QString MainWindow::getport() const
{
    return port;
}

void MainWindow::setHost(const QString &a)
{
    if (a != host) {
        host = a;
        emit hostChanged();
    }
}

QString MainWindow::gethost() const
{
    return host;
}

void MainWindow::setUsername(const QString &a)
{
    if (a != username) {
        username = a;
        emit usernameChanged();
    }
}

QString MainWindow::getusername() const
{
    return username;
}

void MainWindow::setPooltime(const int &a)
{
    if (a != pooltime) {
        pooltime = a;
        emit pooltimeChanged();
    }
}

int MainWindow::getpooltime() const
{
    return pooltime;
}

void MainWindow::on_ConnectButton_clicked()
{
    int socket;
    char buf[BIG_MESSAGE];

    SM.SetName(getusername());
    SM.SetHost(QHostInfo::localHostName());
    SM.SetDomain(QHostInfo::localDomainName());
    SM.SetPoolingPeriod(getpooltime());
    UM.SetSenderName(getusername());

    client.CreateConnectSocket(getport().toInt(),
                               gethost().toStdString().c_str());

    socket = client.getExistingSocket();
    if(socket > 0)
        emit validSocket();
    else{
        return;
    }

    strcpy(buf, SM.FormMessage(SM.GetName(),
                               SM.GetHost(),
                               SM.GetDomain(),
                               SM.GetPoolingPeriod()).toStdString().c_str());

    //send first message about client
    int buflen = strlen(buf);
    Socketreaderwriter::write(socket, buf, buflen);

    //create thread responsible for reading data from the server
    QThread* readingthread = new QThread;
    Service* service = new Service(socket);
    QTimer * timer = new QTimer(0);
    timer->setInterval(SM.GetPoolingPeriod());
    service->moveToThread(readingthread);
    timer->moveToThread(readingthread);
    connect(readingthread, SIGNAL(started()), timer, SLOT(start()));
    connect(timer, SIGNAL(timeout()), service, SLOT(ReadingMessages()));
    connect(readingthread, SIGNAL(finished()), timer, SLOT(stop()));       // ???
    readingthread->start();

    //add new messages to char area
    connect(service, SIGNAL(recieveMessage(QString)), this, SIGNAL(fillCharArea(QString)));
    //if connection is broken, set 'connect' button enabled again
    connect(service, SIGNAL(disconnectMessage()), this, SIGNAL(changeConnectButton()));
    //kill readingthread
    connect(service, SIGNAL(finish(QThread*)), this, SLOT(StopThread(QThread*)));

}

void MainWindow::on_SendButton_clicked(bool anoncheckbox, QString input_message)
{
    char buf[BIG_MESSAGE];
    memset(buf, 0, BIG_MESSAGE);
    if(!anoncheckbox){
        UM.FormMessage(UM.GetSenderName(), input_message);

        strcpy(buf, UM.GetBuffer().toStdString().c_str());
        int lenbuf = strlen(buf);

        if(Socketreaderwriter::write(client.getExistingSocket(), buf, lenbuf) < 0)
            qDebug() << "Cannot send message ";
    }
    else{
        UM.FormMessage("Anonymous", input_message);

        strcpy(buf, UM.GetBuffer().toStdString().c_str());
        int lenbuf = strlen(buf);

        if(Socketreaderwriter::write(client.getExistingSocket(), buf, lenbuf) < 0)
            qDebug() << "Cannot send message ";
    }

}


void MainWindow::StopThread(QThread * thread)
{
    thread->quit();
    thread->wait();

    delete thread;
}
