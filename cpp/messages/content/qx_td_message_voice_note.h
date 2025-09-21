#ifndef QX_TD_MESSAGE_VOICE_NOTE_H
#define QX_TD_MESSAGE_VOICE_NOTE_H

#include "messages/qx_td_message_content.h"
#include "files/qx_td_voice_note.h"
#include "qx_td_formatted_text.h"

class QxTdMessageVoiceNote : public QxTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QxTdVoiceNote *voiceNote READ voiceNote NOTIFY dataChanged)
    Q_PROPERTY(QxTdFormattedText *caption READ caption NOTIFY dataChanged)
    Q_PROPERTY(bool isListened READ isListened NOTIFY dataChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageVoiceNote cannot be created in QML.")
public:
    explicit QxTdMessageVoiceNote(QObject *parent = nullptr);

    QxTdVoiceNote *voiceNote() const;
    QxTdFormattedText *caption() const;
    bool isListened() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QxTdMessageVoiceNote)
    QScopedPointer<QxTdVoiceNote> m_voiceNote;
    QScopedPointer<QxTdFormattedText> m_caption;
    bool m_isListened;
};

#endif // QX_TD_MESSAGE_VOICE_NOTE_H
