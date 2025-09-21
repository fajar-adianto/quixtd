#ifndef QX_TD_REQUEST_H
#define QX_TD_REQUEST_H

#include <QtConcurrent>
#include <QFuture>
#include "qx_td_object.h"
#include "qx_td_response.h"

/**
 * @brief The QxTdRequest class
 *
 * Base class for all rdlib requests
 */
class QxTdRequest : public QxTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdRequest)
public:
    explicit QxTdRequest(QObject *parent = nullptr);

    virtual QFuture<QxTdResponse> sendAsync() = 0;
    virtual void send();
    virtual QFuture<QJsonObject> exec();
};

/**
 * @brief The QxTdOkRequest class
 *
 * A request class that expects an OK response from tdlib
 * for the requested action
 */
class QxTdOkRequest : public QxTdRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdOkRequest)
public:
    explicit QxTdOkRequest(QObject *parent = nullptr);
    /**
     * @brief sendAsync
     * @return QxTdResponse - will either be resp.isOk() or resp.isError()
     */
    QFuture<QxTdResponse> sendAsync();
};

#endif // QX_TD_REQUEST_H
