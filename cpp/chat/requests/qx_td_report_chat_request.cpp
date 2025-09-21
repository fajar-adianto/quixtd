#include "qx_td_report_chat_request.h"
#include <QJsonArray>

#include "qx_td_chat_report_reason.h"

QxTdReportChatRequest::QxTdReportChatRequest(QObject *parent)
    : QxTdOkRequest(parent)
{
    // Intentionally left empty.
}

void QxTdReportChatRequest::setChatId(const QString &id) {
    m_chatId = id;
}

void QxTdReportChatRequest::setMessageIds(const QList<qint64> &messageIds) {
    m_messageIds = messageIds;
}

void QxTdReportChatRequest::setReason(QxTdChatReportReason *reason) {
    m_reason = reason;
}

void QxTdReportChatRequest::setText(const QString &text) {
    m_text = text;
}

QJsonObject QxTdReportChatRequest::marshalJson()
{
    QJsonArray json_messages;
    for (auto &m_messageId : m_messageIds)
        json_messages.append(m_messageId);
    return QJsonObject{
        { "@type", "reportChat" },
        { "chat_id", m_chatId },
        { "message_ids", json_messages },
        { "reason", m_reason->marshalJson() },
        { "text", m_text }
    };
}
