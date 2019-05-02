#ifndef CLIENTSERVICE_H
#define CLIENTSERVICE_H


#include <QObject>
#include <QTimer>
#include "usermessage.h"
#include "servicemessage.h"

class ClientService : public QObject {
    Q_OBJECT
public:
    ClientService(int clsock, char * name, int pperiod, QObject * parent = 0);
    ~ClientService();


public slots:
    void UserService();

    void ReleaseSocket();

signals:
    void sentMessageClient(QString);
    void disconnect(QString);
    void finish(QThread *);



private:
    int client_socket;
    char username[50];
    int polling_period;


};

#endif // CLIENTSERVICE_H
