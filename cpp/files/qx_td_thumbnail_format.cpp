#include "qx_td_thumbnail_format.h"

QxTdThumbnailFormat::QxTdThumbnailFormat(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

QxTdThumbnailFormat *QxTdThumbnailFormat::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();

    if (type == "thumbnailFormatGif") {
        return new QxTdThumbnailFormatGif(parent);
    } else if (type == "thumbnailFormatJpeg") {
        return new QxTdThumbnailFormatJpeg(parent);
    } else if (type == "thumbnailFormatMpeg4") {
        return new QxTdThumbnailFormatMpeg4(parent);
    } else if (type == "thumbnailFormatPng") {
        return new QxTdThumbnailFormatPng(parent);
    } else if (type == "thumbnailFormatTgs") {
        return new QxTdThumbnailFormatTgs(parent);
    } else if (type == "thumbnailFormatWebp") {
        return new QxTdThumbnailFormatWebp(parent);
    }

    return nullptr;
}

QxTdThumbnailFormatGif::QxTdThumbnailFormatGif(QObject *parent)
    : QxTdThumbnailFormat(parent)
{
    setType(THUMBNAIL_FORMAT_GIF);
}

QxTdThumbnailFormatJpeg::QxTdThumbnailFormatJpeg(QObject *parent)
    : QxTdThumbnailFormat(parent)
{
    setType(THUMBNAIL_FORMAT_JPEG);
}

QxTdThumbnailFormatMpeg4::QxTdThumbnailFormatMpeg4(QObject *parent)
    : QxTdThumbnailFormat(parent)
{
    setType(THUMBNAIL_FORMAT_MPEG4);
}

QxTdThumbnailFormatPng::QxTdThumbnailFormatPng(QObject *parent)
    : QxTdThumbnailFormat(parent)
{
    setType(THUMBNAIL_FORMAT_PNG);
}

QxTdThumbnailFormatTgs::QxTdThumbnailFormatTgs(QObject *parent)
    : QxTdThumbnailFormat(parent)
{
    setType(THUMBNAIL_FORMAT_TGS);
}

QxTdThumbnailFormatWebp::QxTdThumbnailFormatWebp(QObject *parent)
    : QxTdThumbnailFormat(parent)
{
    setType(THUMBNAIL_FORMAT_WEBP);
}
