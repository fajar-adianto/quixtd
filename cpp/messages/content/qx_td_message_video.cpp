#include "qx_td_message_video.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageVideo::QxTdMessageVideo(QObject *parent)
    : QxTdMessageContent(parent)
    , m_video(new QxTdVideo)
    , m_caption(new QxTdFormattedText)
{
    setType(MESSAGE_VIDEO);
}

QxTdVideo *QxTdMessageVideo::video() const
{
    return m_video.data();
}
QxTdFormattedText *QxTdMessageVideo::caption() const
{
    return m_caption.data();
}
void QxTdMessageVideo::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageContent::unmarshalJson(json);
    m_video->unmarshalJson(json["video"].toObject());
    m_caption->unmarshalJson(json["caption"].toObject());
    m_isSecret = json["is_secret"].toBool();
    m_infoText = m_caption->text() != "" ? m_caption->text() : "";
    m_typeText = m_caption->text() != "" ? qxTranslate("Video,") : qxTranslate("Video");
    m_infoImageUrl = QUrl("image://photo/" + m_video->thumbnail()->file()->local()->path());
}
