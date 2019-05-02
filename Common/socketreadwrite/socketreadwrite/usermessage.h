#ifndef USERMESSAGE_H
#define USERMESSAGE_H


#include "message.h"

class  UserMessage : public Message
{

public:
    UserMessage(QString mes = "0");


    QString FormMessage(QString, QString);
    void ProcessRecievedMes(QString);

    QString GetSenderName() const;
    void SetSenderName(QString nm);

 private:
    QString sendername;
};

#endif // USERMESSAGE_H
