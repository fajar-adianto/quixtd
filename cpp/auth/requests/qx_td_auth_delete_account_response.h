#ifndef QX_TD_AUTH_DELETE_ACCOUNT_RESPONSE_H
#define QX_TD_AUTH_DELETE_ACCOUNT_RESPONSE_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdAuthDeleteAccountResponse class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1delete_account.html
 */
class QxTdAuthDeleteAccountResponse : public QxTdOkRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdAuthDeleteAccountResponse)
public:
    explicit QxTdAuthDeleteAccountResponse(QObject *parent = nullptr);

    /**
     * @brief setReason
     * @param reason
     *
     * (Optional) The reason why the account was deleted
     */
    void setReason(const QString &reason);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();

private:
    QString m_reason;
};

#endif // QX_TD_AUTH_DELETE_ACCOUNT_RESPONSE_H
