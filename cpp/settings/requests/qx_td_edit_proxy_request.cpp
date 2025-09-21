#include "qx_td_edit_proxy_request.h"
#include "client/qx_td_client.h"

QxTdEditProxyRequest::QxTdEditProxyRequest(QObject *parent)
    : QxTdRequest(parent)
{
    // Intentionally left empty.
}

QJsonObject QxTdEditProxyRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "editProxy" },
        { "proxy_id", m_id },
        { "server", m_server },
        { "port", m_port },
        { "enable", m_enable },
        { "type", m_type->marshalJson() }
    };
}

void QxTdEditProxyRequest::setId(qint32 value)
{
    m_id = value;
}

void QxTdEditProxyRequest::setServer(QString value)
{
    m_server = value;
}

void QxTdEditProxyRequest::setPort(qint32 value) {
    m_port = value;
}

void QxTdEditProxyRequest::setEnable(bool value) {
    m_enable = value;
}

void QxTdEditProxyRequest::setType(QPointer<QxTdProxyType> value) {
    m_type = value;
}

QFuture<QxTdResponse> QxTdEditProxyRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::proxy);
}
