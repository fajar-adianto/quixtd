#include "qx_td_formatted_text.h"
#include <QJsonArray>

QxTdFormattedText::QxTdFormattedText(QObject *parent)
    : QxTdObject(parent)
    , m_entities(nullptr)
{
    setType(FORMATTED_TEXT);
    m_entities = new QxTdObjectListModel<QxTdTextEntity>(this);
}

QString QxTdFormattedText::text() const
{
    return m_text;
}

QString QxTdFormattedText::oneLineText() const
{
    return m_oneLineText;
}

QxTdObjectListModel<QxTdTextEntity> *QxTdFormattedText::entities() const
{
    return m_entities;
}

QObject *QxTdFormattedText::qmlEntities() const
{
    return m_entities;
}

void QxTdFormattedText::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_text = json["text"].toString();
    emit textChanged();
    m_oneLineText = m_text;
    m_oneLineText.replace("\n", " ");
    const QJsonArray entities = json["entities"].toArray();
    for (const QJsonValue &value : entities) {
        auto *entity = new QxTdTextEntity();
        entity->unmarshalJson(value.toObject());
        m_entities->append(entity);
    }
    emit entitiesChanged();
}
