#ifndef QX_TD_REMOVE_PROXY_REQUEST_H
#define QX_TD_REMOVE_PROXY_REQUEST_H

#include "common/qx_td_request.h"

/**
 * @brief The QxTdGetProxiesRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_proxies.html
 */
class QxTdRemoveProxyRequest : public QxTdOkRequest
{
    Q_OBJECT

public:
    explicit QxTdRemoveProxyRequest(QObject *parent = nullptr);
    QJsonObject marshalJson();

    void setId(qint32 value);
    
private:
    qint32 m_id;
};

#endif // QX_TD_REMOVE_PROXY_REQUEST_H
