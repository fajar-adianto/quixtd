#include "chat/qx_td_chat_list.h"

QxTdChatList::QxTdChatList(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

QxTdChatListMain::QxTdChatListMain(QObject *parent)
    : QxTdChatList(parent)
{
    setType(CHAT_LIST_MAIN);
}

QxTdChatListArchive::QxTdChatListArchive(QObject *parent)
    : QxTdChatList(parent)
{
    setType(CHAT_LIST_ARCHIVE);
}

QxTdChatListFilter::QxTdChatListFilter(QObject *parent)
    : QxTdChatList(parent)
{
    setType(CHAT_LIST_FILTER);
}

