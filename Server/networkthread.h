#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H

#include "network.h"
#include <QThread>

class NetworkThread : public QThread{
    Q_OBJECT
public:
    NetworkThread(Server & n) : _n(n)
    {

    }

public:
    void run() override{
        _n.CreateNetworkConnections();
    }


private:
    Server& _n;
};


#endif // NETWORKTHREAD_H
