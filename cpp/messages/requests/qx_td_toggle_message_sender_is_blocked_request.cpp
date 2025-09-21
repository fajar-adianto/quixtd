#include "qx_td_toggle_message_sender_is_blocked_request.h"
#include "client/qx_td_client.h"

QxTdToggleMessageSenderIsBlockedRequest::QxTdToggleMessageSenderIsBlockedRequest(QObject *parent)
    : QxTdOkRequest(parent)
    , m_senderId(nullptr)
    , m_isBlocked(false)
{
    // Intentionally left empty.
}

void QxTdToggleMessageSenderIsBlockedRequest::setSenderId(QxTdMessageSender *senderId)
{
    m_senderId = senderId;
}

void QxTdToggleMessageSenderIsBlockedRequest::setIsBlocked(const bool &isBlocked)
{
    m_isBlocked = isBlocked;
}

QJsonObject QxTdToggleMessageSenderIsBlockedRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "toggleMessageSenderIsBlocked" },
        { "is_blocked", m_isBlocked },
        { "sender_id", m_senderId->marshalJson() }
    };
}
