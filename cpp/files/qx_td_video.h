#ifndef QX_TD_VIDEO_H
#define QX_TD_VIDEO_H

#include "qx_td_thumbnail.h"
#include "qx_td_file.h"

class QxTdVideo : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 duration READ duration NOTIFY videoChanged)
    Q_PROPERTY(qint32 width READ width NOTIFY videoChanged)
    Q_PROPERTY(qint32 height READ height NOTIFY videoChanged)
    Q_PROPERTY(QString fileName READ fileName NOTIFY videoChanged)
    Q_PROPERTY(QString mimeType READ mimeType NOTIFY videoChanged)
    Q_PROPERTY(QxTdThumbnail *thumbnail READ thumbnail NOTIFY videoChanged)
    Q_PROPERTY(QxTdFile *video READ video NOTIFY videoChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdVideo cannot be created in QML.")
public:
    explicit QxTdVideo(QObject *parent = nullptr);

    qint32 duration() const;

    qint32 width() const;

    qint32 height() const;

    QString fileName() const;

    QString mimeType() const;

    QxTdThumbnail *thumbnail() const;

    QxTdFile *video() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void videoChanged();

private:
    qint32 m_duration;
    qint32 m_width;
    qint32 m_height;
    QString m_fileName;
    QString m_mimeType;
    QScopedPointer<QxTdThumbnail> m_thumbnail;
    QScopedPointer<QxTdFile> m_video;
};

#endif // QX_TD_VIDEO_H
