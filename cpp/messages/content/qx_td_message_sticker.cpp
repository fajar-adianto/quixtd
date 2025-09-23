#include "qx_td_message_sticker.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageSticker::QxTdMessageSticker(QObject *parent)
    : QxTdMessageContent(parent)
    , m_sticker(new QxTdSticker)
{
    setType(MESSAGE_STICKER);
}

QxTdSticker *QxTdMessageSticker::sticker() const
{
    return m_sticker.get();
}

bool QxTdMessageSticker::isPremium() const {
    return m_is_premium;
}

void QxTdMessageSticker::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageContent::unmarshalJson(json);
    if (m_typeString == "messageAnimatedEmoji") {
        auto tempAnimatedEmoji = json["animated_emoji"].toObject();
        if (!tempAnimatedEmoji.isEmpty() && tempAnimatedEmoji["@type"] == "animatedEmoji") {
            m_sticker->unmarshalJson(tempAnimatedEmoji["sticker"].toObject());
        }
    } else {
        m_sticker->unmarshalJson(json["sticker"].toObject());
    }
    m_is_premium = json["is_premium"].toBool(); 
    m_infoImageUrl = QUrl("image://photo/" + m_sticker->thumbnail()->file()->local()->path());
    m_typeText = m_sticker->emoji() + " " + qxTranslate("Sticker");
}
