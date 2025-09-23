#ifndef QX_TD_MESSAGE_AUDIO_H
#define QX_TD_MESSAGE_AUDIO_H

#include "messages/qx_td_message_content.h"
#include "files/qx_td_audio.h"
#include "qx_td_formatted_text.h"

class QxTdMessageAudio : public QxTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QxTdAudio *audio READ audio NOTIFY dataChanged)
    Q_PROPERTY(QxTdFormattedText *caption READ caption NOTIFY dataChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageAudio cannot be created in QML.")
public:
    explicit QxTdMessageAudio(QObject *parent = nullptr);

    QxTdAudio *audio() const;
    QxTdFormattedText *caption() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QxTdMessageAudio)
    std::unique_ptr<QxTdAudio> m_audio;
    std::unique_ptr<QxTdFormattedText> m_caption;
};

#endif // QX_TD_MESSAGE_AUDIO_H
