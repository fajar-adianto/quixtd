#include "qx_td_thumbnail.h"

QxTdThumbnail::QxTdThumbnail(QObject *parent)
    : QxTdObject(parent)
    , m_format(nullptr)
    , m_file(new QxTdFile)
    , m_width(0)
    , m_height(0)
{
    setType(PHOTO_SIZE);
}

QxTdThumbnailFormat *QxTdThumbnail::format() const
{
    return m_format.data();
}

QxTdFile *QxTdThumbnail::file() const
{
    return m_file.data();
}

qint32 QxTdThumbnail::width() const
{
    return m_width;
}

qint32 QxTdThumbnail::height() const
{
    return m_height;
}

void QxTdThumbnail::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    const QJsonObject format = json["format"].toObject();
    m_format.reset(QxTdThumbnailFormat::create(format, this));
    m_file->unmarshalJson(json["file"].toObject());
    if (m_file->local()->path().isEmpty()) {
        m_file->downloadFile();
    }
    m_width = qint32(json["width"].toInt());
    m_height = qint32(json["height"].toInt());
    emit thumbnailChanged();
}
