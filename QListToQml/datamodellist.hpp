#ifndef DATAMODELLIST_H
#define DATAMODELLIST_H

#include <QObject>

class DataModelList : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList strList READ strList WRITE setStrList NOTIFY strListChanged)

public:
    DataModelList(const QStringList &strList, QObject *parent=nullptr): QObject(parent)
      , m_strList(strList) {}

    QStringList strList() const
    {
        return m_strList;
    }
    void setStrList(const QStringList &strList)
    {
        m_strList = strList;
        emit strListChanged();
    }

private:
    QStringList m_strList;

signals:
    void strListChanged();

public slots:
    QStringList getList()
    {
        return m_strList;
    }

    int getListCount()
    {
        return m_strList.count();
    }
};

#endif // DATAMODELLIST_H
