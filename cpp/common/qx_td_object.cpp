#include "qx_td_object.h"

QxTdObject::QxTdObject(QObject *parent)
    : QObject(parent)
    , m_type(UNKNOWN)
{
    // Intentionally left empty.
}

QxTdObject::Type QxTdObject::type() const
{
    return m_type;
}

QString QxTdObject::typeString() const
{
    return m_typeString;
}

void QxTdObject::unmarshalJson(const QJsonObject &json)
{
    m_typeString = json["@type"].toString();
}

QJsonObject QxTdObject::marshalJson()
{
    return QJsonObject();
}

void QxTdObject::setType(const QxTdObject::Type type)
{
    m_type = type;
    emit typeChanged(m_type);
}
