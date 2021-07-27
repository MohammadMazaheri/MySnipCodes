#include "listmodeltype.h"

QVector<qint32> ListModelType::roleKeys {};
QVector<QString> ListModelType::roleValues {};

ListModelType::ListModelType(QObject* parent): QAbstractListModel(parent)
{
    m_fieldNames.append("name");
    m_fieldNames.append("value");
    roleNames();
}

QHash<int, QByteArray> ListModelType::roleNames() const
{
    QHash<int, QByteArray > roles;
    for (int i = 0; i < m_fieldNames.count(); i++)
    {
        int key = QString::number((roles.insert(Qt::UserRole + i + 1, m_fieldNames[i].toUtf8())).key()).toInt();
        QString value = roles.find(key).value();
        if (roleKeys.indexOf(key) < 0)
            roleKeys.append(key);
        if (roleValues.indexOf(value) < 0)
            roleValues.append(value);
    }
    return roles;
}

int ListModelType::rowCount(const QModelIndex &) const
{
    return m_data.count();
}

int ListModelType::colCount() const
{
    return m_fieldNames.count();
}

QStringList ListModelType::fieldNames() const
{
    return m_fieldNames;
}

QVariant ListModelType::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= rowCount())
        return QVariant();

    int col = roleKeys.indexOf(role);
    QVariantList list = m_data.value(index.row());
    QVariant value = list.value(col);
    return value;
}

QVariant ListModelType::data(int row, const QString &fieldName) const
{
    int key = roleValues.indexOf(fieldName);
    QModelIndex index = createIndex(row, roleKeys[key]);
    return data(index, roleKeys[key]);
}

void ListModelType::insert(const int index, const QVariantList &data)
{
    if (index < 0) return;
    int row = index;
    if (row > rowCount())
        row = rowCount();

    beginInsertRows(QModelIndex(), row, row);
    endInsertRows();
    m_data.insert(row, data);

    callDataChanged();
}

void ListModelType::replace(const QList<QVariantList> &data)
{
    clear();
    beginInsertRows(QModelIndex(), 0, data.count());
    endInsertRows();
    m_data.append(data);

    callDataChanged();
}

void ListModelType::update(const int index, const QVariantList &data)
{
    if (index < 0 || index >= rowCount()) return;

    m_data.replace(index, data);

    callDataChanged();
}

void ListModelType::remove(const int index)
{
    if (index < 0 || index >= rowCount()) return;

    beginRemoveRows(QModelIndex(), index, index);
    endRemoveRows();
    m_data.removeAt(index);

    callDataChanged();
}

void ListModelType::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    endRemoveRows();
    m_data.clear();

    callDataChanged();
}

void ListModelType::callDataChanged()
{
    QModelIndex index1 = createIndex(0, 0);
    QModelIndex index2 = createIndex(rowCount() - 1, m_fieldNames.count());
    emit dataChanged(index1, index2, roleKeys);
}
