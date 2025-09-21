#include "qx_td_disable_proxy_request.h"

QxTdDisableProxyRequest::QxTdDisableProxyRequest(QObject *parent)
    : QxTdOkRequest(parent)
{
    // Intentionally left empty.
}

QJsonObject QxTdDisableProxyRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "disableProxy" }
    };
}
