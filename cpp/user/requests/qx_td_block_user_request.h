#ifndef QX_TD_BLOCK_USER_REQUEST_H
#define QX_TD_BLOCK_USER_REQUEST_H

#include "common/qx_td_request.h"

class QxTdUser; // Forward declaration.

/**
 * @brief The QxTdBlockUserRequest class
 *
 * Add a user to the blacklist
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1block_user.html
 *
 * Usage:
 *
 *   std::unique_ptr<QxTdBlockUserRequest> req(new QxTdBlockUserRequest);
 *   req->setUserId(1);
 *   // or
 *   req->setUserId("1");
 *   // or
 *   QxTdUser *user;
 *   req->setUser(user);
 *   req->send();
 *   // or
 *   QFuture<QxTdResponse> resp = req->sendAsync()
 *   await(resp)
 *   if (resp.result().isOk()) {}
 */
class QxTdBlockUserRequest : public QxTdOkRequest
{
    Q_OBJECT
public:
    explicit QxTdBlockUserRequest(QObject *parent = nullptr);

    void setUser(QxTdUser *user);
    void setUserId(const qint64 &id);
    void setUserId(const QString &id);

    QJsonObject marshalJson();

private:
    Q_DISABLE_COPY(QxTdBlockUserRequest)
    qint64 m_userId;
};

#endif // QX_TD_BLOCK_USER_REQUEST_H
