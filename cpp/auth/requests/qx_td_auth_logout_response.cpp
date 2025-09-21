#include "qx_td_auth_logout_response.h"

QxTdAuthLogOutResponse::QxTdAuthLogOutResponse(QObject *parent)
    : QxTdOkRequest(parent)
{
    // Intentionally left empty.
}

QJsonObject QxTdAuthLogOutResponse::marshalJson()
{
    return QJsonObject{
        { "@type", "logOut" },
    };
}
