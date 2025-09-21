#ifndef QX_TD_PING_PROXY_REQUEST_H
#define QX_TD_PING_PROXY_REQUEST_H

#include "common/qx_td_request.h"

/**
 * @brief The QxTdGetProxiesRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1ping_proxy.html
 */
class QxTdPingProxyRequest : public QxTdRequest
{
    Q_OBJECT

public:
    explicit QxTdPingProxyRequest(QObject *parent = nullptr);
    QJsonObject marshalJson();
    QFuture<QxTdResponse> sendAsync();
    
    void setId(qint32 value);
    
private:
    qint32 m_id;
};

#endif // QX_TD_PING_PROXY_REQUEST_H
