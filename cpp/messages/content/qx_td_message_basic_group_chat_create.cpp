#include "qx_td_message_basic_group_chat_create.h"
#include <QDebug>
#include <QJsonObject>
#include "utils/qx_td_translate_tools.h"

QxTdMessageBasicGroupChatCreate::QxTdMessageBasicGroupChatCreate(QObject *parent)
    : QxTdMessageChatAddMembers(parent)
{
    setType(MESSAGE_BASIC_GROUP_CHAT_CREATE);
}

QString QxTdMessageBasicGroupChatCreate::title() const
{
    return m_title;
}

void QxTdMessageBasicGroupChatCreate::unmarshalJson(const QJsonObject &json)
{
    m_title = json["title"].toString();
    emit titleChanged();
    QxTdMessageChatAddMembers::unmarshalJson(json);
    m_typeText = qxTranslate("created this group");
    emit membersChanged();
}
