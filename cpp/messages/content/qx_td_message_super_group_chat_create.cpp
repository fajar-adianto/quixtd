#include "qx_td_message_super_group_chat_create.h"
#include "utils/qx_td_await.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageSuperGroupChatCreate::QxTdMessageSuperGroupChatCreate(QObject *parent)
    : QxTdMessageContent(parent)
{
    setType(MESSAGE_SUPER_GROUP_CHAT_CREATE);
}

QString QxTdMessageSuperGroupChatCreate::title() const
{
    return m_title;
}

void QxTdMessageSuperGroupChatCreate::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageContent::unmarshalJson(json);
    m_title = json["title"].toString();
    m_typeText = qxTranslate("created this group");
    emit titleChanged();
}
