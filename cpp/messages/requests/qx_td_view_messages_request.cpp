#include "qx_td_view_messages_request.h"

QxTdViewMessagesRequest::QxTdViewMessagesRequest(QObject *parent)
    : QxTdOkRequest(parent)
    , m_chatId(0)
{
    // Intentionally left empty.
}

void QxTdViewMessagesRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QxTdViewMessagesRequest::setMessageIds(const QList<qint64> &messageIds)
{
    m_messageIds = messageIds;
}

QJsonObject QxTdViewMessagesRequest::marshalJson()
{
    QJsonArray json_messages;
    for (auto &m_messageId : m_messageIds)
        json_messages.append(m_messageId);
    return QJsonObject{
        { "@type", "viewMessages" },
        { "chat_id", m_chatId },
        { "message_ids", json_messages },
        { "force_read", false }
    };
}
