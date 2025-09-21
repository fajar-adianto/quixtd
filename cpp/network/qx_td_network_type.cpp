#include "qx_td_network_type.h"

QxTdNetworkType::QxTdNetworkType(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

QxTdNetworkTypeMobile::QxTdNetworkTypeMobile(QObject *parent)
    : QxTdNetworkType(parent)
{
    setType(NETWORK_TYPE_MOBILE);
}

QxTdNetworkTypeMobileRoaming::QxTdNetworkTypeMobileRoaming(QObject *parent)
    : QxTdNetworkType(parent)
{
    setType(NETWORK_TYPE_MOBILE_ROAMING);
}

QxTdNetworkTypeNone::QxTdNetworkTypeNone(QObject *parent)
    : QxTdNetworkType(parent)
{
    setType(NETWORK_TYPE_NONE);
}

QxTdNetworkTypeOther::QxTdNetworkTypeOther(QObject *parent)
    : QxTdNetworkType(parent)
{
    setType(NETWORK_TYPE_OTHER);
}

QxTdNetworkTypeWiFi::QxTdNetworkTypeWiFi(QObject *parent)
    : QxTdNetworkType(parent)
{
    setType(NETWORK_TYPE_WIFI);
}
