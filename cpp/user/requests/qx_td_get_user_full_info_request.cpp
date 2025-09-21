#include "qx_td_get_user_full_info_request.h"
#include "client/qx_td_client.h"

QxTdGetUserFullInfoRequest::QxTdGetUserFullInfoRequest(QObject *parent)
    : QxTdRequest(parent)
{
    // Intentionally left empty.
}

void QxTdGetUserFullInfoRequest::setUserId(const QString &id)
{
    setUserId(id.toLongLong());
}

void QxTdGetUserFullInfoRequest::setUserId(const qint64 &id)
{
    m_uid = id;
}

QJsonObject QxTdGetUserFullInfoRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getUserFullInfo" },
        { "user_id", m_uid.value() }
    };
}

QFuture<QxTdResponse> QxTdGetUserFullInfoRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::userFullInfo);
}
