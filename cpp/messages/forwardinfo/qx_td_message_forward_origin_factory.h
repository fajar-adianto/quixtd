#ifndef QX_TD_MESSAGE_FORWARD_ORIGIN_FACTORY_H
#define QX_TD_MESSAGE_FORWARD_ORIGIN_FACTORY_H

#include <QJsonObject>
#include <QObject>

class QxTdMessageForwardOrigin; // Forward declaration.

struct QxTdMessageForwardOriginFactory
{
    static QxTdMessageForwardOrigin *create(const QJsonObject &json, QObject *parent);
};

#endif // QX_TD_MESSAGE_FORWARD_ORIGIN_FACTORY_H
