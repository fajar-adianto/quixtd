#include "qx_td_get_proxies_request.h"
#include "client/qx_td_client.h"

QxTdGetProxiesRequest::QxTdGetProxiesRequest(QObject *parent)
    : QxTdRequest(parent)
{
    // Intentionally left empty.
}

QJsonObject QxTdGetProxiesRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getProxies" }
    };
}

QFuture<QxTdResponse> QxTdGetProxiesRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::proxies);
}
