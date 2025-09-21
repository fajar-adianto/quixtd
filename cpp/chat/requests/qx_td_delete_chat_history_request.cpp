#include "qx_td_delete_chat_history_request.h"

QxTdDeleteChatHistoryRequest::QxTdDeleteChatHistoryRequest(QObject *parent)
    : QxTdOkRequest(parent)
    , m_chatId(0)
    , m_removeFromChatList(false)
{
    // Intentionally left empty.
}

void QxTdDeleteChatHistoryRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QxTdDeleteChatHistoryRequest::setRemoveFromChatList(const bool &remove)
{
    m_removeFromChatList = remove;
}

void QxTdDeleteChatHistoryRequest::setRevoke(const bool &value)
{
    m_revoke = value;
}

QJsonObject QxTdDeleteChatHistoryRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "deleteChatHistory" },
        { "chat_id", m_chatId },
        { "remove_from_chat_list", m_removeFromChatList },
        { "revoke", m_revoke }
    };
}
