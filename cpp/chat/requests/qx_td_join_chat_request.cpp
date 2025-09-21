#include "qx_td_join_chat_request.h"

QxTdJoinChatRequest::QxTdJoinChatRequest(QObject *parent)
    : QxTdOkRequest(parent)
    , m_chatId(0)
{
    // Intentionally left empty.
}

void QxTdJoinChatRequest::setChatId(const QString &chatId)
{
    setChatId(chatId.toLongLong());
}

void QxTdJoinChatRequest::setChatId(const qint64 &chatId)
{
    m_chatId = chatId;
}

QJsonObject QxTdJoinChatRequest::marshalJson()
{
    return QJsonObject {
        { "@type", "joinChat" },
        { "chat_id", m_chatId.value() }
    };
}
