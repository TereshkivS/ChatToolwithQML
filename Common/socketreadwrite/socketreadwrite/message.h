#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>

#define SMALL_MESSAGE 100
#define BIG_MESSAGE 1500

class Message{
public:
    QString GetMessageContent() const;
    QString GetBuffer() const;
    static void AddToFront(QString&, const char *);
    static QString GetUserNameFromString(QString);

protected:
    QString buff;
    QString mescontent;

};

#endif // MESSAGE_H
