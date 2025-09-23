#include "qx_td_message_voice_note.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageVoiceNote::QxTdMessageVoiceNote(QObject *parent)
    : QxTdMessageContent(parent)
    , m_voiceNote(new QxTdVoiceNote)
    , m_caption(new QxTdFormattedText)
    , m_isListened(new bool)
{
    setType(MESSAGE_VOICE_NOTE);
}

QxTdVoiceNote *QxTdMessageVoiceNote::voiceNote() const
{
    return m_voiceNote.get();
}
QxTdFormattedText *QxTdMessageVoiceNote::caption() const
{
    return m_caption.get();
}
bool QxTdMessageVoiceNote::isListened() const
{
    return m_isListened;
}
void QxTdMessageVoiceNote::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageContent::unmarshalJson(json);
    m_voiceNote->unmarshalJson(json["voice_note"].toObject());
    m_caption->unmarshalJson(json["caption"].toObject());
    m_isListened = json["is_listened"].toBool();
    m_infoText = m_caption->text() != "" ? m_caption->text() : "";
    m_typeText = m_caption->text() != "" ? qxTranslate("Voice message,") : qxTranslate("Voice message");
}
