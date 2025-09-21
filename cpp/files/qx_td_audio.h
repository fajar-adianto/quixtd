#ifndef QX_TD_AUDIO_H
#define QX_TD_AUDIO_H

#include "qx_td_thumbnail.h"

class QxTdAudio : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 duration READ duration NOTIFY audioChanged)
    Q_PROPERTY(QString title READ title NOTIFY audioChanged)
    Q_PROPERTY(QString performer READ performer NOTIFY audioChanged)
    Q_PROPERTY(QString fileName READ fileName NOTIFY audioChanged)
    Q_PROPERTY(QString mimeType READ mimeType NOTIFY audioChanged)
    Q_PROPERTY(QxTdThumbnail *albumCoverThumbnail READ albumCoverThumbnail NOTIFY audioChanged)
    Q_PROPERTY(QxTdFile *audio READ audio NOTIFY audioChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdAudio cannot be created in QML.")
public:
    explicit QxTdAudio(QObject *parent = nullptr);

    qint32 duration() const;

    QString title() const;

    QString performer() const;

    QString fileName() const;

    QString mimeType() const;

    QxTdThumbnail *albumCoverThumbnail() const;

    QxTdFile *audio() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void audioChanged();

private:
    qint32 m_duration;
    QString m_title;
    QString m_performer;
    QString m_fileName;
    QString m_mimeType;
    QScopedPointer<QxTdThumbnail> m_albumCoverThumbnail;
    QScopedPointer<QxTdFile> m_audio;
};

#endif // QX_TD_AUDIO_H
