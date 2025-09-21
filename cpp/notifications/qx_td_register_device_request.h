#ifndef QX_TD_REGISTER_DEVICE_REQUEST_H
#define QX_TD_REGISTER_DEVICE_REQUEST_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdRegisterDeviceRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1register_device.html
 */
class QxTdRegisterDeviceRequest : public QxTdRequest
{
    Q_OBJECT
public:
    explicit QxTdRegisterDeviceRequest(QObject *parent = nullptr);

    void setToken(const QString &token);

    QJsonObject marshalJson();

    QFuture<QxTdResponse> sendAsync();

private:
    QString m_token;
};

#endif // QX_TD_REGISTER_DEVICE_REQUEST_H
