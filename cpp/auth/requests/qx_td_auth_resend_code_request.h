#ifndef QX_TD_AUTH_RESEND_CODE_REQUEST_H
#define QX_TD_AUTH_RESEND_CODE_REQUEST_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdAuthRegistrationResponse class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1register_user.html
 */
class QxTdAuthResendCodeRequest : public QxTdOkRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdAuthResendCodeRequest)

public:
    explicit QxTdAuthResendCodeRequest(QObject *parent = nullptr);

        /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();

};
#endif // QX_TD_AUTH_RESEND_CODE_REQUEST_H
