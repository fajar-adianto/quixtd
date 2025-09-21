#include "qx_td_register_device_request.h"
#include "client/qx_td_client.h"

QxTdRegisterDeviceRequest::QxTdRegisterDeviceRequest(QObject *parent)
    : QxTdRequest(parent)
{
}

void QxTdRegisterDeviceRequest::setToken(const QString &token)
{
    m_token = token;
}

QJsonObject QxTdRegisterDeviceRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "registerDevice" },
        { "device_token", QJsonObject{
                                  { "@type", "deviceTokenUbuntuPush" },
                                  { "token", m_token } } }
    };
}

QFuture<QxTdResponse> QxTdRegisterDeviceRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::pushReceiverId);
}
