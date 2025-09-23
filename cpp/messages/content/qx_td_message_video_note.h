#ifndef QX_TD_MESSAGE_VIDEO_NOTE_H
#define QX_TD_MESSAGE_VIDEO_NOTE_H

#include "messages/qx_td_message_content.h"
#include "files/qx_td_video_note.h"

class QxTdMessageVideoNote : public QxTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QxTdVideoNote *videoNote READ videoNote NOTIFY dataChanged)
    Q_PROPERTY(bool isViewed READ isViewed NOTIFY dataChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdVideoNote cannot be created in QML.")
public:
    explicit QxTdMessageVideoNote(QObject *parent = nullptr);

    QxTdVideoNote *videoNote() const;
    bool isViewed() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QxTdMessageVideoNote)
    std::unique_ptr<QxTdVideoNote> m_videoNote;
    bool m_isViewed;
};

#endif // QX_TD_MESSAGE_VIDEO_NOTE_H
