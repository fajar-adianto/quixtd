#include "qx_td_message_document.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageDocument::QxTdMessageDocument(QObject *parent)
    : QxTdMessageContent(parent)
    , m_document(new QxTdDocument)
    , m_caption(new QxTdFormattedText)
{
    setType(MESSAGE_DOCUMENT);
}

QxTdDocument *QxTdMessageDocument::document() const
{
    return m_document.get();
}
QxTdFormattedText *QxTdMessageDocument::caption() const
{
    return m_caption.get();
}
void QxTdMessageDocument::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageContent::unmarshalJson(json);
    m_document->unmarshalJson(json["document"].toObject());
    m_caption->unmarshalJson(json["caption"].toObject());
    m_infoText = m_caption->text() != "" ? m_caption->oneLineText() : "";
    m_typeText = m_document->fileName() + (m_caption->text() != "" ? "," : "");
}
