#ifndef SERVICEMESSAGE_H
#define SERVICEMESSAGE_H

#include "message.h"

class ServiceMessage : public Message
{
public:
    QString FormMessage(QString, QString, QString, int);

    QString GetName() const;
    QString GetHost() const;
    QString GetDomain() const;
    int GetPoolingPeriod() const;

    void SetName(QString name);
    void SetHost(QString host);
    void SetDomain(QString domain);
    void SetPoolingPeriod(int period);
    static QString CannotConnetMessage();


    void ProcessRecievedMes(QString mes);

    static QString DisconnectMessage();

private:
    QString sendername;
    QString hostname;
    QString domainname;
    int poolingperiod;
};

#endif // SERVICEMESSAGE_H
