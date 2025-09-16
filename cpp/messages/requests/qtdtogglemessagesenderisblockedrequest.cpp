#include "qtdtogglemessagesenderisblockedrequest.h"
#include "client/qtdclient.h"

QTdToggleMessageSenderIsBlockedRequest::QTdToggleMessageSenderIsBlockedRequest(QObject *parent)
    : QTdOkRequest(parent)
    , m_senderId(Q_NULLPTR)
    , m_isBlocked(false)
{
}

void QTdToggleMessageSenderIsBlockedRequest::setSenderId(QTdMessageSender *senderId)
{
    m_senderId = senderId;
}

void QTdToggleMessageSenderIsBlockedRequest::setIsBlocked(const bool &isBlocked)
{
    m_isBlocked = isBlocked;
}

QJsonObject QTdToggleMessageSenderIsBlockedRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "toggleMessageSenderIsBlocked" },
        { "is_blocked", m_isBlocked },
        { "sender_id", m_senderId->marshalJson() }
    };
}
