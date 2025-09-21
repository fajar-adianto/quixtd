#include "qx_td_get_super_group_full_info_request.h"
#include "client/qx_td_client.h"

QxTdGetSuperGroupFullInfoRequest::QxTdGetSuperGroupFullInfoRequest(QObject *parent)
    : QxTdRequest(parent)
    , m_id(0)
{
    // Intentionally left empty.
}

void QxTdGetSuperGroupFullInfoRequest::setSupergroupId(const qint64 &id)
{
    m_id = id;
}

QJsonObject QxTdGetSuperGroupFullInfoRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getSupergroupFullInfo" },
        { "supergroup_id", m_id }
    };
}

QFuture<QxTdResponse> QxTdGetSuperGroupFullInfoRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::supergroupFullInfo);
}
