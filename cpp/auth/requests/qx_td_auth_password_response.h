#ifndef QX_TD_AUTH_PASSWORD_RESPONSE_H
#define QX_TD_AUTH_PASSWORD_RESPONSE_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdAuthPasswordResponse class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1check_authentication_password.html
 */
class QxTdAuthPasswordResponse : public QxTdOkRequest
{
    Q_OBJECT
public:
    explicit QxTdAuthPasswordResponse(QObject *parent = nullptr);

    /**
     * @brief setPassword
     * @param password to check
     */
    void setPassword(const QString &password);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();

private:
    QString m_password;
};

#endif // QX_TD_AUTH_PASSWORD_RESPONSE_H
