#ifndef QX_TD_DISABLE_PROXY_REQUEST_H
#define QX_TD_DISABLE_PROXY_REQUEST_H

#include "common/qx_td_request.h"

/**
 * @brief The QxTdGetProxiesRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_proxies.html
 */
class QxTdDisableProxyRequest : public QxTdOkRequest
{
    Q_OBJECT

public:
    explicit QxTdDisableProxyRequest(QObject *parent = nullptr);
    QJsonObject marshalJson();

};

#endif // QX_TD_DISABLE_PROXY_REQUEST_H
