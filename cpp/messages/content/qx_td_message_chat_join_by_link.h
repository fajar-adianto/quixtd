#ifndef QX_TD_MESSAGE_CHAT_JOIN_BY_LINK_H
#define QX_TD_MESSAGE_CHAT_JOIN_BY_LINK_H

#include "messages/qx_td_message_content.h"

/**
 * @brief The QxTdMessageChatJoinByLink class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_chat_join_by_link.html
 */
class QxTdMessageChatJoinByLink : public QxTdMessageContent
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageChatJoinByLink cannot be created in QML.")
    Q_DISABLE_COPY(QxTdMessageChatJoinByLink)
public:
    explicit QxTdMessageChatJoinByLink(QObject *parent = nullptr);
};

#endif // QX_TD_MESSAGE_CHAT_JOIN_BY_LINK_H
