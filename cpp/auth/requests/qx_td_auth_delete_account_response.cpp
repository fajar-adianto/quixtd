#include "qx_td_auth_delete_account_response.h"

QxTdAuthDeleteAccountResponse::QxTdAuthDeleteAccountResponse(QObject *parent)
    : QxTdOkRequest(parent)
{
    // Intentionally left empty.
}

void QxTdAuthDeleteAccountResponse::setReason(const QString &reason)
{
    m_reason = reason;
}

QJsonObject QxTdAuthDeleteAccountResponse::marshalJson()
{
    return QJsonObject{
        { "@type", "deleteAccount" },
        { "reason", m_reason },
    };
}
