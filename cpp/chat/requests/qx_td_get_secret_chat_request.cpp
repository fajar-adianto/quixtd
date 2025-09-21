#include "qx_td_get_secret_chat_request.h"
#include "client/qx_td_client.h"

QxTdGetSecretChatRequest::QxTdGetSecretChatRequest(QObject *parent)
    : QxTdRequest(parent)
    , m_chatId(0)
{
    // Intentionally left empty.
}

void QxTdGetSecretChatRequest::setSecretChatId(const qint64 &id)
{
    m_chatId = id;
}

QJsonObject QxTdGetSecretChatRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getSecretChat" },
        { "secret_chat_id", m_chatId },
    };
}

QFuture<QxTdResponse> QxTdGetSecretChatRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::secretChat);
}
