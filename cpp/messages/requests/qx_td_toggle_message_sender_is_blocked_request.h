#ifndef QX_TD_TOGGLE_MESSAGE_SENDER_IS_BLOCKED_H
#define QX_TD_TOGGLE_MESSAGE_SENDER_IS_BLOCKED_H

#include "common/qx_td_request.h"
#include "../qx_td_message_sender.h"

class QxTdToggleMessageSenderIsBlockedRequest : public QxTdOkRequest
{
    Q_OBJECT

public:
    explicit QxTdToggleMessageSenderIsBlockedRequest(QObject *parent = nullptr);
    void setSenderId(QxTdMessageSender *senderId);
    void setIsBlocked(const bool &isBlocked);
    QJsonObject marshalJson();

private:
    Q_DISABLE_COPY(QxTdToggleMessageSenderIsBlockedRequest)
    QxTdMessageSender *m_senderId;
    bool m_isBlocked;
};

#endif // QX_TD_TOGGLE_MESSAGE_SENDER_IS_BLOCKED_H
