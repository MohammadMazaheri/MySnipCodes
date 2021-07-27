#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include "dbconnection.hpp"

class DbInterface: public QObject
{
    Q_OBJECT

    Q_PROPERTY(SqlQueryModel* model READ model WRITE setModel NOTIFY modelChanged)

public:
    explicit DbInterface(QString dbFullName, QQmlApplicationEngine* engine, QObject* parent = Q_NULLPTR): QObject(parent)
      ,m_engine(engine)
    {
        m_dbConnection = new DbConnection(dbFullName, parent);

        if (m_dbConnection->createDB())
            qDebug()<<"DB is created";
        else
            qDebug()<<"DB is existed";

        m_model = new SqlQueryModel;
    }

    ~DbInterface()
    {
        delete m_model;
        delete m_dbConnection;
    }

    SqlQueryModel* model() const
    {
        return m_model;
    }

    void setModel(SqlQueryModel*& model)
    {
        m_model = model;
        emit modelChanged();
    }

private:
    DbConnection* m_dbConnection;
    SqlQueryModel* m_model;
    QString m_query;
    QQmlApplicationEngine* m_engine;

    const QString kTtableName = "tblTest";

Q_SIGNALS:
    void modelChanged();

//public Q_SLOTS:
public slots:
    bool update(const int &id, const QString &name = "", const qreal &value = 0.0, const int &isDeleted = 0)
    {
        m_query = QString("UPDATE %1 SET name = '%2', value = '%3', isDeleted = '%4' WHERE id = %5")
                .arg(kTtableName).arg(name).arg(value).arg(isDeleted).arg(id);
        return m_dbConnection->execQuery(m_query);
    }

    bool append(const QString &name = "", const qreal &value = 0.0)
    {
        m_query = QString("SELECT * FROM %1 WHERE name = '%2'").arg(kTtableName).arg(name);
        m_dbConnection->execQueryModel(m_query, m_model);
        if(m_model->rowCount() > 0 && m_model->record(0).value("isDeleted").toInt() != 0)
            return update(m_model->record(0).value("id").toInt(), name, value, 0);
        else
        {
            m_query = QString("INSERT INTO %1 (name, value, isDeleted) VALUES('%2', '%3', 0)")
                    .arg(kTtableName).arg(name).arg(value);
            return m_dbConnection->execQuery(m_query);
        }
    }

    bool remove(const int &id)
    {
        //m_query = QString("DELETE FROM %1 WHERE id = '%2'").arg(kTtableName).arg(id);
        m_query = QString("UPDATE %1 SET isDeleted = 1 WHERE id = %2").arg(kTtableName).arg(id);
        return m_dbConnection->execQuery(m_query);
    }

    QString getLastError()
    {
        return m_dbConnection->getLastError();
    }

    void refresh(QString query)
    {
        m_dbConnection->execQueryModel(query, m_model);
        m_engine->rootContext()->setContextProperty("sqlModel", QVariant::fromValue(this->model()));
    }
};

#endif // DBINTERFACE_H
