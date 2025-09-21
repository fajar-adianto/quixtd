#include "qx_td_edit_message_caption_request.h"
#include "client/qx_td_client.h"

QxTdEditMessageCaptionRequest::QxTdEditMessageCaptionRequest(QObject *parent)
    : QxTdRequest(parent)
    , m_chatId(0)
    , m_messageId(0)
    , m_text(QString())
    , m_entities(QJsonArray())
{
    // Intentionally left empty.
}

void QxTdEditMessageCaptionRequest::setText(const QString &text)
{
    m_text = text;
}

void QxTdEditMessageCaptionRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QxTdEditMessageCaptionRequest::setMessageId(const qint64 &id)
{
    m_messageId = id;
}

void QxTdEditMessageCaptionRequest::setEntities(const QJsonArray &entities)
{
    m_entities = entities;
}

QJsonObject QxTdEditMessageCaptionRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "editMessageCaption" },
        { "chat_id", m_chatId },
        { "message_id", m_messageId },
        { "caption", QJsonObject{
                             { "@type", "formattedText" },
                             { "text", m_text },
                             { "entities", m_entities } } },
        { "disable_web_page_preview", false },
        { "clear_draft", true }
    };
}

QFuture<QxTdResponse> QxTdEditMessageCaptionRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::message);
}
