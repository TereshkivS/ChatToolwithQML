#ifndef SOCKETREADWRITE_H
#define SOCKETREADWRITE_H


#include <WinSock2.h>
#include <QDebug>
#include <QHostInfo>

#include "usermessage.h"

enum SendState
{
   ANON_MES = 0,
   NOT_ANON_MES
};

class Socketreaderwriter
{

public:
    Socketreaderwriter();

    static int read(int so, char buf[], int l)
    {
        int res = recv(so, buf, l, 0);
        return res;
    }

    static int write(int so, const char buf[], int l)
    {
        int i = send(so, buf, l, 0);
        if (i==0)
        {
            //qDebug() << "Can't write to socket, connection is closed";
            //exit(1);
        }
        return i;
    }

    static const char * formfirstmessage(const char * username, const char * pollperiod)
    {
        QString _domain = QHostInfo::localDomainName();
        QString _host = QHostInfo::localHostName();
        QString result = _domain + " " + _host + " " + QString(username) + " " + QString(pollperiod);
        char localbuf[100];
        strcpy(localbuf, result.toStdString().c_str());
        return localbuf;
    }

    static void sendmessagetoserver(QString mes, QString name, int sock, SendState state)
    {
        char result[1100];
        QString temp("(");
        if(state == NOT_ANON_MES)
            temp.append(name);
        else if(state == ANON_MES)
            temp.append("Anonymous");

        temp.append("):\t");

        temp.append(mes);

        strcpy(result, temp.toStdString().c_str());
        int bufsize = strlen(result);

        if(write(sock, result, bufsize) < 0)
            qDebug() << "Cannot send message:(";

    }

    static int getpollperiod(const char * mes)
    {
        QString poll(strrchr(mes, ' '));
        return poll.toInt();
    }

//    static const char * getmessagefromclient(const char * mes)
//    {
//        char result[1000];
//        char *p = strstr(mes, ".)");
//        p = p + 2;
//        strncpy(result, p, strstr(p, "(.") - p);
//        return result;
//    }

//    static const char * getnamefromclient(const char * mes)
//    {
//        char result[100];
//        strncpy(result, mes, strstr(mes, "(.") - mes);
//        return result;
//    }
};

#endif // SOCKETREADWRITE_H
