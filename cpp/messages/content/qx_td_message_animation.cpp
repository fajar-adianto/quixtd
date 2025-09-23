#include "qx_td_message_animation.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageAnimation::QxTdMessageAnimation(QObject *parent)
    : QxTdMessageContent(parent)
    , m_animation(new QxTdAnimation)
    , m_caption(new QxTdFormattedText)
{
    setType(MESSAGE_ANIMATION);
}

QxTdAnimation *QxTdMessageAnimation::animation() const
{
    return m_animation.get();
}
QxTdFormattedText *QxTdMessageAnimation::caption() const
{
    return m_caption.get();
}
void QxTdMessageAnimation::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageContent::unmarshalJson(json);
    m_animation->unmarshalJson(json["animation"].toObject());
    m_caption->unmarshalJson(json["caption"].toObject());
    m_isSecret = json["is_secret"].toBool();
    m_infoText = m_caption->text() != "" ? m_caption->oneLineText() : "";
    m_typeText = m_caption->text() != "" ? qxTranslate("GIF,") : qxTranslate("GIF");
    m_infoImageUrl = QUrl("file://" + m_animation->thumbnail()->file()->local()->path());
}
