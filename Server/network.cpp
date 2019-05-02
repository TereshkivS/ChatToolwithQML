#include "network.h"
#include "networkthread.h"
#include "tablemodel.h"
#include <QDebug>

Network::Network() : m_message("")
{
    connect(&server, SIGNAL(sentDataToNetwork(QString,QString,QString,int)), this, SIGNAL(sentData(QString,QString,QString,int)));
    connect(&server, SIGNAL(sentMessageToNetwork(QString)), this, SIGNAL(sentMessage(QString)));
    connect(&server, SIGNAL(disconnectMessageToNetwork(QString)), this, SIGNAL(disconnect(QString)));
}

void Network::start_button(QString port){
    server.SetConnectionPort(port.toInt());
    NetworkThread* N= new NetworkThread(server);
    connect(N, SIGNAL(finished()), N, SLOT(deleteLater()));
    N->start();
}

QString Network::message() const {
    return m_message;
}

void Network::setMessage(const QString& value) {
    if(m_message != value) {
        m_message = value;
        messageChanged(); // trigger signal of property change
    }
}
