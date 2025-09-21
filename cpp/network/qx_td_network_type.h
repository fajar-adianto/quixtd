#ifndef QX_TD_NETWORK_TYPE_H
#define QX_TD_NETWORK_TYPE_H

#include "common/qx_td_object.h"
#include <QObject>

class QxTdNetworkType : public QxTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdNetworkType)
public:
    explicit QxTdNetworkType(QObject *parent = nullptr);
};

class QxTdNetworkTypeMobile : public QxTdNetworkType
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdNetworkTypeMobile)
public:
    explicit QxTdNetworkTypeMobile(QObject *parent = nullptr);
};

class QxTdNetworkTypeMobileRoaming : public QxTdNetworkType
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdNetworkTypeMobileRoaming)
public:
    explicit QxTdNetworkTypeMobileRoaming(QObject *parent = nullptr);
};

class QxTdNetworkTypeNone : public QxTdNetworkType
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdNetworkTypeNone)
public:
    explicit QxTdNetworkTypeNone(QObject *parent = nullptr);
};

class QxTdNetworkTypeOther : public QxTdNetworkType
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdNetworkTypeOther)
public:
    explicit QxTdNetworkTypeOther(QObject *parent = nullptr);
};

class QxTdNetworkTypeWiFi : public QxTdNetworkType
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdNetworkTypeWiFi)
public:
    explicit QxTdNetworkTypeWiFi(QObject *parent = nullptr);
};

#endif // QX_TD_NETWORK_TYPE_H
