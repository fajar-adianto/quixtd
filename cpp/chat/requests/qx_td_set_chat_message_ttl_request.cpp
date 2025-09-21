#include "qx_td_set_chat_message_ttl_request.h"

QxTdSetChatMessageTtlRequest::QxTdSetChatMessageTtlRequest(QObject *parent)
    : QxTdOkRequest(parent)
    , m_chatId(0)
{
    // Intentionally left empty.
}

void QxTdSetChatMessageTtlRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QxTdSetChatMessageTtlRequest::setTTL(const qint32 &ttl)
{
    m_ttl = ttl;
}

QJsonObject QxTdSetChatMessageTtlRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "setChatMessageTtl" },
        { "chat_id", m_chatId },
        { "ttl", m_ttl }
    };
}
