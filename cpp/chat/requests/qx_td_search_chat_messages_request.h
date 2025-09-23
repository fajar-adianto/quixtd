#ifndef QX_TD_SEARCH_CHAT_MESSAGES_REQUEST_H
#define QX_TD_SEARCH_CHAT_MESSAGES_REQUEST_H

#include <QList>

#include "common/qx_td_request.h"
#include "client/qx_td_client.h"
// #include "messages/qx_td_message_sender.h"

/**
 * @brief The QxTdSearchChatMessagesRequest class
 *

* https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1search_chat_messages_request.html
 */
class QxTdSearchChatMessagesRequest : public QxTdRequest {
    Q_OBJECT
    Q_DISABLE_COPY(QxTdSearchChatMessagesRequest)

public:
    explicit QxTdSearchChatMessagesRequest(QObject *parent = nullptr);

    QJsonObject marshalJson() override;
    QFuture<QxTdResponse> sendAsync() override;
    void setChatId(const qint64 chatId);
    void setQuery(const QString &query);
    //void setSenderId(QxTdMessageSender *senderId);
    void setFromMessageId(const qint64 fromMessageId);
    void setOffset(const qint32 offset);
    void setLimit(const qint32 limit);
    void setMessageThreadId(const qint64 messageThreadId);

private:
    qint64 m_chatId;
    QString m_query;
    //std::unique_ptr<QxTdMessageSender> m_senderId;
    qint64 m_fromMessageId;
    qint32 m_offset;
    qint32 m_limit;
    qint64 m_messageThreadId;
};

#endif // QX_TD_SEARCH_CHAT_MESSAGES_REQUEST_H
