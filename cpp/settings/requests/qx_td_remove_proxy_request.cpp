#include "qx_td_remove_proxy_request.h"

QxTdRemoveProxyRequest::QxTdRemoveProxyRequest(QObject *parent)
    : QxTdOkRequest(parent)
{
    // Intentionally left empty.
}

void QxTdRemoveProxyRequest::setId(qint32 value)
{
    m_id = value;
}

QJsonObject QxTdRemoveProxyRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "removeProxy" },
        { "proxy_id", m_id }
    };
}
