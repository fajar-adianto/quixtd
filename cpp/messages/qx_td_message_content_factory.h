#ifndef QX_TD_MESSAGE_CONTENT_FACTORY_H
#define QX_TD_MESSAGE_CONTENT_FACTORY_H

#include <QJsonObject>
#include <QObject>

class QxTdMessageContent; // Forward declaration.

struct QxTdMessageContentFactory
{
    static QxTdMessageContent *create(const QJsonObject &json, QObject *parent = nullptr);
};

#endif // QX_TD_MESSAGE_CONTENT_FACTORY_H
