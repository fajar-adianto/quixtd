#ifndef QX_TD_FORWARD_MESSAGES_REQUEST_H
#define QX_TD_FORWARD_MESSAGES_REQUEST_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdForwardMessagesRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1forward_messages.html
 */
class QxTdForwardMessagesRequest : public QxTdRequest
{
    Q_OBJECT
public:
    explicit QxTdForwardMessagesRequest(QObject *parent = nullptr);

    void setChatId(const qint64 chatId);
    void setFromChatId(const qint64 fromChatId);
    void setMessageIds(const QList<qint64> &messageIds);

    QJsonObject marshalJson();

    QFuture<QxTdResponse> sendAsync();

private:
    Q_DISABLE_COPY(QxTdForwardMessagesRequest)
    qint64 m_chatId, m_fromChatId;
    QList<qint64> m_messageIds;
};

#endif // QX_TD_FORWARD_MESSAGES_REQUEST_H
