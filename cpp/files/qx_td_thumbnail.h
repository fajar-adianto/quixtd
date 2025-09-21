#ifndef QX_TD_THUMBNAIL_H
#define QX_TD_THUMBNAIL_H

#include "qx_td_file.h"
#include "qx_td_thumbnail_format.h"

class QxTdThumbnail : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QxTdThumbnailFormat *format READ format NOTIFY thumbnailChanged)
    Q_PROPERTY(QxTdFile *file READ file NOTIFY thumbnailChanged)
    Q_PROPERTY(qint32 width READ width NOTIFY thumbnailChanged)
    Q_PROPERTY(qint32 height READ height NOTIFY thumbnailChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdThumbnail cannot be created in QML.")
public:
    explicit QxTdThumbnail(QObject *parent = nullptr);

    QxTdThumbnailFormat *format() const;

    QxTdFile *file() const;

    qint32 width() const;

    qint32 height() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void thumbnailChanged();

private:
    QScopedPointer<QxTdThumbnailFormat> m_format;
    QScopedPointer<QxTdFile> m_file;
    qint32 m_width;
    qint32 m_height;
};

#endif // QX_TD_THUMBNAIL_H
