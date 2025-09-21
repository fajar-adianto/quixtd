#include "qx_td_search_public_chat_request.h"
#include "client/qx_td_client.h"

QxTdSearchPublicChatRequest::QxTdSearchPublicChatRequest(QObject *parent)
    : QxTdRequest(parent)
    , m_username("")
{
    // Intentionally left empty.
}

void QxTdSearchPublicChatRequest::setChatUsername(const QString &username)
{
    m_username = username;
}

QJsonObject QxTdSearchPublicChatRequest::marshalJson()
{
    return QJsonObject {
        { "@type", "searchPublicChat" },
        { "username", m_username }
    };
}

QFuture<QxTdResponse> QxTdSearchPublicChatRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::chat);
}
