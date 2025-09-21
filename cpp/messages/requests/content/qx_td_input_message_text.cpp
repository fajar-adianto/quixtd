#include "qx_td_input_message_text.h"
#include "messages/content/qx_td_formatted_text.h"

QxTdInputMessageText::QxTdInputMessageText(QObject *parent)
    : QxTdInputMessageContent(parent)
    , m_text(QString())
    , m_entities(QJsonArray())
    , m_disable_web_page_preview(new bool)
    , m_clear_draft(false)
{
    // Intentionally left empty.
}

void QxTdInputMessageText::setText(const QString &text)
{
    m_text = text;
}
void QxTdInputMessageText::setClearDraft(const bool clear_draft)
{
    m_clear_draft = clear_draft;
}
void QxTdInputMessageText::setEntities(const QJsonArray &entities)
{
    m_entities = entities;
}
QJsonObject QxTdInputMessageText::marshalJson()
{
    return QJsonObject {
        { "@type", "inputMessageText" },
        { "text", QJsonObject { { "@type", "formattedText" }, { "text", m_text }, { "entities", m_entities } } },
        { "disable_web_page_preview", false },
        { "clear_draft", m_clear_draft }
    };
}

QString QxTdInputMessageText::text() const
{
    return m_text;
}
bool QxTdInputMessageText::clearDraft() const
{
    return m_clear_draft;
}
bool QxTdInputMessageText::disableWebPagePreview() const
{
    return m_disable_web_page_preview;
}

void QxTdInputMessageText::unmarshalJson(const QJsonObject &json)
{
    QxTdInputMessageContent::unmarshalJson(json);
    m_clear_draft = json["clear_draft"].toBool();
    m_disable_web_page_preview = json["m_disable_web_page_preview"].toBool();
    QScopedPointer<QxTdFormattedText> formattedText(new QxTdFormattedText);
    formattedText->unmarshalJson(json["text"].toObject());
    m_text = formattedText->text();
    emit inputMessageTextChanged();
}
