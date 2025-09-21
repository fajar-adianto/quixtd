#include "qx_td_send_chat_action_request.h"

QxTdSendChatActionRequest::QxTdSendChatActionRequest(QObject *parent)
    : QxTdOkRequest(parent)
    , m_chatId(0)
{
    // Intentionally left empty.
}

void QxTdSendChatActionRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QxTdSendChatActionRequest::setAction(const QxTdChatAction &id)
{
    Q_UNUSED(id);
    // Reserved for future use.
}

QJsonObject QxTdSendChatActionRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "sendChatAction" },
        { "chat_id", m_chatId },
        {
                "action", QJsonObject{
                                  { "@type", "chatActionTyping" },
                          },
        }
    };
}
