#include "qx_td_close_secret_chat_request.h"

QxTdCloseSecretChatRequest::QxTdCloseSecretChatRequest(QObject *parent)
    : QxTdOkRequest(parent)
    , m_secretChatId(0)
{
    // Intentionally left empty.
}

void QxTdCloseSecretChatRequest::setSecretChatId(const qint64 &id)
{
    m_secretChatId = id;
}

QJsonObject QxTdCloseSecretChatRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "closeSecretChat" },
        { "secret_chat_id", m_secretChatId }
    };
}
