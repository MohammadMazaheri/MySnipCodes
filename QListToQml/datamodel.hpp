#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>

class DataModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(qreal latitude READ latitude WRITE setLatitude NOTIFY latitudeChanged)
    Q_PROPERTY(qreal longitude READ longitude WRITE setLongitude NOTIFY longitudeChanged)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)

public:
    DataModel(const QString &name = "", const qreal latitude = 0.0
              , const qreal longitude = 0.0, const QString &color = "white", QObject *parent=nullptr): QObject(parent)
      , m_name(name)
      , m_latitude(latitude)
      , m_longitude(longitude)
      , m_color(color) {}

    QString name() const
    {
        return m_name;
    }
    void setName(const QString &name)
    {
        m_name = name;
        emit nameChanged();
    }

    qreal latitude() const
    {
        return m_latitude;
    }
    void setLatitude(const qreal latitude)
    {
        m_latitude = latitude;
        emit latitudeChanged();
    }

    qreal longitude() const
    {
        return m_longitude;
    }
    void setLongitude(const qreal longitude)
    {
        m_longitude = longitude;
        emit longitudeChanged();
    }

    QString color() const
    {
        return m_color;
    }
    void setColor(const QString &color)
    {
        if (color != m_color) {
            m_color = color;
            emit colorChanged();
        }
    }

    Q_INVOKABLE QObject* getObject()
    {
        return this;
    }

signals:
    void nameChanged();
    void latitudeChanged();
    void longitudeChanged();
    void colorChanged();

private:
    QString m_name;
    qreal m_latitude;
    qreal m_longitude;
    QString m_color;
};

#endif // DATAMODEL_H
