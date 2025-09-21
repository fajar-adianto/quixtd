#include "qx_td_message_chat_upgrade_from.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageChatUpgradeFrom::QxTdMessageChatUpgradeFrom(QObject *parent)
    : QxTdMessageContent(parent)
{
    setType(MESSAGE_CHAT_UPGRADE_FROM);
}

QString QxTdMessageChatUpgradeFrom::title() const
{
    return m_title;
}

QString QxTdMessageChatUpgradeFrom::qmlBasicGroupId() const
{
    return m_groupdId.toQmlValue();
}

qint64 QxTdMessageChatUpgradeFrom::basicGroupId() const
{
    return m_groupdId.value();
}

void QxTdMessageChatUpgradeFrom::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageContent::unmarshalJson(json);
    m_title = json["title"].toString();
    m_groupdId = json["basic_group_id"];
    m_typeText = qxTranslate("upgraded to supergroup");
    emit contentChanged();
}
