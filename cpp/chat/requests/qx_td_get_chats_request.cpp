#include "qx_td_get_chats_request.h"
#include "client/qx_td_client.h"

QxTdGetChatsRequest::QxTdGetChatsRequest(QObject *parent)
    : QxTdRequest(parent)
    , m_chatList(QStringLiteral("chatListMain"))
{
    // Intentionally left empty.
}

QJsonObject QxTdGetChatsRequest::marshalJson()
{
    return QJsonObject {
        { "@type", "getChats" },
        { "chat_list", QJsonObject { { "@type", m_chatList } } },
        { "limit", m_limit },
    };
}

void QxTdGetChatsRequest::setChatList(const QString chatList)
{
    m_chatList = chatList;
}

void QxTdGetChatsRequest::setLimit(const qint64 value)
{
    m_limit = value;
}

QFuture<QxTdResponse> QxTdGetChatsRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::chats);
}
