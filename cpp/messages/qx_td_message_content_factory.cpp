#include "qx_td_message_content_factory.h"
#include <QDebug> // TEMP
#include "qx_td_message_content.h"
#include "content/qx_td_message_animation.h"
#include "content/qx_td_message_audio.h"
#include "content/qx_td_message_basic_group_chat_create.h"
#include "content/qx_td_message_call.h"
#include "content/qx_td_message_chat_add_members.h"
#include "content/qx_td_message_chat_change_photo.h"
#include "content/qx_td_message_chat_change_title.h"
#include "content/qx_td_message_chat_delete_member.h"
#include "content/qx_td_message_chat_delete_photo.h"
#include "content/qx_td_message_chat_join_by_link.h"
#include "content/qx_td_message_chat_set_message_auto_delete_time.h"
#include "content/qx_td_message_pin_message.h"
#include "content/qx_td_message_chat_upgrade_from.h"
#include "content/qx_td_message_chat_upgrade_to.h"
#include "content/qx_td_message_screenshot_taken.h"
#include "content/qx_td_message_document.h"
#include "content/qx_td_message_location.h"
#include "content/qx_td_message_photo.h"
#include "content/qx_td_message_sticker.h"
#include "content/qx_td_message_super_group_chat_create.h"
#include "content/qx_td_message_text.h"
#include "content/qx_td_message_video.h"
#include "content/qx_td_message_video_note.h"
#include "content/qx_td_message_voice_note.h"
#include "content/qx_td_message_custom_service_action.h"
#include "content/qx_td_message_contact_registered.h"
#include "content/qx_td_message_contact.h"
#include "content/qx_td_message_poll.h"
#include "content/qx_td_message_unsupported.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageContent *QxTdMessageContentFactory::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    // TODO: create a map of QMap<@type, QxTdObject::Type> so we can do fast lookups and
    // switch on the type. Otherwise this is/elseif is going to get huge supporting all content
    // types
    if (type == "messageText") {
        return new QxTdMessageText(parent);
    } else if (type == "messageSticker" || type == "messageAnimatedEmoji") {
        return new QxTdMessageSticker(parent);
    } else if (type == "messagePhoto") {
        return new QxTdMessagePhoto(parent);
    } else if (type == "messageAnimation") {
        return new QxTdMessageAnimation(parent);
    } else if (type == "messageAudio") {
        return new QxTdMessageAudio(parent);
    } else if (type == "messageDocument") {
        return new QxTdMessageDocument(parent);
    } else if (type == "messageLocation") {
        return new QxTdMessageLocation(parent);
    } else if (type == "messageVideo") {
        return new QxTdMessageVideo(parent);
    } else if (type == "messageVideoNote") {
        return new QxTdMessageVideoNote(parent);
    } else if (type == "messageVoiceNote") {
        return new QxTdMessageVoiceNote(parent);
    } else if (type == "messageChatJoinByLink") {
        return new QxTdMessageChatJoinByLink(parent);
    } else if (type == "messageBasicGroupChatCreate") {
        return new QxTdMessageBasicGroupChatCreate(parent);
    } else if (type == "messageCall") {
        return new QxTdMessageCall(parent);
    } else if (type == "messageScreenshotTaken") {
        return new QxTdMessageScreenshotTaken(parent);
    } else if (type == "messageChatAddMembers") {
        return new QxTdMessageChatAddMembers(parent);
    } else if (type == "messageChatChangePhoto") {
        return new QxTdMessageChatChangePhoto(parent);
    } else if (type == "messageChatChangeTitle") {
        return new QxTdMessageChatChangeTitle(parent);
    } else if (type == "messageChatDeleteMember") {
        return new QxTdMessageChatDeleteMember(parent);
    } else if (type == "messageChatDeletePhoto") {
        return new QxTdMessageChatDeletePhoto(parent);
    } else if (type == "messageChatSetMessageAutoDeleteTime") {
        return new QxTdMessageChatSetMessageAutoDeleteTime(parent);
    } else if (type == "messageChatUpgradeFrom") {
        return new QxTdMessageChatUpgradeFrom(parent);
    } else if (type == "messageChatUpgradeTo") {
        return new QxTdMessageChatUpgradeTo(parent);
    } else if (type == "messageCustomServiceAction") {
        return new QxTdMessageCustomServiceAction(parent);
    } else if (type == "messageContactRegistered") {
        return new QxTdMessageContactRegistered(parent);
    } else if (type == "messageUnsupported") {
        return new QxTdMessageUnsupported(parent);
    } else if (type == "messageSupergroupChatCreate") {
        return new QxTdMessageSuperGroupChatCreate(parent);
    } else if (type == "messagePinMessage") {
        return new QxTdMessagePinMessage(parent);
    } else if (type == "messagePoll") {
        return new QxTdMessagePoll(parent);
    } else if (type == "messageContact") {
        return new QxTdMessageContact(parent);
/*
      else if (type == "messageWebsiteConnected") {
        return new QxTdMessageWebsiteConnected(parent);
    } else if (type == "messageVenue") {
        return new QxTdMessageVenue(parent);
    } else if (type == "messagePassportDataReceived") {
        return new QxTdMessagePassportDataReceived(parent);
    } else if (type == "messagePassportDataSent") {
        return new QxTdMessagePassportDataSent(parent);
    } else if (type == "messagePaymentSuccessful") {
        return new QxTdMessagePaymentSuccesssful(parent);
    } else if (type == "messagePaymentSuccessfulBot") {
        return new QxTdMessagePaymentSuccessfulBot"(parent);
    } else if (type == "messageLinkInfo") {
        return new QxTdMessageLinkInfo(parent);
    } else if (type == "messageInvoice") {
        return new QxTdMessageInvoice(parent);
    } else if (type == "messageGame") {
        return new QxTdMessageGame(parent);
    } else if (type == "messageGameScore") {
        return new QxTdMessageGameScore(parent);
    } else if (type == "message") {
        return new QxTdMessage(parent);
    } else if (type == "message") {
        return new QxTdMessage(parent);
    } else if (type == "message") {
        return new QxTdMessage(parent);
    } else if (type == "message") {
        return new QxTdMessage(parent);
    }

*/
    }

    qWarning() << "Received unknown message type" << type << json;
    std::unique_ptr<QxTdMessageContent> uknMSg(new QxTdMessageContent(parent));
    uknMSg->setTypeText(qxTranslate("Unimplemented:"));
    uknMSg->setInfoText(type);
    return uknMSg.release();
}
