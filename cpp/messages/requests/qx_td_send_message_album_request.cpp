#include "qx_td_send_message_album_request.h"
#include "client/qx_td_client.h"

QxTdSendMessageAlbumRequest::QxTdSendMessageAlbumRequest(QObject *parent)
    : QxTdRequest(parent)
    , m_chatId(0)
    , m_replyMessageId(0)
    , m_contents(QList<QxTdInputMessageContent*>())
    , m_messageSendOptions(new QxTdMessageSendOptions)
{
    // Intentionally left empty.
}

void QxTdSendMessageAlbumRequest::setContents(const QList<QxTdInputMessageContent *> &contents)
{
    m_contents = contents;
}

void QxTdSendMessageAlbumRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QxTdSendMessageAlbumRequest::setReplyToMessageId(const qint64 &id)
{
    m_replyMessageId = id;
}

void QxTdSendMessageAlbumRequest::setDisableNotification(const bool value)
{
    m_messageSendOptions->setDisableNotifications(value);
}

void QxTdSendMessageAlbumRequest::setSendDate(const qint32 value)
{
    m_messageSendOptions->setSendDate(value);
}

QJsonObject QxTdSendMessageAlbumRequest::marshalJson()
{
    QJsonArray contents;
    for (int i = 0; i < m_contents.count(); ++i) {
        contents << m_contents.at(i)->marshalJson();
    }
    return QJsonObject {
        { "@type", "sendMessageAlbum" },
        { "chat_id", m_chatId },
        { "reply_to_message_id", m_replyMessageId },
        { "input_message_contents", contents },
        { "options", m_messageSendOptions->marshalJson() }
    };
}

QFuture<QxTdResponse> QxTdSendMessageAlbumRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::message);
}
