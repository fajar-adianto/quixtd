#include "qx_td_send_message_request.h"
#include "client/qx_td_client.h"

QxTdSendMessageRequest::QxTdSendMessageRequest(QObject *parent)
    : QxTdRequest(parent)
    , m_chatId(0)
    , m_replyMessageId(0)
    , m_content(nullptr)
    , m_messageSendOptions(new QxTdMessageSendOptions)
{
    // Intentionally left empty.
}

void QxTdSendMessageRequest::setContent(QxTdInputMessageContent *content)
{
    m_content = content;
}

void QxTdSendMessageRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QxTdSendMessageRequest::setReplyToMessageId(const qint64 &id)
{
    m_replyMessageId = id;
}

void QxTdSendMessageRequest::setDisableNotification(const bool value)
{
    m_messageSendOptions->setDisableNotifications(value);
}

void QxTdSendMessageRequest::setSendDate(const qint32 value)
{
    m_messageSendOptions->setSendDate(value);
}

QJsonObject QxTdSendMessageRequest::marshalJson()
{

    return QJsonObject{
        { "@type", "sendMessage" },
        { "chat_id", m_chatId },
        { "reply_to_message_id", m_replyMessageId },
        { "input_message_content", m_content->marshalJson() },
        { "options", m_messageSendOptions->marshalJson() }
    };
}

QFuture<QxTdResponse> QxTdSendMessageRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::message);
}
