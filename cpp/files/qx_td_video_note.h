#ifndef QX_TD_VIDEO_NOTE_H
#define QX_TD_VIDEO_NOTE_H

#include "qx_td_thumbnail.h"
#include "qx_td_file.h"

class QxTdVideoNote : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 duration READ duration NOTIFY videoChanged)
    Q_PROPERTY(qint32 length READ length NOTIFY videoChanged)
    Q_PROPERTY(QxTdThumbnail *thumbnail READ thumbnail NOTIFY videoChanged)
    Q_PROPERTY(QxTdFile *video READ video NOTIFY videoChanged)
    QML_ELEMENT
public:
    explicit QxTdVideoNote(QObject *parent = nullptr);

    qint32 duration() const;

    qint32 length() const;

    QxTdThumbnail *thumbnail() const;

    QxTdFile *video() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void videoChanged();

private:
    qint32 m_duration;
    qint32 m_length;
    std::unique_ptr<QxTdThumbnail> m_thumbnail;
    std::unique_ptr<QxTdFile> m_video;
};

#endif // QX_TD_VIDEO_NOTE_H
