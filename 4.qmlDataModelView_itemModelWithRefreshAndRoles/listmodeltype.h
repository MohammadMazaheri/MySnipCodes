#ifndef LISTMODELTYPE_H
#define LISTMODELTYPE_H

#include <QAbstractListModel>
#include <QDebug>

class ListModelType : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int rowCount READ rowCount)
    Q_PROPERTY(int colCount READ colCount)
    Q_PROPERTY(QStringList fieldNames READ fieldNames)

public:
    static QVector<qint32> roleKeys;
    static QVector<QString> roleValues;

    explicit ListModelType(QObject* parent = Q_NULLPTR);

    QHash<int, QByteArray> roleNames() const override;

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int colCount() const;
    QStringList fieldNames() const;

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const override;
    Q_INVOKABLE QVariant data(int row, const QString &fieldName) const;

    Q_INVOKABLE void insert(const int index, const QVariantList &data);
    Q_INVOKABLE void replace(const QList<QVariantList> &data);
    Q_INVOKABLE void update(const int index, const QVariantList &data);
    Q_INVOKABLE void remove(const int index);
    Q_INVOKABLE void clear();

private:
    QStringList m_fieldNames {};
    QList<QVariantList> m_data {};

    void callDataChanged();
};

#endif // LISTMODELTYPE_H
