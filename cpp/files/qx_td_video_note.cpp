#include "qx_td_video_note.h"

QxTdVideoNote::QxTdVideoNote(QObject *parent)
    : QxTdObject(parent)
    , m_duration(0)
    , m_length(0)
    , m_thumbnail(new QxTdThumbnail)
    , m_video(new QxTdFile)
{
    setType(VIDEO_NOTE);
}

qint32 QxTdVideoNote::duration() const
{
    return m_duration;
}

qint32 QxTdVideoNote::length() const
{
    return m_duration;
}

QxTdThumbnail *QxTdVideoNote::thumbnail() const
{
    return m_thumbnail.data();
}

QxTdFile *QxTdVideoNote::video() const
{
    return m_video.data();
}

void QxTdVideoNote::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_duration = qint32(json["duration"].toInt());
    m_length = qint32(json["length"].toInt());
    if (json.contains("thumbnail")) {
        m_thumbnail->unmarshalJson(json["thumbnail"].toObject());
    }
    m_video->unmarshalJson(json["video"].toObject());
    emit videoChanged();
}
