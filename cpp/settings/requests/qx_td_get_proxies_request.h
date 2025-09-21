#ifndef QX_TD_GET_PROXIES_REQUEST_H
#define QX_TD_GET_PROXIES_REQUEST_H

#include "common/qx_td_request.h"

/**
 * @brief The QxTdGetProxiesRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_proxies.html
 */
class QxTdGetProxiesRequest : public QxTdRequest
{
    Q_OBJECT

public:
    explicit QxTdGetProxiesRequest(QObject *parent = nullptr);
    QJsonObject marshalJson();
    QFuture<QxTdResponse> sendAsync();
};

#endif // QX_TD_GET_PROXIES_REQUEST_H
