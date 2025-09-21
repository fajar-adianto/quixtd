#ifndef QX_TD_AUTH_PHONE_NUMBER_RESPONSE_H
#define QX_TD_AUTH_PHONE_NUMBER_RESPONSE_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdAuthPhoneNumberResponse class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1set_authentication_phone_number.html
 */
class QxTdAuthPhoneNumberResponse : public QxTdOkRequest
{
    Q_OBJECT
public:
    explicit QxTdAuthPhoneNumberResponse(QObject *parent = nullptr);

    void setPhoneNumber(const QString &number);

    QJsonObject marshalJson();

private:
    QString m_number;
};

#endif // QX_TD_AUTH_PHONE_NUMBER_RESPONSE_H
