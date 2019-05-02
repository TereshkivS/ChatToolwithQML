#include "server.h"
#include "WinSock2.h"
#include "iostream"

#include "socketreadwrite.h"
#include "clientservice.h"

#include <QThread>
#include <QMutex>
#include <QDebug>

#include "tablemodel.h"


Server::Server(QObject *parent)
{

}

Server::~Server()
{
    qDebug() << "Stop server";
    ShutDownSockets();
}

int Server::CreateListenSocket(int port)
{
    /*to prevent 10093 socket error*/
    int iResult;
    WSADATA wsaData;
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);



    sockaddr_in serveraddr;
    int sock;

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock < 0)
    {
        qDebug() << "Socket creation failed ";

        return -1;
    }

    memset(&serveraddr, 0, sizeof(serveraddr));

    //fill address structure
    serveraddr.sin_family = AF_INET;
    /*Any hoss/IP available*/
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(port);

    if(bind(sock, (struct sockaddr*) & serveraddr, sizeof(serveraddr)) < 0)
    {
        qDebug() << "Binding failed";
        return -2;
    }

    if(listen(sock, SOMAXCONN) < 0)
    {
        qDebug() << "Cannot listen";
        return -3;
    }
    qDebug() << "Create socket";
    return sock;
}

int Server::Accept(int listensock)
{
    int client_socket1;
    sockaddr_in clientaddr;
    int clientaddrlen;

    clientaddrlen = sizeof(clientaddr);
    client_socket1 = accept(listensock, (struct sockaddr *)&clientaddr, &clientaddrlen);
    if(client_socket1 < 0)
    {
        qDebug() << "Cannot accept connection";
        return -1;
    }
    return client_socket1;
}

int Server::ShutDownSockets()
{
    SendMessageToAllClients(SM.DisconnectMessage());

    foreach (QThread* threaditer, threadPool) {
        threaditer->quit();
        threaditer->wait();
        delete threaditer;
    }
    return 0;
}

void Server::SendMessageToAllClients(QString msg)
{

    int k;
    char buff[BIG_MESSAGE];
    memset(buff, 0, BIG_MESSAGE);
    strcpy(buff, msg.toStdString().c_str());
    int lenbuf = strlen(buff);
    mutex.lock();
    foreach (int sock, sockets) {
       if( (k = Socketreaderwriter::write(sock, buff, lenbuf)) < 0 ){
            //disconnect socket
           // ...
            qDebug() << "Cannot send message to client " << sock;
        }
    }
    mutex.unlock();
}

void Server::StopThread(QThread * thread)
{
    thread->quit();

    mutex.lock();
    thread->wait();
    threadPool.removeAll(thread);
    //remove from userlist area
    // .....
    sockets.removeAll(client_socket);
    mutex.unlock();
    delete thread;

}

void Server::SetConnectionPort(int p)
{
    port = p;
}


void Server::CreateNetworkConnections()
{

    server_socket = CreateListenSocket(port);
    forever{
        client_socket = Accept(server_socket);
        memset(buf,0,sizeof(buf));
        Socketreaderwriter::read(client_socket, buf, 1000);

        //read poolling period from client
        SM.ProcessRecievedMes(QString(buf));

        int pool = SM.GetPoolingPeriod();
        QString domain = SM.GetDomain();
        QString host = SM.GetHost();
        QString name = SM.GetName();

        //fill in users
        emit sentDataToNetwork(domain, host, name, pool);

        QThread * userthread = new QThread(this);
        mutex.lock();
        sockets.append(client_socket);
        threadPool.append(userthread);
        mutex.unlock();

        //do socket non blocking
        u_long flags;
        ioctlsocket(client_socket, FIONBIO, &flags);


        ClientService * service = new ClientService(client_socket, buf, pool);
        QTimer * timer = new QTimer(0);
        timer->setInterval(200);

        //connect thread's death with socket close
        connect(userthread, SIGNAL(finished()), service, SLOT(ReleaseSocket()));
        connect(userthread, SIGNAL(finished()), service, SLOT(deleteLater()));
        service->moveToThread(userthread);
        timer->moveToThread(userthread);
        connect(userthread, SIGNAL(started()), timer, SLOT(start()));
        connect(timer, SIGNAL(timeout()), service, SLOT(UserService()));

        //connect(userthread, SIGNAL(finished()), timer, SLOT(stop()));// ????


        userthread->start();

        //fill in char area
        connect(service, SIGNAL(sentMessageClient(QString)), this, SIGNAL(sentMessageToNetwork(QString)), Qt::DirectConnection);

        //send mmessage on all clients
        connect(service, SIGNAL(sentMessageClient(QString)), this, SLOT(SendMessageToAllClients(QString)), Qt::DirectConnection);

        //remove user from userlist
        connect(service, SIGNAL(disconnect(QString)), this, SIGNAL(disconnectMessageToNetwork(QString)), Qt::DirectConnection);

        //kill userservice's thread
        connect(service, SIGNAL(finish(QThread*)), this, SLOT(StopThread(QThread*)));

    }

}
