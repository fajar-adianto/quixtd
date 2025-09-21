#include "qx_td_get_user_request.h"
#include "client/qx_td_client.h"

QxTdGetUserRequest::QxTdGetUserRequest(QObject *parent)
    : QxTdRequest(parent)
{
    // Intentionally left empty
}

void QxTdGetUserRequest::setUserId(const QString &id)
{
    setUserId(id.toLongLong());
}

void QxTdGetUserRequest::setUserId(const qint64 &id)
{
    m_uid = id;
}

QJsonObject QxTdGetUserRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getUser" },
        { "user_id", m_uid.value() }
    };
}

QFuture<QxTdResponse> QxTdGetUserRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::user);
}
