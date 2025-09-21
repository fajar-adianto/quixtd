#include "qx_td_message_chat_join_by_link.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageChatJoinByLink::QxTdMessageChatJoinByLink(QObject *parent)
    : QxTdMessageContent(parent)
{
    setType(MESSAGE_CHAT_JOIN_BY_LINK);
    m_typeText = qxTranslate("joined the group via the public link");
}
