#include "qx_td_set_chat_title_request.h"

QxTdSetChatTitleRequest::QxTdSetChatTitleRequest(QObject *parent)
    : QxTdOkRequest(parent)
    , m_chatId(0)
{
    // Intentionally left empty.
}

void QxTdSetChatTitleRequest::setTitle(const qint64 &chatId, const QString &title)
{
    m_chatId = chatId;
    m_title = title;
}

QJsonObject QxTdSetChatTitleRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "setChatTitle" },
        { "chat_id", m_chatId },
        { "title", m_title },
    };
}
