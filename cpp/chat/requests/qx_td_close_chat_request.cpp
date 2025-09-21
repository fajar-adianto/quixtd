#include "qx_td_close_chat_request.h"

QxTdCloseChatRequest::QxTdCloseChatRequest(QObject *parent)
    : QxTdOkRequest(parent)
    , m_chatId(0)
{
    // Intentionally left empty.
}

void QxTdCloseChatRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

QJsonObject QxTdCloseChatRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "closeChat" },
        { "chat_id", m_chatId }
    };
}
