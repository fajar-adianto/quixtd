#include "qx_td_create_new_secret_chat_request.h"
#include "client/qx_td_client.h"

QxTdCreateNewSecretChatRequest::QxTdCreateNewSecretChatRequest(QObject *parent)
    : QxTdRequest(parent)
    , m_userId(0)
{
    // Intentionally left empty.
}

void QxTdCreateNewSecretChatRequest::setUserId(const qint64 &id)
{
    m_userId = id;
}

QJsonObject QxTdCreateNewSecretChatRequest::marshalJson()
{
  return QJsonObject{
      {"@type", "createNewSecretChat"},
      {"user_id", m_userId}
  };
}

QFuture<QxTdResponse> QxTdCreateNewSecretChatRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::chat);
}
