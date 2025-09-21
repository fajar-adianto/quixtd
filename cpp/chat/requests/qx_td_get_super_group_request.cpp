#include "qx_td_get_super_group_request.h"
#include "client/qx_td_client.h"

QxTdGetSuperGroupRequest::QxTdGetSuperGroupRequest(QObject *parent)
    : QxTdRequest(parent)
    , m_sgId(0)
{
    // Intentionally left empty.
}

void QxTdGetSuperGroupRequest::setSuperGroupId(const qint64 &id)
{
    m_sgId = id;
}

QJsonObject QxTdGetSuperGroupRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getSupergroup" },
        { "supergroup_id", m_sgId },
    };
}

QFuture<QxTdResponse> QxTdGetSuperGroupRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::superGroup);
}
