#ifndef QX_TD_JOIN_CHAT_REQUEST_H
#define QX_TD_JOIN_CHAT_REQUEST_H

#include <QObject>
#include "common/qx_td_request.h"
#include "common/qx_td_int.h"

/**
 * @brief The QxTdJoinChatRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1join_chat.html
 */
class QxTdJoinChatRequest : public QxTdOkRequest
{
    Q_OBJECT
public:
    explicit QxTdJoinChatRequest(QObject *parent = nullptr);

    void setChatId(const QString &chatId);
    void setChatId(const qint64 &chatId);
    QJsonObject marshalJson();

private:
    QxTdInt64 m_chatId;
};

#endif // QX_TD_JOIN_CHAT_REQUEST_H
