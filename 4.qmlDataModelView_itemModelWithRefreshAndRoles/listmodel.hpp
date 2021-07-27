#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include "listmodeltype.h"

class ListModel: public QObject
{
    Q_OBJECT

    Q_PROPERTY(ListModelType* model READ model WRITE setModel NOTIFY modelChanged)

public:
    explicit ListModel(QObject* parent = Q_NULLPTR): QObject(parent)
    {
        m_model = new ListModelType(this);
        connect(m_model, SIGNAL(dataChanged(const QModelIndex, const QModelIndex, const QVector<int>)), this, SLOT(onDataChanged(const QModelIndex, const QModelIndex, const QVector<int>)));
    }

    ~ListModel()
    {
        delete m_model;
    }

    ListModelType* model() const
    {
        return m_model;
    }

    void setModel(ListModelType*& model)
    {
        m_model = model;
    }

private:
    ListModelType* m_model;

Q_SIGNALS:
    void modelChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());

private Q_SLOTS:
    void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>())
    {
        emit modelChanged(topLeft, bottomRight, roles);
    }

public Q_SLOTS:
    void append(const QString &name = "", const qreal &value = 0.0)
    {
        QVariantList list {name, value};
        m_model->insert(m_model->rowCount(), qvariant_cast<QVariantList>(list));
    }

    void insert(const int &index = 0, const QString &name = "", const qreal &value = 0.0)
    {
        QVariantList list {name, value};
        m_model->insert(index, qvariant_cast<QVariantList>(list));
    }

    void update(const int &index, const QString &name = "", const qreal &value = 0.0)
    {
        QVariantList list {name, value};
        m_model->update(index, qvariant_cast<QVariantList>(list));
    }

    void replace(const QList<QVariantList> &data)
    {
        m_model->replace(data);
    }

    void remove(const int &index)
    {
        m_model->remove(index);
    }

    void clear()
    {
        m_model->clear();
    }
};

#endif // LISTMODEL_H
