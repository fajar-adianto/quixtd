#include "qx_td_text_entity.h"

QxTdTextEntity::QxTdTextEntity(QObject *parent)
    : QxTdObject(parent)
    , m_offset(0)
    , m_length(0)
    , m_type(nullptr)
{
    setType(TEXT_ENTITY);
}

qint32 QxTdTextEntity::offset() const
{
    return m_offset;
}

qint32 QxTdTextEntity::length() const
{
    return m_length;
}

QxTdTextEntityType *QxTdTextEntity::entityType() const
{
    return m_type.get();
}

void QxTdTextEntity::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_offset = qint32(json["offset"].toInt());
    m_length = qint32(json["length"].toInt());
    m_type.reset(QxTdTextEntityFactory::create(json["type"].toObject(), this));
    emit entityChanged();
}
