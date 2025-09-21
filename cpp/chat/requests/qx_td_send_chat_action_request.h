#ifndef QX_TD_SEND_CHAT_ACTION_REQUEST_H
#define QX_TD_SEND_CHAT_ACTION_REQUEST_H

#include "common/qx_td_request.h"
#include "chat/qx_td_chat_action.h"
#include <QObject>

/**
 * @brief The QxTdSendChatActionRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1send_chat_action.html
 */
class QxTdSendChatActionRequest : public QxTdOkRequest
{
    Q_OBJECT
    qint64 m_chatId;

public:
    explicit QxTdSendChatActionRequest(QObject *parent = nullptr);
    void setChatId(const qint64 &id);
    void setAction(const QxTdChatAction &action);
    QJsonObject marshalJson();
};

#endif // QX_TD_SEND_CHAT_ACTION_REQUEST_H
