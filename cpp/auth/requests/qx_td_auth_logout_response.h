#ifndef QX_TD_AUTH_LOGOUT_RESPONSE_H
#define QX_TD_AUTH_LOGOUT_RESPONSE_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdAuthLogOutResponse class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1log_out.html
 */
class QxTdAuthLogOutResponse : public QxTdOkRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdAuthLogOutResponse)
public:
    explicit QxTdAuthLogOutResponse(QObject *parent = nullptr);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();
};

#endif // QX_TD_AUTH_LOGOUT_RESPONSE_H
