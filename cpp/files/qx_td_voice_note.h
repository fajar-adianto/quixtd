#ifndef QX_TD_VOICE_NOTE_H
#define QX_TD_VOICE_NOTE_H

#include "qx_td_photo_size.h"

class QxTdVoiceNote : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 duration READ duration NOTIFY voiceNoteChanged)
    Q_PROPERTY(QString waveform READ waveform NOTIFY voiceNoteChanged)
    Q_PROPERTY(QString mimeType READ mimeType NOTIFY voiceNoteChanged)
    Q_PROPERTY(QxTdFile *voice READ voice NOTIFY voiceNoteChanged)
    Q_PROPERTY(QString qmlDuration READ qmlDuration NOTIFY voiceNoteChanged)
    QML_ELEMENT
public:
    explicit QxTdVoiceNote(QObject *parent = nullptr);

    qint32 duration() const;

    QString waveform() const;

    QString mimeType() const;

    QxTdFile *voice() const;

    QString qmlDuration() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void voiceNoteChanged();

private:
    qint32 m_duration;
    QString m_waveform;
    QString m_mimeType;
    QScopedPointer<QxTdFile> m_voice;
};

#endif // QX_TD_VOICE_NOTE_H
