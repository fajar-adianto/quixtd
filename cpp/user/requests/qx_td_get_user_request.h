#ifndef QX_TD_GET_USER_REQUEST_H
#define QX_TD_GET_USER_REQUEST_H

#include "common/qx_td_request.h"
#include "common/qx_td_int.h"

/**
 * @brief The QxTdGetUserRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_user.html
 */
class QxTdGetUserRequest : public QxTdRequest
{
    Q_OBJECT
public:
    explicit QxTdGetUserRequest(QObject *parent = nullptr);

    void setUserId(const QString &id);
    void setUserId(const qint64 &id);

    QJsonObject marshalJson();

    QFuture<QxTdResponse> sendAsync();

private:
    QxTdInt64 m_uid;
};

#endif // QX_TD_GET_USER_REQUEST_H
