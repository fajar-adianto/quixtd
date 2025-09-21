#include "qx_abstract_int64_id.h"
#include <QDebug>

QxAbstractInt64Id::QxAbstractInt64Id(QObject *parent)
    : QxTdObject(parent)
    , m_id(0)
{
    // Intentionally left empty.
}

qint64 QxAbstractInt64Id::id() const
{
    return m_id.value();
}

QString QxAbstractInt64Id::qmlId() const
{
    return m_id.toQmlValue();
}

QJsonValue QxAbstractInt64Id::jsonId() const
{
    return m_id.toJsonValue();
}

void QxAbstractInt64Id::unmarshalJson(const QJsonObject &json, const QString &id_key)
{
    QxTdObject::unmarshalJson(json);
    auto new_id = json[id_key].toVariant().toLongLong();
    if (m_id.value() != new_id) {
        m_id = new_id;
        emit idChanged(m_id.value());
    }
}

QxAbstractInt64Id *QxAbstractInt64Id::create(const QJsonObject &json, QObject *parent)
{
    auto *obj = new QxAbstractInt64Id(parent);
    obj->unmarshalJson(json);
    return obj;
}
