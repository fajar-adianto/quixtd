#include "qx_td_search_user_by_phone_number_request.h"

#include "client/qx_td_client.h"

QxTdSearchUserByPhoneNumberRequest::QxTdSearchUserByPhoneNumberRequest(QObject *parent)
    : QxTdRequest(parent)
{
    // Intentionally left empty
}

void QxTdSearchUserByPhoneNumberRequest::setPhoneNumber(const QString &value)
{
    m_phoneNumber = value;
}

QJsonObject QxTdSearchUserByPhoneNumberRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "searchUserByPhoneNumber" },
        { "phone_number", m_phoneNumber },
    };
}

QFuture<QxTdResponse> QxTdSearchUserByPhoneNumberRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::user);
}
