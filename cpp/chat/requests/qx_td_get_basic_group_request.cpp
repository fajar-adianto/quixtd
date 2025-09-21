#include "qx_td_get_basic_group_request.h"
#include "client/qx_td_client.h"

QxTdGetBasicGroupRequest::QxTdGetBasicGroupRequest(QObject *parent)
    : QxTdRequest(parent)
    , m_groupId(0)
{
    // Intentionally left empty.
}

void QxTdGetBasicGroupRequest::setGroupId(const qint64 groupId)
{
    m_groupId = groupId;
}

QJsonObject QxTdGetBasicGroupRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getBasicGroup" },
        { "basic_group_id", m_groupId },
    };
}

QFuture<QxTdResponse> QxTdGetBasicGroupRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::basicGroup);
}
