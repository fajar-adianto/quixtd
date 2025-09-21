#include "qx_td_chat_action_factory.h"
#include "qx_td_chat_action.h"
#include <QDebug>

QxTdChatAction *QxTdChatActionFactory::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    if (type == "chatActionCancel") {
        return new QxTdChatActionCancel(parent);
    } else if (type == "chatActionChoosingContact") {
        return new QxTdChatActionChoosingContact(parent);
    } else if (type == "chatActionChoosingLocation") {
        return new QxTdChatActionChoosingLocation(parent);
    } else if (type == "chatActionRecordingAudio") {
        return new QxTdChatActionRecordingAudio(parent);
    } else if (type == "chatActionRecordingVideo") {
        return new QxTdChatActionRecordingVideo(parent);
    } else if (type == "chatActionRecordingVideoNote") {
        return new QxTdChatActionRecordingVideoNote(parent);
    } else if (type == "chatActionRecordingVoiceNote") {
        return new QxTdChatActionRecordingVoiceNote(parent);
    } else if (type == "chatActionStartPlayingGame") {
        return new QxTdChatActionStartPlayingGame(parent);
    } else if (type == "chatActionTyping") {
        return new QxTdChatActionTyping(parent);
    } else if (type == "chatActionUploadingAudio") {
        return new QxTdChatActionUploadingAudio(parent);
    } else if (type == "chatActionUploadingDocument") {
        return new QxTdChatActionUploadingDocument(parent);
    } else if (type == "chatActionUploadingPhoto") {
        return new QxTdChatActionUploadingPhoto(parent);
    } else if (type == "chatActionUploadingVideo") {
        return new QxTdChatActionUploadingVideo(parent);
    } else if (type == "chatActionUploadingVideoNote") {
        return new QxTdChatActionUploadingVideoNote(parent);
    } else if (type == "chatActionUploadingVoiceNote") {
        return new QxTdChatActionUploadingVoiceNote(parent);
    } else if (type == "chatActionChoosingSticker") {
        return new QxTdChatActionChoosingSticker(parent);
    }
    qWarning() << "Received unknown chat action" << type;
    return new QxTdChatActionUnknown(parent);
}
