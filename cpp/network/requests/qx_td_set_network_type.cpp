#include "qx_td_set_network_type.h"
#include "network/qx_td_network_type.h"

QxTdSetNetworkTypeRequest::QxTdSetNetworkTypeRequest(QObject *parent)
    : QxTdOkRequest(parent)
    , m_networkType(nullptr)
{
    // Intentionally left empty.
}

void QxTdSetNetworkTypeRequest::setNetworkType(QxTdNetworkType *networkType)
{
    m_networkType = networkType;
}

QJsonObject QxTdSetNetworkTypeRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "setNetworkType" },
        { "type", m_networkType->marshalJson() },
    };
}
