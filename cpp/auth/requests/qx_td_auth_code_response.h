#ifndef QX_TD_AUTH_CODE_RESPONSE_H
#define QX_TD_AUTH_CODE_RESPONSE_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdAuthCodeResponse class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1check_authentication_code.html
 */
class QxTdAuthCodeResponse : public QxTdOkRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdAuthCodeResponse)
public:
    explicit QxTdAuthCodeResponse(QObject *parent = nullptr);

    /**
     * @brief setCode
     * @param code
     *
     * The verification code received via SMS, Telegram or call
     */
    void setCode(const QString &code);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();

private:
    QString m_code;
};

#endif // QX_TD_AUTH_CODE_RESPONSE_H
