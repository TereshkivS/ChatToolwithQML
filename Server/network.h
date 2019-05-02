#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QDebug>
#include "server.h"

class Network : public QObject
{
    Q_OBJECT
    //messageChanged emmited when does WRITE setMessage.
    //and all bindings involving the message property is updated by READ message
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)

public:
    Network();

public slots: // slots are public methods available in QML
    void start_button(QString port);

signals:
     void messageChanged();
     //d-domain, h-host, n-username, p-pooling time
     void sentData(QString d, QString h, QString n, int p);
     //t - text
     void sentMessage(QString t);
     //n-username
     void disconnect(QString n);

    public:
     QString message() const;
     void setMessage(const QString& value);

    private:
     QString m_message;
     Server server;


};

#endif // NETWORK_H
