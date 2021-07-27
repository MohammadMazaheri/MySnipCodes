#ifndef SQLQUERYMODEL_H
#define SQLQUERYMODEL_H

#include <QSqlQueryModel>
#include <QSqlRecord>

class SqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT
    Q_PROPERTY(QStringList fieldNames READ fieldNames)
public:
    using QSqlQueryModel::QSqlQueryModel;
    QHash<int, QByteArray> roleNames() const
    {
        QHash<int, QByteArray> roles;
        for (int i = 0; i < record().count(); i ++)
             roles.insert(Qt::UserRole + i + 1, record().fieldName(i).toUtf8());
        return roles;
    }

    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const
    {
        QVariant value;
        if (index.isValid())
        {
            if (role < Qt::UserRole)
            {
                value = QSqlQueryModel::data(index, role);
            }
            else
            {
                int columnIdx = role - Qt::UserRole - 1;
                QModelIndex modelIndex = this->index(index.row(), columnIdx);
                value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
            }
        }
        return value;
    }

    Q_INVOKABLE QVariant data(int row, const QString & fieldName)
    {
        int col = record().indexOf(fieldName);
        if(col != -1 && 0 <= row && row < rowCount())
        {
            QModelIndex ix = index(row, col);
            return ix.data();
        }
        return QVariant();
    }

    QStringList fieldNames() const
    {
        QStringList names;
        for (int i = 0; i < record().count(); i ++)
            names << record().fieldName(i);
        return names;
    }
};


#endif // SQLQUERYMODEL_H
