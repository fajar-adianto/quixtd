#ifndef QX_TD_LEAVE_CHAT_REQUEST_H
#define QX_TD_LEAVE_CHAT_REQUEST_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdLeaveChatRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1leave_chat.html
 */
class QxTdLeaveChatRequest : public QxTdOkRequest
{
    Q_OBJECT
    qint64 m_chatId;

public:
    explicit QxTdLeaveChatRequest(QObject *parent = nullptr);
    void setChatId(const qint64 &id);
    QJsonObject marshalJson();
};

#endif // QX_TD_LEAVE_CHAT_REQUEST_H
