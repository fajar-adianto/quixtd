#include "qx_td_voice_note.h"
#include <QTime>

QxTdVoiceNote::QxTdVoiceNote(QObject *parent)
    : QxTdObject(parent)
    , m_duration(0)
    , m_voice(new QxTdFile)
{
    setType(VOICE_NOTE);
}

qint32 QxTdVoiceNote::duration() const
{
    return m_duration;
}

QString QxTdVoiceNote::waveform() const
{
    return m_waveform;
}

QString QxTdVoiceNote::mimeType() const
{
    return m_mimeType;
}

QString QxTdVoiceNote::qmlDuration() const
{
    qint32 totalHours = (qint32)m_duration / 3600;
    if (totalHours > 0) {
        return QTime(0, 0, 0, 0).addSecs(m_duration).toString("hh:mm:ss");
    } else {
        return QTime(0, 0, 0, 0).addSecs(m_duration).toString("mm:ss");
    }
}

QxTdFile *QxTdVoiceNote::voice() const
{
    return m_voice.data();
}

void QxTdVoiceNote::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_duration = qint32(json["duration"].toInt());
    m_waveform = json["waveform"].toString();
    m_mimeType = json["mime_type"].toString();
    m_voice->unmarshalJson(json["voice"].toObject());
    emit voiceNoteChanged();
}
