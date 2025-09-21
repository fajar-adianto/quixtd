#ifndef QX_TD_THUMBNAIL_FORMAT_H
#define QX_TD_THUMBNAIL_FORMAT_H

#include "common/qx_td_object.h"

/**
 * @brief The QxTdThumbnailFormat class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_thumbnail_format.html
 */
class QxTdThumbnailFormat : public QxTdObject
{
    Q_OBJECT
public:
    explicit QxTdThumbnailFormat(QObject *parent = nullptr);

    static QxTdThumbnailFormat *create(const QJsonObject &json, QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(QxTdThumbnailFormat)
};

/**
 * @brief The QxTdThumbnailFormatGif class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1thumbnail_format_gif.html
 */
class QxTdThumbnailFormatGif : public QxTdThumbnailFormat
{
    Q_OBJECT
public:
    explicit QxTdThumbnailFormatGif(QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(QxTdThumbnailFormatGif)
};

/**
 * @brief The QxTdThumbnailFormatJpeg class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1thumbnail_format_jpeg.html
 */
class QxTdThumbnailFormatJpeg : public QxTdThumbnailFormat
{
    Q_OBJECT
public:
    explicit QxTdThumbnailFormatJpeg(QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(QxTdThumbnailFormatJpeg)
};

/**
 * @brief The QxTdThumbnailFormatMpeg4 class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1thumbnail_format_mpeg4.html
 */
class QxTdThumbnailFormatMpeg4 : public QxTdThumbnailFormat
{
    Q_OBJECT
public:
    explicit QxTdThumbnailFormatMpeg4(QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(QxTdThumbnailFormatMpeg4)
};

/**
 * @brief The QxTdThumbnailFormatPng class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1thumbnail_format_png.html
 */
class QxTdThumbnailFormatPng : public QxTdThumbnailFormat
{
    Q_OBJECT
public:
    explicit QxTdThumbnailFormatPng(QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(QxTdThumbnailFormatPng)
};

/**
 * @brief The QxTdThumbnailFormatTgs class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1thumbnail_format_tgs.html
 */
class QxTdThumbnailFormatTgs : public QxTdThumbnailFormat
{
    Q_OBJECT
public:
    explicit QxTdThumbnailFormatTgs(QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(QxTdThumbnailFormatTgs)
};

/**
 * @brief The QxTdThumbnailFormatWebp class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1thumbnail_format_webp.html
 */
class QxTdThumbnailFormatWebp : public QxTdThumbnailFormat
{
    Q_OBJECT
public:
    explicit QxTdThumbnailFormatWebp(QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(QxTdThumbnailFormatWebp)
};

#endif // QX_TD_THUMBNAIL_FORMAT_H
