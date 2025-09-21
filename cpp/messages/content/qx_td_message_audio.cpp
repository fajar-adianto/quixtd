#include "qx_td_message_audio.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageAudio::QxTdMessageAudio(QObject *parent)
    : QxTdMessageContent(parent)
    , m_audio(new QxTdAudio)
    , m_caption(new QxTdFormattedText)
{
    setType(MESSAGE_AUDIO);
}

QxTdAudio *QxTdMessageAudio::audio() const
{
    return m_audio.data();
}
QxTdFormattedText *QxTdMessageAudio::caption() const
{
    return m_caption.data();
}
void QxTdMessageAudio::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageContent::unmarshalJson(json);
    m_audio->unmarshalJson(json["audio"].toObject());
    m_caption->unmarshalJson(json["caption"].toObject());
    m_infoText = m_caption->text() != "" ? m_caption->oneLineText() : "";
    m_typeText = QString("%1 - %2%3").arg(m_audio->performer(), m_audio->title(), m_caption->text() != "" ? "," : "");
    m_infoImageUrl = QUrl("file://" + m_audio->albumCoverThumbnail()->file()->local()->path());
}
