#include "qx_td_search_chat_messages_request.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

QxTdSearchChatMessagesRequest::QxTdSearchChatMessagesRequest(QObject *parent)
    : QxTdRequest(parent)
{
    // Intentionally left empty.
}

void QxTdSearchChatMessagesRequest::setChatId(const qint64 chatId) {
	m_chatId = chatId;
}

void QxTdSearchChatMessagesRequest::setQuery(const QString &query) {
	m_query = query;
}

void QxTdSearchChatMessagesRequest::setFromMessageId(const qint64 fromMessageId) {
	m_fromMessageId = fromMessageId;
}

void QxTdSearchChatMessagesRequest::setOffset(const qint32 offset) {
    m_offset = offset;
}

void QxTdSearchChatMessagesRequest::setLimit(const qint32 limit) {
    m_limit = limit;
}

void QxTdSearchChatMessagesRequest::setMessageThreadId(const qint64 messageThreadId) {
	m_messageThreadId = messageThreadId;
}

QJsonObject QxTdSearchChatMessagesRequest::marshalJson() {
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

QFuture<QxTdResponse> QxTdSearchChatMessagesRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::chat);
}
