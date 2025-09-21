#include "qx_td_get_contacts_request.h"
#include "client/qx_td_client.h"

QxTdGetContactsRequest::QxTdGetContactsRequest(QObject *parent)
    : QxTdRequest(parent)
{
    // Intentionally left empty.
}

QJsonObject QxTdGetContactsRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getContacts" }
    };
}

QFuture<QxTdResponse> QxTdGetContactsRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::users);
}
