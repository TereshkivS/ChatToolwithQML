#include "tablemodel.h"
#include "socketreadwrite.h"

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent)
{
    //table.append({"1", "2", "3", 4});
}

int TableModel::rowCount(const QModelIndex &) const
{
    return table.size();
}

int TableModel::columnCount(const QModelIndex &) const
{
    return ColumnsCount - Qt::UserRole;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(index.row() >= table.size())
        return QVariant();

    ClientData temptable = table.at(index.row());
    switch (role)
    {
    case Domain:
        return QVariant(temptable.domain);
    case Host:
        return QVariant(temptable.host);
    case Username:
        return QVariant(temptable.username);
    case Poolingtime:
        return QVariant(temptable.poolingtime);
    default:
        return QVariant();
    }
    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Domain] = "DomainRole";
    roles[Host] = "HostRole";
    roles[Username] = "UsernameRole";
    roles[Poolingtime] = "PoolingtimeRole";
    return roles;
}

void TableModel::appendClientData(const ClientData& temptable)
{
    beginInsertRows(QModelIndex(), table.size(), table.size());
    table.append(temptable);
    endInsertRows();
}

void TableModel::removeClientData(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    table.removeAt(index);
    endRemoveRows();
}

void TableModel::appendDataFromQml(QString d, QString h, QString n, int p)
{
    appendClientData({d, h, n, p});
}

void TableModel::removeDataFromQml(QString usern)
{
    /*serach index of item, which has username = n*/
    QString name = Message::GetUserNameFromString(usern);
    int i = 0;
    for(; i < table.size() ; i++){
        if(table.at(i).username == name)
            break;
    }
    removeClientData(i);
}

