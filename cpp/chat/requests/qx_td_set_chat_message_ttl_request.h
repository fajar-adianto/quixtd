#ifndef QX_TD_SET_CHAT_MESSAGE_TTL_REQUEST_H
#define QX_TD_SET_CHAT_MESSAGE_TTL_REQUEST_H

#include "common/qx_td_request.h"
#include <QObject>

/**
 * @brief The QxTdSetChatMessageTtlRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1send_chat_set_ttl_message.html
 */
class QxTdSetChatMessageTtlRequest : public QxTdOkRequest
{
    Q_OBJECT
    qint64 m_chatId;
    qint32 m_ttl;

public:
    explicit QxTdSetChatMessageTtlRequest(QObject *parent = nullptr);
    void setChatId(const qint64 &id);
    void setTTL(const qint32 &ttl);
    QJsonObject marshalJson();
};

#endif // QX_TD_SET_CHAT_MESSAGE_TTL_REQUEST_H
