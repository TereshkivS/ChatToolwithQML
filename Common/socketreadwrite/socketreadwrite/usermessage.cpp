#include "usermessage.h"
#include <QStringList>
#include <QString>

UserMessage::UserMessage(QString mes)
{
    mescontent = mes;
}

QString UserMessage::FormMessage(QString name, QString cont)
{
    buff = name;
    buff.append(":  ");
    buff.append(cont);
    return buff;
}


void UserMessage::ProcessRecievedMes(QString mes)
{
    QStringList components = mes.split(":  ");
    sendername = components.first();
    mescontent = components.back();
}

QString UserMessage::GetSenderName() const
{
    return sendername;
}

void UserMessage::SetSenderName(QString nm)
{
    sendername = nm;
}
