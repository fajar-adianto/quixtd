#include "qx_td_message_send_options.h"

QxTdMessageSendOptions::QxTdMessageSendOptions(QObject *parent)
    : QxTdObject(parent)
    , m_disableNotifications(false)
    , m_sendDate(0)
{
    setType(MESSAGE_SEND_OPTIONS);
}

void QxTdMessageSendOptions::setDisableNotifications(const bool value)
{
    m_disableNotifications = value;
}

void QxTdMessageSendOptions::setSendDate(const qint32 value)
{
    m_sendDate = value;
}

QJsonObject QxTdMessageSendOptions::marshalJson()
{
    auto result = QJsonObject{
        { "@type", "messageSendOptions" },
        { "disable_notification", m_disableNotifications }
    };
    if (m_sendDate > 0) {
        result.insert("scheduling_state", QJsonObject{
            { "@type", "messageSchedulingStateSendAtDate" },
            { "send_date", m_sendDate }
        });
    } else if (m_sendDate == -1) {
        result.insert("scheduling_state", QJsonObject{
            { "@type", "messageSchedulingStateSendWhenOnline" }
        });
    }
    return result;
}
