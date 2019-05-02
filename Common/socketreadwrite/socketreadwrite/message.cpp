#include "message.h"
#include <QStringList>

QString Message::GetMessageContent() const
{
    return mescontent;
}

QString Message::GetBuffer() const
{

    return buff;
}

void Message::AddToFront(QString& mainbuf, const char * tempbuf)
{
    mainbuf.insert(0, tempbuf);
}

QString Message::GetUserNameFromString(QString str)
{
    QStringList list = str.split("#");
    return list.first();
}
