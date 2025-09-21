#include "qx_td_edit_message_text_request.h"
#include "client/qx_td_client.h"

QxTdEditMessageTextRequest::QxTdEditMessageTextRequest(QObject *parent)
    : QxTdRequest(parent)
    , m_chatId(0)
    , m_messageId(0)
    , m_text(QString())
    , m_entities(QJsonArray())
{
    // Intentionally left empty.
}

void QxTdEditMessageTextRequest::setText(const QString &text)
{
    m_text = text;
}

void QxTdEditMessageTextRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QxTdEditMessageTextRequest::setMessageId(const qint64 &id)
{
    m_messageId = id;
}

void QxTdEditMessageTextRequest::setEntities(const QJsonArray &entities)
{
    m_entities = entities;
}

QJsonObject QxTdEditMessageTextRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "editMessageText" },
        { "chat_id", m_chatId },
        { "message_id", m_messageId },
        { "input_message_content", QJsonObject{
                                           { "@type", "inputMessageText" },
                                           { "text", QJsonObject{
                                                             { "@type", "formattedText" },
                                                             { "text", m_text },
                                                             { "entities", m_entities } } },
                                           { "disable_web_page_preview", false },
                                           { "clear_draft", true } } }
    };
}

QFuture<QxTdResponse> QxTdEditMessageTextRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::message);
}
