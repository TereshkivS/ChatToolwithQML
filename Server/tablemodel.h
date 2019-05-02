#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>

struct ClientData
{
    QString domain;
    QString host;
    QString username;
    int poolingtime;

    friend bool operator == (const ClientData& lhs, const ClientData& rhs)
    {
        if(lhs.domain != rhs.domain)
            return false;
        if(lhs.host != rhs.host)
            return false;
        if(lhs.username != rhs.username)
            return false;
        if(lhs.poolingtime != rhs.poolingtime)
            return false;
        return true;
    }
};

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
    enum Role{
        Domain = Qt::UserRole,
        Host,
        Username,
        Poolingtime,
        ColumnsCount
    };
public:
    explicit TableModel(QObject *parent = nullptr);

public:

    int rowCount(const QModelIndex & = QModelIndex()) const override;

    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    //bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    void appendClientData(const ClientData& data);

    void removeClientData(int index);


public slots:
    void appendDataFromQml(QString d, QString h, QString n, int p);

    void removeDataFromQml(QString usern);

private:
    QList<ClientData> table;
};

#endif // TABLEMODEL_H
