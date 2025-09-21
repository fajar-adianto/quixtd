#ifndef QX_TD_AUTH_REGISTRATION_RESPONSE_H
#define QX_TD_AUTH_REGISTRATION_RESPONSE_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdAuthRegistrationResponse class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1register_user.html
 */
class QxTdAuthRegistrationResponse : public QxTdOkRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdAuthRegistrationResponse)
public:
    explicit QxTdAuthRegistrationResponse(QObject *parent = nullptr);

    /**
     * @brief setFirstName
     * @param firstname
     *
     * The first name of the user; 1-64 characters
     */
    void setFirstName(const QString &firstname);

    /**
     * @brief setLastName
     * @param lastname
     *
     * The last name of the user; 0-64 characters.
     */
    void setLastName(const QString &lastname);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();

private:
    QString m_firstname;
    QString m_lastname;
};

#endif // QX_TD_AUTH_REGISTRATION_RESPONSE_H
