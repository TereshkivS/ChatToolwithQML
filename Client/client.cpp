#include "client.h"
#include <QDebug>
#include "WinSock2.h"
#include "socketreadwrite.h"

MyClient::MyClient(QObject *parent)
{

}

MyClient::~MyClient()
{
    //DiscSocket();
}

int MyClient::CreateConnectSocket(int port, const char *addr)
{
    /*to prevent 10093 socket error*/
    int iResult;
    WSADATA wsaData;
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    struct sockaddr_in serveraddr;

    if ((connectsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        qDebug() << "Socket createion falied";
        return -1;
    }

    memset(&serveraddr, 0, sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;

    serveraddr.sin_addr.s_addr = inet_addr(addr);
    serveraddr.sin_port = htons(port);

    int rez;

    if(::connect(connectsocket, (struct sockaddr *)&serveraddr, sizeof serveraddr) < 0)
    {
        qDebug() << WSAGetLastError();
        closesocket(connectsocket);
        qDebug("Cannot connect to server");
        connectsocket = -3;
        return -3;
    }
    qDebug() << "Create socket !!";

    return connectsocket;
}

int MyClient::getExistingSocket()
{
    return connectsocket;
}
