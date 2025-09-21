#include "qx_td_add_proxy_request.h"
#include "client/qx_td_client.h"

QxTdAddProxyRequest::QxTdAddProxyRequest(QObject *parent)
    : QxTdRequest(parent)
{
    // Intentionally left empty.
}

QJsonObject QxTdAddProxyRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "addProxy" },
        { "server", m_server },
        { "port", m_port },
        { "enable", m_enable },
        { "type", m_type->marshalJson() }
    };
}

void QxTdAddProxyRequest::setServer(QString value) {
    m_server = value;
}

void QxTdAddProxyRequest::setPort(qint32 value) {
    m_port = value;
}

void QxTdAddProxyRequest::setEnable(bool value) {
    m_enable = value;
}

void QxTdAddProxyRequest::setType(QPointer<QxTdProxyType> value) {
    m_type = value;
}

QFuture<QxTdResponse> QxTdAddProxyRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::proxy);
}
