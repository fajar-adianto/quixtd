#include "qx_td_message_chat_delete_photo.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageChatDeletePhoto::QxTdMessageChatDeletePhoto(QObject *parent)
    : QxTdMessageContent(parent)
{
    setType(MESSAGE_CHAT_DELETE_PHOTO);
    m_typeText = qxTranslate("deleted the chat photo");
}
