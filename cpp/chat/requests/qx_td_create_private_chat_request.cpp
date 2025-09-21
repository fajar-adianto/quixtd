#include "qx_td_create_private_chat_request.h"
#include "client/qx_td_client.h"

QxTdCreatePrivateChatRequest::QxTdCreatePrivateChatRequest(QObject *parent)
    : QxTdRequest(parent)
    , m_userId(0)
{
    // Intentionally left empty.
}

void QxTdCreatePrivateChatRequest::setUserId(const qint64 &id)
{
    m_userId = id;
}

void QxTdCreatePrivateChatRequest::setForce(const bool &force)
{
    m_force = force;
}

QJsonObject QxTdCreatePrivateChatRequest::marshalJson()
{
  return QJsonObject{
      {"@type", "createPrivateChat"},
      {"user_id", m_userId},
      {"force", m_force}
  };
}

QFuture<QxTdResponse> QxTdCreatePrivateChatRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::chat);
}
