#include "qx_td_input_message_content_factory.h"

#include "qx_td_input_message_content_attachment_caption.h"

#include "content/qx_td_input_message_audio.h"
#include "content/qx_td_input_message_contact.h"
#include "content/qx_td_input_message_document.h"
#include "content/qx_td_input_message_location.h"
#include "content/qx_td_input_message_photo.h"
#include "content/qx_td_input_message_sticker.h"
#include "content/qx_td_input_message_video.h"
#include <stdexcept>

QxTdInputMessageContentAttachmentCaption *QxTdInputMessageContentFactory::create(const InputMessageType type, QObject *parent)
{
    switch (type) {
    case Photo:
        return new QxTdInputMessagePhoto(parent);
    case Video:
        return new QxTdInputMessageVideo(parent);
    case Audio:
        return new QxTdInputMessageAudio(parent);
    case Document:
        return new QxTdInputMessageDocument(parent);
    default:
        throw std::invalid_argument( "invalid input message type" );
    }
}
