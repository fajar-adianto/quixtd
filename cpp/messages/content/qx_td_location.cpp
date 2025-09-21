#include "qx_td_location.h"

QxTdLocation::QxTdLocation(QObject *parent)
    : QxTdObject(parent)
    , m_latitude(0)
    , m_longitude(0)
{
    setType(TEXT_ENTITY);
}

double QxTdLocation::latitude() const
{
    return m_latitude;
}

void QxTdLocation::setLatitude(const double value)
{
    m_latitude = value;
}

double QxTdLocation::longitude() const
{
    return m_longitude;
}

void QxTdLocation::setLongitude(const double value)
{
    m_longitude = value;
}

void QxTdLocation::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_latitude = double(json["latitude"].toDouble());
    m_longitude = double(json["longitude"].toDouble());
    emit entityChanged();
}

QJsonObject QxTdLocation::marshalJson()
{
    return QJsonObject{
        { "latitude", m_latitude },
        { "longitude", m_longitude }
    };
}
