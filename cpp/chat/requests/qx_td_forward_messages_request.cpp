#include "qx_td_forward_messages_request.h"
#include "client/qx_td_client.h"

QxTdForwardMessagesRequest::QxTdForwardMessagesRequest(QObject *parent)
    : QxTdRequest(parent)
    , m_chatId(0)
    , m_fromChatId(0)
    , m_messageIds(QList<qint64>())
{
    // Intentionally left empty.
}

void QxTdForwardMessagesRequest::setChatId(const qint64 chatId)
{
    m_chatId = chatId;
}

void QxTdForwardMessagesRequest::setFromChatId(const qint64 fromChatId)
{
    m_fromChatId = fromChatId;
}

void QxTdForwardMessagesRequest::setMessageIds(const QList<qint64> &messageIds)
{
    m_messageIds = messageIds;
}

QJsonObject QxTdForwardMessagesRequest::marshalJson()
{
    QJsonArray ids;
    for (const qint64 &id : m_messageIds) {
        ids << QJsonValue(id);
    }
    return QJsonObject{
        { "@type", "forwardMessages" },
        { "chat_id", m_chatId },
        { "from_chat_id", m_fromChatId },
        { "message_ids", ids },
        { "as_album", false },
    };
}

QFuture<QxTdResponse> QxTdForwardMessagesRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::basicGroup);
}
