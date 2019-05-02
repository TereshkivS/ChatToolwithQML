#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QMutex>
#include "clientservice.h"
#include "usermessage.h"
#include "servicemessage.h"

class Server : public QObject {
    Q_OBJECT
public:
    Server(QObject * parent = 0);
    ~Server();


    int CreateListenSocket(int port);
    int Accept(int listensock);
    void SetConnectionPort(int);

public slots:
    void CreateNetworkConnections();
    int ShutDownSockets();
    void SendMessageToAllClients(QString);
    void StopThread(QThread *);



signals:
    void sentDataToNetwork(QString, QString, QString, int);
    void sentMessageToNetwork(QString);
    void disconnectMessageToNetwork(QString);



private:
    int server_socket;
    int client_socket;
    QList<QThread* > threadPool;
    QList<int> sockets;
    char buf[1000];
    int port;

    UserMessage UM;
    ServiceMessage SM;

    QMutex mutex;

};


#endif // SERVER_H
