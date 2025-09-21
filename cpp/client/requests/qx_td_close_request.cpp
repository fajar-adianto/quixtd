#include "qx_td_close_request.h"

QxTdCloseRequest::QxTdCloseRequest(QObject *parent)
    : QxTdOkRequest(parent)
{
    // Intentionally left empty.
}

QJsonObject QxTdCloseRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "close" }
    };
}
