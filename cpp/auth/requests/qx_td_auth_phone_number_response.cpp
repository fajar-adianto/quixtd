#include "qx_td_auth_phone_number_response.h"

QxTdAuthPhoneNumberResponse::QxTdAuthPhoneNumberResponse(QObject *parent)
    : QxTdOkRequest(parent)
{
    // Intentionally left empty.
}

void QxTdAuthPhoneNumberResponse::setPhoneNumber(const QString &number)
{
    m_number = number;
}

QJsonObject QxTdAuthPhoneNumberResponse::marshalJson()
{
    return QJsonObject{
        { "@type", "setAuthenticationPhoneNumber" },
        { "phone_number", m_number },
        { "allow_flash_call", false },
        { "is_current_phone_number", true }
    };
}
