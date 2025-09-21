#include "qx_td_request.h"
#include <QDebug>
#include "client/qx_td_client.h"

QxTdRequest::QxTdRequest(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

void QxTdRequest::send()
{
    return QxTdClient::instance()->send(this);
}

QFuture<QJsonObject> QxTdRequest::exec()
{
    return QxTdClient::instance()->exec(this);
}

QxTdOkRequest::QxTdOkRequest(QObject *parent)
    : QxTdRequest(parent)
{
    // Intentionally left empty.
}

QFuture<QxTdResponse> QxTdOkRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::ok);
}
