#ifndef QX_TD_USER_STATUS_FACTORY_H
#define QX_TD_USER_STATUS_FACTORY_H

#include <QJsonObject>
#include <QObject>

class QxTdUserStatus; // Forward declaration.

struct QxTdUserStatusFactory
{
    static QxTdUserStatus *create(const QJsonObject &json, QObject *parent);
};

#endif // QX_TD_USER_STATUS_FACTORY_H
