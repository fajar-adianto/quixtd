#include "qx_td_ping_proxy_request.h"
#include "client/qx_td_client.h"

QxTdPingProxyRequest::QxTdPingProxyRequest(QObject *parent)
    : QxTdRequest(parent)
{
    // Intentionally left empty.
}

void QxTdPingProxyRequest::setId(qint32 value)
{
    m_id = value;
}

QJsonObject QxTdPingProxyRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "pingProxy" },
        { "proxy_id", m_id }
    };
}

QFuture<QxTdResponse> QxTdPingProxyRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::seconds);
}

