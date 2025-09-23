#include "qx_td_audio.h"

QxTdAudio::QxTdAudio(QObject *parent)
    : QxTdObject(parent)
    , m_duration(0)
    , m_albumCoverThumbnail(new QxTdThumbnail)
    , m_audio(new QxTdFile)
{
    setType(AUDIO);
}

qint32 QxTdAudio::duration() const
{
    return m_duration;
}

QString QxTdAudio::title() const
{
    return m_title;
}

QString QxTdAudio::performer() const
{
    return m_performer;
}

QString QxTdAudio::fileName() const
{
    return m_fileName;
}

QString QxTdAudio::mimeType() const
{
    return m_mimeType;
}

QxTdThumbnail *QxTdAudio::albumCoverThumbnail() const
{
    return m_albumCoverThumbnail.get();
}

QxTdFile *QxTdAudio::audio() const
{
    return m_audio.get();
}

void QxTdAudio::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
        m_duration = qint32(json["duration"].toInt());
    m_title = json["title"].toString();
    m_performer = json["performer"].toString();
    m_fileName = json["file_name"].toString();
    m_mimeType = json["mime_type"].toString();
    if (json.contains("album_cover_thumbnail")) {
        m_albumCoverThumbnail->unmarshalJson(json["album_cover_thumbnail"].toObject());
    }
    m_audio->unmarshalJson(json["audio"].toObject());
    emit audioChanged();
}
