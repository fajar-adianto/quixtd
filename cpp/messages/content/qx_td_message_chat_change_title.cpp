#include "qx_td_message_chat_change_title.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageChatChangeTitle::QxTdMessageChatChangeTitle(QObject *parent)
    : QxTdMessageContent(parent)
{
    setType(MESSAGE_CHAT_CHANGE_TITLE);
}

QString QxTdMessageChatChangeTitle::title() const
{
    return m_title;
}

void QxTdMessageChatChangeTitle::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageContent::unmarshalJson(json);
    m_title = json["title"].toString();
    m_typeText = qxTranslate("changed the chat title");
    emit contentChanged();
}
