#ifndef QX_TD_CHAT_TYPE_FACTORY_H
#define QX_TD_CHAT_TYPE_FACTORY_H

#include <QJsonObject>
#include <QObject>

class QxTdChatList; // Forward declaration.
class QxTdChatType; // Forward declaration.
class QxTdChat; // Forward declaration.

struct QxTdChatFactory
{
    static QxTdChatList *createList(const QJsonObject &json, QObject *parent);
    static QxTdChatType *createType(const QJsonObject &json, QObject *parent);
    static QxTdChat *createChat(const QJsonObject &json, QObject *parent = nullptr);
};

#endif // QX_TD_CHAT_TYPE_FACTORY_H
