#ifndef QX_TD_CONNECTION_STATE_FACTORY_H
#define QX_TD_CONNECTION_STATE_FACTORY_H

#include <QJsonObject>
#include <QObject>

class QxTdConnectionState; // Forward declaration.

struct QxTdConnectionStateFactory
{
    static QxTdConnectionState *create(const QJsonObject &json, QObject *parent);
};

#endif // QX_TD_CONNECTION_STATE_FACTORY_H
