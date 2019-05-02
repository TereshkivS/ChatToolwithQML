#include "service.h"
#include "socketreadwrite.h"
#include "servicemessage.h"
#include <QThread>
#include "WinSock2.h"


Service::Service(int sock, QObject *parent)
{
    client_socket = sock;
}

Service::~Service()
{

}

void Service::ReadingMessages()
{
    char temp_buf[BIG_MESSAGE];
    memset(temp_buf, 0, BIG_MESSAGE);
    if(Socketreaderwriter::read(client_socket, temp_buf, BIG_MESSAGE) >= 0){
        QString Buf(temp_buf);
        if(Buf == ServiceMessage::DisconnectMessage()){
            emit disconnectMessage();
            emit finish(QThread::currentThread());
        }
        else{
            emit recieveMessage(Buf);
        }
    }
}
