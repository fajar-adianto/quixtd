#include "qx_td_get_message_link_request.h"
#include "client/qx_td_client.h"

QxTdGetMessageLinkRequest::QxTdGetMessageLinkRequest(QObject *parent)
    : QxTdRequest(parent)
{
    // Intentionally left empty.
}

void QxTdGetMessageLinkRequest::setChatId(const qint64 &chat)
{
    m_chat = chat;
}

void QxTdGetMessageLinkRequest::setMessageId(const qint64 &msg)
{
    m_msg = msg;
}

void QxTdGetMessageLinkRequest::setMediaTimestamp(const qint32 &timestamp)
{
    m_media_timestamp = timestamp;
}

void QxTdGetMessageLinkRequest::setForAlbum(const bool &forAlbum)
{
    m_for_album = forAlbum;
}

void QxTdGetMessageLinkRequest::setForComment(const bool &forComment)
{
    m_for_comment = forComment;
}

QJsonObject QxTdGetMessageLinkRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getMessageLink" },
        { "chat_id", m_chat },
        { "message_id", m_msg },
        { "media_timestamp", m_media_timestamp },
        { "for_album", m_for_album },
        { "for_comment", m_for_comment }
    };
}

QFuture<QxTdResponse> QxTdGetMessageLinkRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::messageLink);
}
