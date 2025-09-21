#include "qx_td_open_message_content_request.h"
#include "client/qx_td_client.h"

QxTdOpenMessageContentRequest::QxTdOpenMessageContentRequest(QObject *parent)
    : QxTdRequest(parent)
    , m_chatId("")
    , m_messageId("")
{
    // Intentionally left empty.
}

void QxTdOpenMessageContentRequest::setChatId(const QString &id)
{
    m_chatId = id;
}

void QxTdOpenMessageContentRequest::setMessageId(const QString &id)
{
    m_messageId = id;
}

QJsonObject QxTdOpenMessageContentRequest::marshalJson()
{

    return QJsonObject{
        { "@type", "openMessageContent" },
        { "chat_id", m_chatId },
        { "message_id", m_messageId }
    };
}

QFuture<QxTdResponse> QxTdOpenMessageContentRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::message);
}
