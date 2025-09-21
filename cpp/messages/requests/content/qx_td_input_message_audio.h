#ifndef QX_TD_INPUT_MESSAGE_AUDIO_H
#define QX_TD_INPUT_MESSAGE_AUDIO_H

#include "../qx_td_input_message_content_attachment_caption.h"

class QxTdInputMessageAudio : public QxTdInputMessageContentAttachmentCaption
{
    Q_OBJECT

public:
    explicit QxTdInputMessageAudio(QObject *parent = nullptr);
    QJsonObject marshalJson();
    void setAttachmentPath(const QString &url);
    void setCaption(const QString &text);
    void setCaptionEntities(const QJsonArray &entities);

private:
    Q_DISABLE_COPY(QxTdInputMessageAudio)
    QString m_audio;
    QString m_caption;
    QJsonArray m_captionEntities;
};

#endif // QX_TD_INPUT_MESSAGE_AUDIO_H
