#include "qx_td_input_message_voice_note.h"

QxTdInputMessageVoiceNote::QxTdInputMessageVoiceNote(QObject *parent)
    : QxTdInputMessageContent(parent)
    , m_voiceNote(QString())
    , m_duration(0)
    , m_waveform(QString())
    , m_caption(QString())
    , m_captionEntities(QJsonArray())
{
    // Intentionally left empty.
}

void QxTdInputMessageVoiceNote::setAttachmentPath(const QString &url)
{
    m_voiceNote = url;
}
void QxTdInputMessageVoiceNote::setDuration(const qint32 &duration)
{
    m_duration = duration;
}
void QxTdInputMessageVoiceNote::setWaveform(const QString &waveform)
{
    m_waveform = waveform;
}
void QxTdInputMessageVoiceNote::setCaption(const QString &caption)
{
    m_caption = caption;
}
void QxTdInputMessageVoiceNote::setCaptionEntities(const QJsonArray &entities)
{
    m_captionEntities = entities;
}
QJsonObject QxTdInputMessageVoiceNote::marshalJson()
{
    return QJsonObject {
        { "@type", "inputMessageVoiceNote" },
        { "voice_note", QJsonObject { { "@type", "inputFileGenerated" }, { "original_path", m_voiceNote }, { "conversion", "record_voice" } } },
        { "caption", QJsonObject { { "@type", "formattedText" }, { "text", m_caption }, { "entities", m_captionEntities } } },
    };
}
