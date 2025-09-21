#ifndef QX_TD_MESSAGE_CHAT_DELETE_PHOTO_H
#define QX_TD_MESSAGE_CHAT_DELETE_PHOTO_H

#include "messages/qx_td_message_content.h"

class QxTdMessageChatDeletePhoto : public QxTdMessageContent
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageChatDeletePhoto cannot be created in QML.")
    Q_DISABLE_COPY(QxTdMessageChatDeletePhoto)
public:
    explicit QxTdMessageChatDeletePhoto(QObject *parent = nullptr);
};

#endif // QX_TD_MESSAGE_CHAT_DELETE_PHOTO_H
