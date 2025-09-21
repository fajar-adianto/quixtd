#include "qx_td_enable_proxy_request.h"

QxTdEnableProxyRequest::QxTdEnableProxyRequest(QObject *parent)
    : QxTdOkRequest(parent)
{
    // Intentionally left empty.
}

void QxTdEnableProxyRequest::setId(qint32 value)
{
    m_id = value;
}

QJsonObject QxTdEnableProxyRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "enableProxy" },
        { "proxy_id", m_id }
    };
}
