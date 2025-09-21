#ifndef QX_TD_INPUT_MESSAGE_CONTENT_ATTACHMENT_CAPTION_H
#define QX_TD_INPUT_MESSAGE_CONTENT_ATTACHMENT_CAPTION_H

#include "qx_td_input_message_content.h"
#include "content/imessageattachmentcontent.h"
#include "content/imessagecaptioncontent.h"

class QxTdInputMessageContentAttachmentCaption : public QxTdInputMessageContent, public IMessageCaptionContent, public IMessageAttachmentContent
{
    Q_OBJECT
    Q_INTERFACES(IMessageCaptionContent IMessageAttachmentContent)
public:
    explicit QxTdInputMessageContentAttachmentCaption(QObject *parent = nullptr);
    virtual QJsonObject marshalJson() = 0;
    virtual void setAttachmentPath(const QString &url) = 0;
    virtual void setCaption(const QString &text) = 0;
    virtual void setCaptionEntities(const QJsonArray &entities) = 0;
};
#endif // QX_TD_INPUT_MESSAGE_CONTENT_ATTACHMENT_CAPTION_H
