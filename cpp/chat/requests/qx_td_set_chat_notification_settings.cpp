#include "qx_td_set_chat_notification_settings.h"
#include "../../notifications/qx_td_notification_settings.h"

QxTdSetChatNotificationSettings::QxTdSetChatNotificationSettings(QObject *parent)
    : QxTdOkRequest(parent)
    , m_chatId(0)
{
    // Intentionally left empty.
}

void QxTdSetChatNotificationSettings::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QxTdSetChatNotificationSettings::setNotificationSettings(QxTdNotificationSettings *settings)
{
    m_notificationSettings = settings;
}

QJsonObject QxTdSetChatNotificationSettings::marshalJson()
{
    return QJsonObject{
        { "@type", "setChatNotificationSettings" },
        { "chat_id", m_chatId },
        { "notification_settings", m_notificationSettings->marshalJson() }
    };
}
