#include "qx_td_message_chat_change_photo.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageChatChangePhoto::QxTdMessageChatChangePhoto(QObject *parent)
    : QxTdMessageContent(parent)
    , m_photo(new QxTdPhotos)
{
    setType(MESSAGE_CHAT_CHANGE_PHOTO);
}

QxTdPhotos *QxTdMessageChatChangePhoto::photo() const
{
    return m_photo.get();
}

void QxTdMessageChatChangePhoto::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageContent::unmarshalJson(json);
    if (json.contains("photo")) {
        m_photo->unmarshalJson(json["photo"].toObject());
        m_typeText = qxTranslate("changed the chat photo");
        emit contentChanged();
    }
}
