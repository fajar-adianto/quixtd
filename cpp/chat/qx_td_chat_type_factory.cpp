#include "qx_td_chat_type_factory.h"
#include "qx_td_basic_group_chat.h"
#include "qx_td_chat_list.h"
#include "qx_td_secret_chat.h"
#include "qx_td_super_group_chat.h"

QxTdChatList *QxTdChatFactory::createList(const QJsonObject &json, QObject *parent)
{
    const QString list = json["@type"].toString();
    QxTdChatList *chatList = nullptr;
    if (list == "chatListMain") {
        chatList = new QxTdChatListMain(parent);
    } else if (list == "chatListArchive") {
        chatList = new QxTdChatListArchive(parent);
    } else if (list == "chatListFilter") {
        chatList = new QxTdChatListFilter(parent);
    } else {
        chatList = new QxTdChatList(parent);
    }
    return chatList;
}
QxTdChatType *QxTdChatFactory::createType(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    QxTdChatType *chatType = nullptr;
    if (type == "chatTypeBasicGroup") {
        chatType = new QxTdChatTypeBasicGroup(parent);
    } else if (type == "chatTypePrivate") {
        chatType = new QxTdChatTypePrivate(parent);
    } else if (type == "chatTypeSecret") {
        chatType = new QxTdChatTypeSecret(parent);
    } else if (type == "chatTypeSupergroup") {
        chatType = new QxTdChatTypeSuperGroup(parent);
    }
    if (chatType) {
        chatType->unmarshalJson(json);
    }
    return chatType;
}

QxTdChat *QxTdChatFactory::createChat(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    QxTdChat *chat = nullptr;
    if (type == "chatTypeBasicGroup") {
        chat = new QxTdBasicGroupChat(parent);
    } else if (type == "chatTypeSecret") {
        chat = new QxTdSecretChat(parent);
    } else if (type == "chatTypeSupergroup") {
        chat = new QxTdSuperGroupChat(parent);
    } else {
        chat = new QxTdChat(parent);
    }
    return chat;
}
