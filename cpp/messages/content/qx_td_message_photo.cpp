#include "qx_td_message_photo.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessagePhoto::QxTdMessagePhoto(QObject *parent)
    : QxTdMessageContent(parent)
    , m_photo(new QxTdPhotos)
    , m_caption(new QxTdFormattedText)
{
    setType(MESSAGE_PHOTO);
}

QxTdPhotos *QxTdMessagePhoto::photo() const
{
    return m_photo.get();
}
QxTdFormattedText *QxTdMessagePhoto::caption() const
{
    return m_caption.get();
}
void QxTdMessagePhoto::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageContent::unmarshalJson(json);
    m_photo->unmarshalJson(json["photo"].toObject());
    m_caption->unmarshalJson(json["caption"].toObject());
    m_isSecret = json["is_secret"].toBool();
    m_infoImageUrl = QUrl("image://photo/" + m_photo->sizes()->at(0)->photo()->local()->path());
    m_infoText = m_caption->text() != "" ? m_caption->oneLineText() : "";
    m_typeText = m_caption->text() != "" ? qxTranslate("Photo,") : qxTranslate("Photo");
}
