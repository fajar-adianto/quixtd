// #include <QtQml>
// #include <QtQml/QQmlContext>

// #include "plugin.h"
// #include "auth/qx_td_auth_manager.h"
// #include "connections/qx_td_connection_manager.h"
// #include "qx_users.h"
// #include "qx_contacts.h"

// #include "auth/qx_td_auth_code.h"
// #include "auth/qx_td_auth_state.h"
// #include "call/qx_td_call_discard_reason.h"
// #include "chat/qx_td_chat.h"
// #include "chat/requests/qx_td_chat_report_reason.h"
// #include "chat/qx_td_chat_list_model.h"
// #include "chat/qx_td_chat_list_sort_filter_model.h"
// #include "connections/qx_td_connection_state.h"
// #include "user/qx_td_user.h"
// #include "files/qx_td_file.h"
// #include "files/qx_td_animation.h"
// #include "files/qx_td_photo_size.h"
// #include "files/qx_td_audio.h"
// #include "files/qx_td_video.h"
// #include "files/qx_td_document.h"
// #include "files/qx_td_sticker.h"
// #include "files/qx_td_thumbnail.h"
// #include "files/qx_td_mini_thumbnail.h"
// #include "messages/qx_td_message.h"
// #include "messages/qx_td_message_list_model.h"
// #include "messages/qx_td_message_content.h"
// #include "messages/qx_td_chat_state.h"
// #include "messages/content/qx_td_message_animation.h"
// #include "messages/content/qx_td_message_audio.h"
// #include "messages/content/qx_td_message_basic_group_chat_create.h"
// #include "messages/content/qx_td_message_call.h"
// #include "messages/content/qx_td_message_chat_add_members.h"
// #include "messages/content/qx_td_message_chat_change_photo.h"
// #include "messages/content/qx_td_message_chat_change_title.h"
// #include "messages/content/qx_td_message_chat_delete_member.h"
// #include "messages/content/qx_td_message_chat_delete_photo.h"
// #include "messages/content/qx_td_message_chat_join_by_link.h"
// #include "messages/content/qx_td_message_chat_set_message_auto_delete_time.h"
// #include "messages/content/qx_td_message_chat_upgrade_from.h"
// #include "messages/content/qx_td_message_chat_upgrade_to.h"
// #include "messages/content/qx_td_message_document.h"
// #include "messages/content/qx_td_message_location.h"
// #include "messages/content/qx_td_message_photo.h"
// #include "messages/content/qx_td_message_poll.h"
// #include "messages/content/qx_td_message_sticker.h"
// #include "messages/content/qx_td_message_screenshot_taken.h"
// #include "messages/content/qx_td_message_text.h"
// #include "messages/content/qx_td_message_video.h"
// #include "messages/content/qx_td_message_video_note.h"
// #include "messages/content/qx_td_message_voice_note.h"
// #include "messages/content/qx_td_message_contact.h"
// #include "messages/content/qx_td_message_unsupported.h"
// #include "notifications/qx_td_enable_notifications.h"
// #include "settings/qx_td_settings.h"
// #include "stickers/qx_td_sticker_sets.h"

// #include "utils/qx_td_text_formatter.h"

// void QxTdLib::registerQmlTypes()
// {
//     static bool registered = false;
//     if (registered) {
//         return;
//     }
//     registered = true;

//     static const char *uri = "QTelegram";
//     //@uri QTelegram
// /**/qmlRegisterType<QxTdSettings>(uri, 1, 0, "Settings");
// /**/qmlRegisterType<QxTdAuthManager>(uri, 1, 0, "AuthState");
//     // ConnectionManager singleton
// /**/qmlRegisterSingletonType<QxTdConnectionManager>(uri, 1, 0, "ConnectionManager", [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
//         Q_UNUSED(engine)
//         Q_UNUSED(scriptEngine)
//         QxTdConnectionManager *connectionManager = new QxTdConnectionManager();
//         return connectionManager;
//     });
// /**/qmlRegisterType<QxTdAuthParams>(uri, 1, 0, "AuthParams");
// /**/qmlRegisterType<QxUsers>(uri, 1, 0, "Users");
// /**/qmlRegisterType<QxContacts>(uri, 1, 0, "Contacts");
// /**/qmlRegisterType<QxTdChatListModel>(uri, 1, 0, "ChatList");
// /**/qmlRegisterType<QxTdChatListSortFilterModel>(uri, 1, 0, "SortedChatList");
// /**/qmlRegisterType<QxTdMessageListModel>(uri, 1, 0, "MessageList");

// /**/qmlRegisterUncreatableType<QxTdChatState>(uri, 1, 0, "ChatState", "Enum type is uncreatable");

// /**/qmlRegisterType<QxTdTextFormatter>(uri, 1, 0, "TextFormatter");
// /**/qmlRegisterType<QxTdEnableNotifications>(uri, 1, 0, "EnableNotifications");

// /**/qmlRegisterType<QxTdStickerSets>(uri, 1, 0, "StickerSets");

//     // QxTdlib call
// /**/qmlRegisterUncreatableType<QxTdCallDiscardReason>(uri, 1, 0, "QxTdCallDiscardReason", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdCallDiscardReasonDeclined>(uri, 1, 0, "QxTdCallDiscardReasonDeclined", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdCallDiscardReasonDisconnected>(uri, 1, 0, "QxTdCallDiscardReasonDisconnected", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdCallDiscardReasonEmpty>(uri, 1, 0, "QxTdCallDiscardReasonEmpty", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdCallDiscardReasonHungUp>(uri, 1, 0, "QxTdCallDiscardReasonHungUp", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdCallDiscardReasonMissed>(uri, 1, 0, "QxTdCallDiscardReasonMissed", "c++ class");

//     // QxTdlib common
// /**/qmlRegisterUncreatableType<QxTdObject>(uri, 1, 0, "QxTdObject", "Base TD c++ class");
// /**/qmlRegisterType<QxTdMediaSizeExtractor>(uri, 1, 0, "QxTdMediaSizeExtractor");

//     // QxTdlib chat
// /**/qmlRegisterUncreatableType<QxTdChat>(uri, 1, 0, "QxTdChat", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdChatType>(uri, 1, 0, "QxTdChatType", "abstract c++ class");
// /**/qmlRegisterUncreatableType<QxTdChatTypeBasicGroup>(uri, 1, 0, "QxTdChatTypeBasicGroup", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdChatTypePrivate>(uri, 1, 0, "QxTdChatTypePrivate", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdChatTypeSecret>(uri, 1, 0, "QxTdChatTypeSecret", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdChatTypeSuperGroup>(uri, 1, 0, "QxTdChatTypeSuperGroup", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdChatPhoto>(uri, 1, 0, "QxTdChatPhoto", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdChatReportReason>(uri, 1, 0, "QxTdChatReportReason", "c++ class");
// /**/qRegisterMetaType<QxTdChatReportReason::ChatReportReasonType>("ChatReportReasonType");

//     // QxTdlib auth
// /**/qmlRegisterUncreatableType<QxTdAuthState>(uri, 1, 0, "QxTdAuthState", "Base TD auth state class");
// /**/qmlRegisterUncreatableType<QxTdAuthStateWaitParams>(uri, 1, 0, "QxTdAuthStateWaitParams", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdAuthStateWaitEncryptionKey>(uri, 1, 0, "QxTdAuthStateWaitEncryptionKey", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdAuthStateWaitPhoneNumber>(uri, 1, 0, "QxTdAuthStateWaitPhoneNumber", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdAuthStateWaitCode>(uri, 1, 0, "QxTdAuthStateWaitCode", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdAuthCodeInfo>(uri, 1, 0, "QxTdAuthCodeInfo", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdAuthStateWaitPassword>(uri, 1, 0, "QxTdAuthStateWaitPassword", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdAuthStateReady>(uri, 1, 0, "QxTdAuthStateReady", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdAuthStateLoggingOut>(uri, 1, 0, "QxTdAuthStateLoggingOut", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdAuthStateClosing>(uri, 1, 0, "QxTdAuthStateClosing", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdAuthStateClosed>(uri, 1, 0, "QxTdAuthStateClosed", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdAuthCodeTelegramMessage>(uri, 1, 0, "QxTdAuthCodeTelegramMessage", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdAuthCodeSms>(uri, 1, 0, "QxTdAuthCodeSms", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdAuthCodeCall>(uri, 1, 0, "QxTdAuthCodeCall", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdAuthCodeFlashCall>(uri, 1, 0, "QxTdAuthCodeFlashCall", "c++ class");


//     // QxTdlib connections
// /**/qmlRegisterUncreatableType<QxTdConnectionState>(uri, 1, 0, "QxTdConnectionState", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdConnectionStateWaitingForNetwork>(uri, 1, 0, "QxTdConnectionStateWaitingForNetwork", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdConnectionStateConnectingToProxy>(uri, 1, 0, "QxTdConnectionStateConnectingToProxy", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdConnectionStateConnecting>(uri, 1, 0, "QxTdConnectionStateConnecting", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdConnectionStateUpdating>(uri, 1, 0, "QxTdConnectionStateUpdating", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdConnectionStateReady>(uri, 1, 0, "QxTdConnectionStateReady", "c++ class");

//     // QxTdlib users
// /**/qmlRegisterUncreatableType<QxTdUser>(uri, 1, 0, "QxTdUser", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdUserStatus>(uri, 1, 0, "QxTdUserStatus", "Abstract status type");
// /**/qmlRegisterUncreatableType<QTxdUserStatusEmpty>(uri, 1, 0, "QxTdUserStatusEmpty", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdUserStateLastMonth>(uri, 1, 0, "QxTdUserStateLastMonth", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdUserStatusLastWeek>(uri, 1, 0, "QxTdUserStatusLastWeek", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdUserStatusOffline>(uri, 1, 0, "QxTdUserStatusOffline", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdUserStatusOnline>(uri, 1, 0, "QxTdUserStatusOnline", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdUserStatusRecently>(uri, 1, 0, "QxTdUserStatusRecently", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdProfilePhoto>(uri, 1, 0, "QxTdProfilePhoto", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdUserType>(uri, 1, 0, "QxTdUserType", "Abstract class");
// /**/qmlRegisterUncreatableType<QxTdUserTypeBot>(uri, 1, 0, "QxTdUserTypeBot", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdUserTypeDeleted>(uri, 1, 0, "QxTdUserTypeDeleted", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdUserTypeRegular>(uri, 1, 0, "QxTdUserTypeRegular", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdUserTypeUnknown>(uri, 1, 0, "QxTdUserTypeUnknown", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageSender>(uri, 1, 0, "QxTdMessageSender", "c++ class");
// /**/qRegisterMetaType<QxTdMessageSender::SenderType>("SenderType");

//     // QxTdlib files
// /**/qmlRegisterUncreatableType<QxTdFile>(uri, 1, 0, "QxTdFile", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdLocalFile>(uri, 1, 0, "QxTdLocalFile", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdRemoteFile>(uri, 1, 0, "QxTdRemoteFile", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdAnimation>(uri, 1, 0, "QxTdAnimation", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdPhoto>(uri, 1, 0, "QxTdPhoto", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdPhotoSize>(uri, 1, 0, "QxTdPhotoSize", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdThumbnail>(uri, 1, 0, "QxTdThumbnail", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdMiniThumbnail>(uri, 1, 0, "QxTdMiniThumbnail", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdAudio>(uri, 1, 0, "QxTdAudio", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdVideo>(uri, 1, 0, "QxTdVideo", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdDocument>(uri, 1, 0, "QxTdDocument", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdSticker>(uri, 1, 0, "QxTdSticker", "c++ class");

//     // QxTdlib notifications
// /**/qmlRegisterUncreatableType<QxTdNotificationSettings>(uri, 1, 0, "QxTdNotificationSettings", "C++ class");

//     // QxTdlib messages
// /**/qmlRegisterUncreatableType<QxTdMessage>(uri, 1, 0, "QxTdMessage", "C++ class");
//     // message content types
// /**/qmlRegisterUncreatableType<QxTdMessageContent>(uri, 1, 0, "QxTdMessageContent", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageAnimation>(uri, 1, 0, "QxTdMessageAnimation", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageAudio>(uri, 1, 0, "QxTdMessageAudio", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageBasicGroupChatCreate>(uri, 1, 0, "QxTdMessageBasicGroupChatCreate", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageCall>(uri, 1, 0, "QxTdMessageCall", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageChatAddMembers>(uri, 1, 0, "QxTdMessageChatAddMembers", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageChatChangePhoto>(uri, 1, 0, "QxTdMessageChatChangePhoto", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageChatChangeTitle>(uri, 1, 0, "QxTdMessageChatChangeTitle", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageChatDeleteMember>(uri, 1, 0, "QxTdMessageChatDeleteMember", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageChatDeletePhoto>(uri, 1, 0, "QxTdMessageChatDeletePhoto", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageChatJoinByLink>(uri, 1, 0, "QxTdMessageChatJoinByLink", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageChatSetMessageAutoDeleteTime>(uri, 1, 0, "QxTdMessageChatSetMessageAutoDeleteTime", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageChatUpgradeFrom>(uri, 1, 0, "QxTdMessageChatUpgradeFrom", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageChatUpgradeTo>(uri, 1, 0, "QxTdMessageChatUpgradeTo", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageDocument>(uri, 1, 0, "QxTdMessageDocument", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageLocation>(uri, 1, 0, "QxTdMessageLocation", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageHidden>(uri, 1, 0, "QxTdMessageHidden", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessagePhoto>(uri, 1, 0, "QxTdMessagePhoto", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessagePoll>(uri, 1, 0, "QxTdMessagePoll", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageSticker>(uri, 1, 0, "QxTdMessageSticker", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageText>(uri, 1, 0, "QxTdMessageText", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageScreenshotTaken>(uri, 1, 0, "QxTdMessageScreenshotTaken", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageUnsupported>(uri, 1, 0, "QxTdMessageUnsupported", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageVideo>(uri, 1, 0, "QxTdMessageVideo", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageVideoNote>(uri, 1, 0, "QxTdMessageVideoNote", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageVoiceNote>(uri, 1, 0, "QxTdMessageVoiceNote", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdFormattedText>(uri, 1, 0, "QxTdFormattedText", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdWebPage>(uri, 1, 0, "QxTdWebPage", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdContact>(uri, 1, 0, "QxTdContact", "c++ class");
// /**/qmlRegisterUncreatableType<QxTdMessageContact>(uri, 1, 0, "QxTdMessageContact", "C++ class");

//     // Settings
// /**/qmlRegisterUncreatableType<QxTdProxy>(uri, 1, 0, "QxTdProxy", "C++ class");
// /**/qmlRegisterUncreatableType<QxTdProxyType>(uri, 1, 0, "QxTdProxyType", "C++ class");

//     // stickers
// /**/qmlRegisterUncreatableType<QxTdStickerSet>(uri, 1, 0, "QxTdStickerSet", "C++ class");
// }
