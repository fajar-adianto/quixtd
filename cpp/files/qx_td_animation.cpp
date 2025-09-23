#include "qx_td_animation.h"

QxTdAnimation::QxTdAnimation(QObject *parent)
    : QxTdObject(parent)
    , m_duration(0)
    , m_width(0)
    , m_height(0)
    , m_thumbnail(new QxTdThumbnail)
    , m_minithumbnail(new QxTdMiniThumbnail)
    , m_animation(new QxTdFile)
{
    setType(ANIMATION);
}

qint32 QxTdAnimation::duration() const
{
    return m_duration;
}

qint32 QxTdAnimation::width() const
{
    return m_width;
}

qint32 QxTdAnimation::height() const
{
    return m_height;
}

QString QxTdAnimation::fileName() const
{
    return m_fileName;
}

QString QxTdAnimation::mimeType() const
{
    return m_mimeType;
}

QxTdThumbnail *QxTdAnimation::thumbnail() const
{
    return m_thumbnail.get();
}

QxTdMiniThumbnail *QxTdAnimation::miniThumbnail() const
{
    return m_minithumbnail.get();
}

QxTdFile *QxTdAnimation::animation() const
{
    return m_animation.get();
}

void QxTdAnimation::unmarshalJson(const QJsonObject &json)
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
    if (json.contains("minithumbnail")) {
        m_minithumbnail->unmarshalJson(json["minithumbnail"].toObject());
    }
    m_animation->unmarshalJson(json["animation"].toObject());
    emit animationChanged();
}
