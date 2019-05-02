#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>

#include "client.h"
#include "servicemessage.h"
#include "usermessage.h"


class MainWindow : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString port READ getport WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString host READ gethost WRITE setHost NOTIFY hostChanged)
    Q_PROPERTY(QString username READ getusername WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(int pooltime READ getpooltime WRITE setPooltime NOTIFY pooltimeChanged)

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void setPort(const QString &a);
    QString getport() const;

    void setHost(const QString &a);
    QString gethost() const;

    void setUsername(const QString &a);
    QString getusername() const;

    void setPooltime(const int &a);
    int getpooltime() const;


public slots:
    void on_ConnectButton_clicked();

    void on_SendButton_clicked(bool anoncheckbox, QString input_message);

    void StopThread(QThread *);

signals:

    void portChanged();
    void hostChanged();
    void usernameChanged();
    void pooltimeChanged();

    void validSocket();
    void fillCharArea(QString tx);
    void changeConnectButton();


private:
    MyClient client;
    ServiceMessage SM;
    UserMessage UM;

    QString port;
    QString host;
    QString username;
    int pooltime;

};
#endif // MAINWINDOW_H
