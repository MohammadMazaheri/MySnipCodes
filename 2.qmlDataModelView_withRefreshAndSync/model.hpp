#ifndef MODEL_H
#define MODEL_H

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "modeltype.hpp"

class Model : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject*> dataList READ dataList WRITE setDataList NOTIFY dataListChanged)

public:
    Model(QQmlApplicationEngine* engine, QObject *parent=nullptr): QObject(parent)
      ,m_engine(engine){}

    QList<QObject*> dataList() const
    {
        return m_model;
    }

    void setDataList(const QList<QObject*> &dataList)
    {
        m_model = dataList;
        emit dataListChanged();
    }

private:
    QList<QObject*> m_model {};
    QQmlApplicationEngine* m_engine;

signals:
    void dataListChanged();

public slots:
    bool append(const QString &name = "", const qreal latitude = 0.0, const qreal longitude = 0.0, const QString &color = "white")
    {
        int count = m_model.count();
        m_model.append(new ModelType(name, latitude, longitude, color));
        if (m_model.count() > count)
        {
            refresh();
            return true;
        }
        else
            return false;
    }

    bool update(const int &id, const QString &name = "", const qreal latitude = 0.0, const qreal longitude = 0.0, const QString &color = "white")
    {
        if (id < 0 || id > m_model.count() - 1)
            return false;

        static_cast<ModelType*>(m_model[id])->setName(name);
        static_cast<ModelType*>(m_model[id])->setLatitude(latitude);
        static_cast<ModelType*>(m_model[id])->setLongitude(longitude);
        static_cast<ModelType*>(m_model[id])->setColor(color);

        refresh();
        return true;
    }

    bool remove(const int &id)
    {
        if (id < 0 || id > m_model.count() - 1)
            return false;

        int count = m_model.count();
        m_model.removeAt(id);
        if (m_model.count() < count)
        {
            refresh();
            return true;
        }
        else
            return false;
    }

    bool remove(int index, int count)
    {
        if (index < 0 || index > m_model.count() - 1)
            return false;

        if (count < 1)
            return false;

        if (count > m_model.count() - index)
            count = m_model.count() - index;

        for (int i = index; i < index + count; i++)
            m_model.removeAt(i);

        refresh();
        return true;
    }

    int count()
    {
        return m_model.count();
    }

    bool clear()
    {
        for (int i = 0; i < m_model.count(); i++)
            m_model.removeAt(i);

        refresh();
        return true;
    }

    void refresh()
    {
        m_engine->rootContext()->setContextProperty("modelList", QVariant::fromValue(this->dataList()));
    }
};

#endif // MODEL_H
