#ifndef QX_TD_INPUT_MESSAGE_VOICE_NOTE_H
#define QX_TD_INPUT_MESSAGE_VOICE_NOTE_H

#include "imessageattachmentcontent.h"
#include "imessagecaptioncontent.h"
#include "../qx_td_input_message_content.h"

class QxTdInputMessageVoiceNote : public QxTdInputMessageContent, public IMessageCaptionContent, public IMessageAttachmentContent
{
    Q_OBJECT
    Q_INTERFACES(IMessageCaptionContent IMessageAttachmentContent)

public:
    explicit QxTdInputMessageVoiceNote(QObject *parent = nullptr);
    QJsonObject marshalJson();
    void setAttachmentPath(const QString &url);
    void setDuration(const qint32 &duration);
    void setWaveform(const QString &waveform);
    void setCaption(const QString &text);
    void setCaptionEntities(const QJsonArray &entities);

private:
    Q_DISABLE_COPY(QxTdInputMessageVoiceNote)
    QString m_voiceNote;
    qint32 m_duration;
    QString m_waveform;
    QString m_caption;
    QJsonArray m_captionEntities;
};

#endif // QX_TD_INPUT_MESSAGE_VOICE_NOTE_H
