#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include "client.h"

class MyClient : public QObject{
    Q_OBJECT

public:
    MyClient(QObject* parent = 0);
    ~MyClient();

    int CreateConnectSocket(int port, const char * addr);
    int getExistingSocket();


private:
    int connectsocket;
};

#endif // CLIENT_H
