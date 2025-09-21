#include "qx_td_auth_code_response.h"

QxTdAuthCodeResponse::QxTdAuthCodeResponse(QObject *parent)
    : QxTdOkRequest(parent)
{
    // Intentionally left empty.
}

void QxTdAuthCodeResponse::setCode(const QString &code)
{
    m_code = code;
}

QJsonObject QxTdAuthCodeResponse::marshalJson()
{
    return QJsonObject{
        { "@type", "checkAuthenticationCode" },
        { "code", m_code },
    };
}
