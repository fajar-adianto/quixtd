#ifndef QX_TD_ADD_PROXY_REQUEST_H
#define QX_TD_ADD_PROXY_REQUEST_H

#include "common/qx_td_request.h"
#include "../qx_td_proxy_type.h"

/**
 * @brief The QxTdAddProxyRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1add_proxy.html
 */
class QxTdAddProxyRequest : public QxTdRequest
{
    Q_OBJECT

public:
    explicit QxTdAddProxyRequest(QObject *parent = nullptr);

    void setServer(QString value);
    void setPort(qint32 value);
    void setType(QPointer<QxTdProxyType> value);
    void setEnable(bool value);

    QJsonObject marshalJson();
    QFuture<QxTdResponse> sendAsync();

private:
    QString m_server;
    qint32 m_port;
    bool m_enable;
    QPointer<QxTdProxyType> m_type;
};

#endif // QX_TD_ADD_PROXY_REQUEST_H
