#include "qx_td_input_message_audio.h"

QxTdInputMessageAudio::QxTdInputMessageAudio(QObject *parent)
    : QxTdInputMessageContentAttachmentCaption(parent)
    , m_audio(QString())
    , m_caption(QString())
    , m_captionEntities(QJsonArray())
{
    // Intentionally left empty.
}

void QxTdInputMessageAudio::setAttachmentPath(const QString &url)
{

    m_audio = url;
}
void QxTdInputMessageAudio::setCaption(const QString &caption)
{
    m_caption = caption;
}
void QxTdInputMessageAudio::setCaptionEntities(const QJsonArray &entities)
{
    m_captionEntities = entities;
}
QJsonObject QxTdInputMessageAudio::marshalJson()
{
    return QJsonObject{
        { "@type", "inputMessageAudio" },
        { "audio", QJsonObject{
                           { "@type", "inputFileGenerated" },
                           { "original_path", m_audio },
                           { "conversion", "attachment" } } },
        { "caption", QJsonObject{ { "@type", "formattedText" }, { "text", m_caption }, { "entities", m_captionEntities } } },
    };
}
