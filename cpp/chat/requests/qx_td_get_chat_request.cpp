#include "qx_td_get_chat_request.h"
#include "client/qx_td_client.h"

QxTdGetChatRequest::QxTdGetChatRequest(QObject *parent)
    : QxTdRequest(parent)
    , m_chat_id(0)
{
    // Intentionally left empty.
}

QJsonObject QxTdGetChatRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getChat" },
        { "chat_id", m_chat_id },
    };
}

void QxTdGetChatRequest::setChatId(const QString &id)
{
    setChatId(id.toLong());
}
void QxTdGetChatRequest::setChatId(const qint64 &id)
{
    m_chat_id = id;
}

QFuture<QxTdResponse>
QxTdGetChatRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::chat);
}
