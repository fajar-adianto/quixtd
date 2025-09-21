#include "qx_td_load_chats_request.h"
#include "client/qx_td_client.h"

QxTdLoadChatsRequest::QxTdLoadChatsRequest(QObject *parent)
    : QxTdOkRequest(parent)
    , m_chatList(QStringLiteral("chatListMain"))
{
    // Intentionally left empty.
}

QJsonObject QxTdLoadChatsRequest::marshalJson()
{
    return QJsonObject {
        { "@type", "loadChats" },
        { "chat_list", QJsonObject { { "@type", m_chatList } } },
        { "limit", m_limit },
    };
}

void QxTdLoadChatsRequest::setChatList(const QString chatList)
{
    m_chatList = chatList;
}

void QxTdLoadChatsRequest::setLimit(const qint64 value)
{
    m_limit = value;
}

