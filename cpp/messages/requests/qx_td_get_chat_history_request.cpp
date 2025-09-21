#include "qx_td_get_chat_history_request.h"
#include "client/qx_td_client.h"

QxTdGetChatHistoryRequest::QxTdGetChatHistoryRequest(QObject *parent)
    : QxTdRequest(parent)
    , m_chatId(0)
    , m_fromMessageId(0)
    , m_offset(0)
    , m_limit(0)
    , m_onlyLocal(false)
{
    // Intentionally left empty.
}

void QxTdGetChatHistoryRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QxTdGetChatHistoryRequest::setFromMessageId(const qint64 &fromMessageId)
{
    m_fromMessageId = fromMessageId;
}

void QxTdGetChatHistoryRequest::setOffset(const qint32 &offset)
{
    m_offset = offset;
}

void QxTdGetChatHistoryRequest::setLimit(const qint32 &limit)
{
    m_limit = limit;
}

void QxTdGetChatHistoryRequest::setOnlyLocal(const bool value)
{
    m_onlyLocal = value;
}

QJsonObject QxTdGetChatHistoryRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getChatHistory" },
        { "chat_id",  m_chatId },
        { "from_message_id", m_fromMessageId },
        { "offset", m_offset },
        { "limit", m_limit },
        { "only_local", m_onlyLocal }
    };
}

QFuture<QxTdResponse> QxTdGetChatHistoryRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::messages);
}
