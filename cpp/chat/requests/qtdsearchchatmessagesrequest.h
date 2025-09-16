#ifndef QTDSEARCHCHATMESSAGESREQUEST_H
#define QTDSEARCHCHATMESSAGESREQUEST_H

#include <QObject>
#include <QList>

#include "common/qx_td_object.h"
#include "common/qtdrequest.h"
#include "client/qtdclient.h"
#include "messages/qtdmessagesender.h"

/**
 * @brief The QTdSearchChatMessagesRequest class
 *

* https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1search_chat_messages_request.html
 */
class QTdSearchChatMessagesRequest : public QTdRequest {
    Q_OBJECT
    Q_DISABLE_COPY(QTdSearchChatMessagesRequest)

public:
    explicit QTdSearchChatMessagesRequest(QObject *parent = nullptr);

    QJsonObject marshalJson() override;
    QFuture<QTdResponse> sendAsync() override;
    void setChatId(const qint64 chatId);
    void setQuery(const QString &query);
    //void setSenderId(QTdMessageSender *senderId);
    void setFromMessageId(const qint64 fromMessageId);
    void setOffset(const qint32 offset);
    void setLimit(const qint32 limit);
    void setMessageThreadId(const qint64 messageThreadId);

private:
    qint64 m_chatId;
    QString m_query;
    //QScopedPointer<QTdMessageSender> m_senderId;
    qint64 m_fromMessageId;
    qint32 m_offset;
    qint32 m_limit;
    qint64 m_messageThreadId;
};

#endif // QTDSEARCHCHATMESSAGESREQUEST_H
