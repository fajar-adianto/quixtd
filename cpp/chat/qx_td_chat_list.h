#ifndef QX_TD_CHAT_LIST_H
#define QX_TD_CHAT_LIST_H

#include "common/qx_td_object.h"

/**
 * @brief The QxTdChatList class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_chat_list.html
 */
class QxTdChatList : public QxTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatList)
public:
    explicit QxTdChatList(QObject *parent = nullptr);
};

/**
 * @brief The QxTdChatListMain class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_list_main.html
 */
class QxTdChatListMain : public QxTdChatList
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatListMain)
public:
    explicit QxTdChatListMain(QObject *parent = nullptr);
};

/**
 * @brief The QxTdChatListArchive class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_list_archive.html
 */
class QxTdChatListArchive : public QxTdChatList
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatListArchive)
public:
    explicit QxTdChatListArchive(QObject *parent = nullptr);
};

/**
 * @brief The QxTdChatListFilter class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_list_filter.html
 */
class QxTdChatListFilter : public QxTdChatList
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatListFilter)
public:
    explicit QxTdChatListFilter(QObject *parent = nullptr);
};
#endif // QX_TD_CHAT_LIST_H
