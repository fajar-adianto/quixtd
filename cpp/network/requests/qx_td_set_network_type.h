#ifndef QX_TD_SET_NETWORK_TYPE_REQUEST_H
#define QX_TD_SET_NETWORK_TYPE_REQUEST_H

#include "common/qx_td_request.h"

class QxTdNetworkType; // Forward declaration.

/**
 * @brief The QxTdSetNetworkTypeRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1set_network_type.html
 */
class QxTdSetNetworkTypeRequest : public QxTdOkRequest
{
    Q_OBJECT
public:
    explicit QxTdSetNetworkTypeRequest(QObject *parent = nullptr);

    void setNetworkType(QxTdNetworkType *networkType);

    QJsonObject marshalJson();

private:
    Q_DISABLE_COPY(QxTdSetNetworkTypeRequest)
    QxTdNetworkType *m_networkType;
};

#endif // QX_TD_SET_NETWORK_TYPE_REQUEST_H
