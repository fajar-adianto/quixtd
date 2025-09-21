#include "qx_td_input_message_document.h"

QxTdInputMessageDocument::QxTdInputMessageDocument(QObject *parent)
    : QxTdInputMessageContentAttachmentCaption(parent)
    , m_document(QString())
    , m_caption(QString())
    , m_captionEntities(QJsonArray())
{
    // Intentionally left empty.
}

void QxTdInputMessageDocument::setAttachmentPath(const QString &url)
{

    m_document = url;
}

void QxTdInputMessageDocument::setCaption(const QString &caption)
{
    m_caption = caption;
}

void QxTdInputMessageDocument::setCaptionEntities(const QJsonArray &entities)
{
    m_captionEntities = entities;
}

QJsonObject QxTdInputMessageDocument::marshalJson()
{
    qDebug() << "inputMessageDocument";
    return QJsonObject{
        { "@type", "inputMessageDocument" },
        { "document", QJsonObject{
                           { "@type", "inputFileGenerated" },
                           { "original_path", m_document },
                           { "conversion", "attachment" } } },
        { "caption", QJsonObject{ { "@type", "formattedText" }, { "text", m_caption }, { "entities", m_captionEntities } } },
    };
}
