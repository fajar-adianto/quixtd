#ifndef QX_TD_AUTH_PARAMETERS_RESPONSE_H
#define QX_TD_AUTH_PARAMETERS_RESPONSE_H

#include "common/qx_td_request.h"

class QxTdAuthParams; // Forward declaration.

/**
 * @brief The QxTdAuthParametersResponse class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1set_tdlib_parameters.html
 */
class QxTdAuthParametersResponse : public QxTdOkRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdAuthParametersResponse)
public:
    explicit QxTdAuthParametersResponse(QObject *parent = nullptr);

    /**
     * @brief setParameters
     * @param params - Parameters
     */
    void setParameters(QxTdAuthParams *params);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();

private:
    QJsonObject m_params;
};

#endif // QX_TD_AUTH_PARAMETERS_RESPONSE_H
