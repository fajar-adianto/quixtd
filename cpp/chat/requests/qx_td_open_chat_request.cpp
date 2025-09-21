#include "qx_td_open_chat_request.h"

QxTdOpenChatRequest::QxTdOpenChatRequest(QObject *parent)
    : QxTdOkRequest(parent)
    , m_chatId(0)
{
    // Intentionally left empty.
}

void QxTdOpenChatRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

QJsonObject QxTdOpenChatRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "openChat" },
        { "chat_id", m_chatId }
    };
}
