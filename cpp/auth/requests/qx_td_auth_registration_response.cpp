#include "qx_td_auth_registration_response.h"

QxTdAuthRegistrationResponse::QxTdAuthRegistrationResponse(QObject *parent)
    : QxTdOkRequest(parent)
{
    // Intentionally left empty.
}

void QxTdAuthRegistrationResponse::setFirstName(const QString &firstname)
{
    m_firstname = firstname;
}

void QxTdAuthRegistrationResponse::setLastName(const QString &lastname)
{
    m_lastname = lastname;
}

QJsonObject QxTdAuthRegistrationResponse::marshalJson()
{
    return QJsonObject {
        { "@type", "registerUser" },
        { "first_name", m_firstname },
        { "last_name", m_lastname },
    };
}
