#include "qx_td_delete_messages_request.h"

QxTdDeleteMessagesRequest::QxTdDeleteMessagesRequest(QObject *parent)
    : QxTdOkRequest(parent)
    , m_chatId(0)
    , m_revoke(true)
{
    // Intentionally left empty.
}

void QxTdDeleteMessagesRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QxTdDeleteMessagesRequest::setMessageIds(const QList<qint64> &messageIds)
{
    m_messageIds = messageIds;
}

void QxTdDeleteMessagesRequest::setRevoke(const bool value)
{
    m_revoke = value;
}

QJsonObject QxTdDeleteMessagesRequest::marshalJson()
{
    QJsonArray json_messages;
    for (auto &m_messageId : m_messageIds)
        json_messages.append(m_messageId);
    return QJsonObject{
        { "@type", "deleteMessages" },
        { "chat_id", m_chatId },
        { "message_ids", json_messages },
        { "revoke", m_revoke }
    };
}
