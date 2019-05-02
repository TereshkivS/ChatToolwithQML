#include "servicemessage.h"
#include <QStringList>

QString ServiceMessage::FormMessage(QString sname, QString hname, QString dname, int period)
{
    buff.append(sname);
    buff.append("#");
    buff.append(hname);
    buff.append("#");
    buff.append(dname);
    buff.append("#");
    buff.append(QString::number(period));
    return buff;
}

QString ServiceMessage::GetName() const
{
    return sendername;
}

QString ServiceMessage::GetHost() const
{
    return hostname;
}

QString ServiceMessage::GetDomain() const
{
    return domainname;
}

int ServiceMessage::GetPoolingPeriod() const
{
    return poolingperiod;
}

void ServiceMessage::SetName(QString name)
{
    sendername = name;
}

void ServiceMessage::SetHost(QString host)
{
    hostname = host;
}

void ServiceMessage::SetDomain(QString domain)
{
    domainname = domain;
}

void ServiceMessage::SetPoolingPeriod(int period)
{
    poolingperiod = period;
}

QString ServiceMessage::CannotConnetMessage()
{
    return QString("Cannot connect to server");
}

void ServiceMessage::ProcessRecievedMes(QString mes)
{
    QStringList components = mes.split("#");
    sendername = components.first();
    components.pop_front();
    hostname = components.first();
    components.pop_front();
    domainname = components.first();
    components.pop_front();
    poolingperiod = components.first().toInt();
    components.pop_front();
}

QString ServiceMessage::DisconnectMessage()
{
    return QString("#disconnect");
}
