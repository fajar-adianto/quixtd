#include "qx_td_get_message_request.h"
#include "client/qx_td_client.h"

QxTdGetMessageRequest::QxTdGetMessageRequest(QObject *parent)
    : QxTdRequest(parent)
{
    // Intentionally left empty.
}

void QxTdGetMessageRequest::setChatId(const qint64 &chat)
{
    m_chat = chat;
}

void QxTdGetMessageRequest::setMessageId(const qint64 &msg)
{
    m_msg = msg;
}

QJsonObject QxTdGetMessageRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getMessage" },
        { "chat_id", m_chat },
        { "message_id", m_msg },
    };
}

QFuture<QxTdResponse> QxTdGetMessageRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::message);
}
