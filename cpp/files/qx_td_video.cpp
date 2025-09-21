#include "qx_td_video.h"

QxTdVideo::QxTdVideo(QObject *parent)
    : QxTdObject(parent)
    , m_duration(0)
    , m_width(0)
    , m_height(0)
    , m_thumbnail(new QxTdThumbnail)
    , m_video(new QxTdFile)
{
    setType(VIDEO);
}

qint32 QxTdVideo::duration() const
{
    return m_duration;
}

qint32 QxTdVideo::width() const
{
    return m_width;
}

qint32 QxTdVideo::height() const
{
    return m_height;
}

QString QxTdVideo::fileName() const
{
    return m_fileName;
}

QString QxTdVideo::mimeType() const
{
    return m_mimeType;
}

QxTdThumbnail *QxTdVideo::thumbnail() const
{
    return m_thumbnail.data();
}

QxTdFile *QxTdVideo::video() const
{
    return m_video.data();
}

void QxTdVideo::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_duration = qint32(json["duration"].toInt());
    m_width = qint32(json["width"].toInt());
    m_height = qint32(json["height"].toInt());
    m_fileName = json["file_name"].toString();
    m_mimeType = json["mime_type"].toString();
    if (json.contains("thumbnail")) {
        m_thumbnail->unmarshalJson(json["thumbnail"].toObject());
    }
    m_video->unmarshalJson(json["video"].toObject());
    emit videoChanged();
}
