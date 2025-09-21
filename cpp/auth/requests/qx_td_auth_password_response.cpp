#include "qx_td_auth_password_response.h"

QxTdAuthPasswordResponse::QxTdAuthPasswordResponse(QObject *parent)
    : QxTdOkRequest(parent)
{
    // Intentionally left empty.
}

void QxTdAuthPasswordResponse::setPassword(const QString &password)
{
    m_password = password;
}

QJsonObject QxTdAuthPasswordResponse::marshalJson()
{
    return QJsonObject{
        { "@type", "checkAuthenticationPassword" },
        { "password", m_password },
    };
}
