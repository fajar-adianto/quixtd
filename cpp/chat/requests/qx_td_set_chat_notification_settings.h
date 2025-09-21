#ifndef QX_TD_SET_CHAT_NOTIFICATION_SETTINGS_H
#define QX_TD_SET_CHAT_NOTIFICATION_SETTINGS_H

#include <QObject>
#include "common/qx_td_request.h"

class QxTdNotificationSettings; // Forward declaration.

/**
 * @brief The QxTdSetChatNotificationSettings class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1set_chat_notification_settings.html
 */
class QxTdSetChatNotificationSettings : public QxTdOkRequest
{
    Q_OBJECT
    qint64 m_chatId;
    QxTdNotificationSettings *m_notificationSettings;

public:
    explicit QxTdSetChatNotificationSettings(QObject *parent = nullptr);

    /**
     * @brief setChatId
     * @param id of chat to close
     */
    void setChatId(const qint64 &id);

    void setNotificationSettings(QxTdNotificationSettings *settings);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();
};

#endif // QX_TD_SET_CHAT_NOTIFICATION_SETTINGS_H
