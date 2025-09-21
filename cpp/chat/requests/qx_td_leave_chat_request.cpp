#include "qx_td_leave_chat_request.h"

QxTdLeaveChatRequest::QxTdLeaveChatRequest(QObject *parent)
    : QxTdOkRequest(parent)
    , m_chatId(0)
{
    // Intentionally left empty.
}

void QxTdLeaveChatRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

QJsonObject QxTdLeaveChatRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "leaveChat" },
        { "chat_id", m_chatId }
    };
}
