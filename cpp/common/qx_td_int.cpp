#include "qx_td_int.h"

QJsonValue QxTdInt32::toJsonValue() const
{
    return QJsonValue{ int(_value) };
}

QString QxTdInt32::toQmlValue() const
{
    return QString::number(_value);
}

qint32 QxTdInt32::value() const
{
    return _value;
}

QJsonValue QxTdInt53::toJsonValue() const
{
    return QJsonValue{ double(_value) };
}

QString QxTdInt53::toQmlValue() const
{
    return QString::number(_value);
}

qint64 QxTdInt53::value() const
{
    return _value;
}

QJsonValue QxTdInt64::toJsonValue() const
{
    return QJsonValue{ QString::number(_value) };
}

QString QxTdInt64::toQmlValue() const
{
    return QString::number(_value);
}

qint64 QxTdInt64::value() const
{
    return _value;
}
