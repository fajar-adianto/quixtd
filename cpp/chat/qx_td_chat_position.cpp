#include "qx_td_chat_position.h"
#include "qx_td_chat_type_factory.h"

QxTdChatPosition::QxTdChatPosition(QObject *parent)
    : QxTdObject(parent)
    , m_list(nullptr)
    , m_order(0)
    , m_isPinned(false)
{
    // Intentionally left empty.
}

QxTdChatList *QxTdChatPosition::list() const
{
    return m_list.get();
}

QString QxTdChatPosition::qmlOrder() const
{
    return m_order.toQmlValue();
}

qint64 QxTdChatPosition::order() const
{
    return m_order.value();
}
bool QxTdChatPosition::isPinned() const
{
    return m_isPinned;
}

void QxTdChatPosition::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_order = json["order"].toVariant().toLongLong();
    m_isPinned = json["is_pinned"].toBool();
    m_list.reset(QxTdChatFactory::createList(json["list"].toObject(), this));
    m_list->unmarshalJson(json["list"].toObject());
}
