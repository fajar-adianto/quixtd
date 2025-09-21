#ifndef QX_TD_CHAT_ACTION_FACTORY_H
#define QX_TD_CHAT_ACTION_FACTORY_H

#include <QObject>
#include <QJsonObject>

class QxTdChatAction; // Forward declaration.

struct QxTdChatActionFactory
{
    static QxTdChatAction *create(const QJsonObject &json, QObject *parent = nullptr);
};

#endif // QX_TD_CHAT_ACTION_FACTORY_H
