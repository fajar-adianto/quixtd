#include "qtdsearchchatmessagesrequest.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

QTdSearchChatMessagesRequest::QTdSearchChatMessagesRequest(QObject *parent)
    : QTdRequest(parent) {
}

void QTdSearchChatMessagesRequest::setChatId(const qint64 chatId) {
	m_chatId = chatId;
}

void QTdSearchChatMessagesRequest::setQuery(const QString &query) {
	m_query = query;
}

void QTdSearchChatMessagesRequest::setFromMessageId(const qint64 fromMessageId) {
	m_fromMessageId = fromMessageId;
}

void QTdSearchChatMessagesRequest::setOffset(const qint32 offset) {
    m_offset = offset;
}

void QTdSearchChatMessagesRequest::setLimit(const qint32 limit) {
    m_limit = limit;
}

void QTdSearchChatMessagesRequest::setMessageThreadId(const qint64 messageThreadId) {
	m_messageThreadId = messageThreadId;
}

QJsonObject QTdSearchChatMessagesRequest::marshalJson() {
    return QJsonObject{
        { "@type", "searchChatMessages" },
        { "chat_id", m_chatId },
        { "query", m_query },
        { "from_message_id", m_fromMessageId },
        { "offset", m_offset },
        { "limit", m_limit },
        { "message_thread_id", m_messageThreadId }
    };
}

QFuture<QTdResponse> QTdSearchChatMessagesRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::chat);
}
