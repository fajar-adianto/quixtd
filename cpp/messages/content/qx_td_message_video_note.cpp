#include "qx_td_message_video_note.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageVideoNote::QxTdMessageVideoNote(QObject *parent)
    : QxTdMessageContent(parent)
    , m_videoNote(new QxTdVideoNote)
    , m_isViewed(new bool)
{
    setType(MESSAGE_VIDEO_NOTE);
}

QxTdVideoNote *QxTdMessageVideoNote::videoNote() const
{
    return m_videoNote.get();
}
bool QxTdMessageVideoNote::isViewed() const
{
    return m_isViewed;
}

void QxTdMessageVideoNote::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageContent::unmarshalJson(json);
    m_videoNote->unmarshalJson(json["video_note"].toObject());
    m_isViewed = json["is_viewed"].toBool();
    m_isSecret = json["is_secret"].toBool();
    m_typeText = qxTranslate("Video message");
    m_infoImageUrl = QUrl("image://photo/" + m_videoNote->thumbnail()->file()->local()->path());
}
