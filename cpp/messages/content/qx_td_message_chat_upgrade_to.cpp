#include "qx_td_message_chat_upgrade_to.h"
#include "utils/qx_td_await.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageChatUpgradeTo::QxTdMessageChatUpgradeTo(QObject *parent)
    : QxTdMessageContent(parent)

{
    setType(MESSAGE_CHAT_UPGRADE_TO);
}

QString QxTdMessageChatUpgradeTo::qmlSuperGroupId() const
{
    return m_sgId.toQmlValue();
}

qint64 QxTdMessageChatUpgradeTo::superGroupId() const
{
    return m_sgId.value();
}

void QxTdMessageChatUpgradeTo::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageContent::unmarshalJson(json);
    if (json.isEmpty()) {
        return;
    }
    m_sgId = json["supergroup_id"];
    m_typeText = qxTranslate("upgraded to supergroup");
    emit contentChanged();
}
