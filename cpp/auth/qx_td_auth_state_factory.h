#ifndef QX_TD_AUTH_STATE_FACTORY_H
#define QX_TD_AUTH_STATE_FACTORY_H

#include <QJsonObject>
#include <QObject>

class QxTdAuthState; // Forward declaration.

struct QxTdAuthStateFactory
{
    static QxTdAuthState *create(const QJsonObject &data, QObject *parent);
};

#endif // QX_TD_AUTH_STATE_FACTORY_H
