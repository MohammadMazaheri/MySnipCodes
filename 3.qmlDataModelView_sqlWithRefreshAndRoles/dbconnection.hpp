#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "sqlquerymodel.hpp"

class DbConnection: public QObject
{
    Q_OBJECT

public:
    DbConnection(QString dbFullName, QObject* parent = Q_NULLPTR): QObject(parent)
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName(dbFullName);
        m_sqlQuery = new QSqlQuery(m_db);
    }

    bool createDB()
    {
        QString query = "CREATE TABLE tblTest "
                        "(id integer PRIMARY KEY AUTOINCREMENT UNIQUE, "
                        "name nvarchar(50) UNIQUE, "
                        "value double, "
                        "isDeleted integer)";

        return execQuery(query);
    }

    bool execQuery(QString query)
    {
        if(connect())
            result = m_sqlQuery->exec(query);
        disconnect();
        return result;
    }

    void execQueryModel(QString query, SqlQueryModel *model)
    {
        if(connect())
            model->setQuery(query);
        disconnect();
    }


    QString getLastError()
    {
        return m_sqlQuery->lastError().text();
    }

private:
    QSqlDatabase m_db;
    QSqlQuery* m_sqlQuery;
    bool result;

    bool connect()
    {
        return m_db.open();
    }

    void disconnect()
    {
        if(m_db.open())
            m_db.close();
    }
};

#endif // DBCONNECTION_H
