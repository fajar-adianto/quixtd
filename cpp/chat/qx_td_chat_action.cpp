#include "qx_td_chat_action.h"
#include "utils/qx_td_translate_tools.h"

QxTdChatAction::QxTdChatAction(QObject *parent)
    : QxTdObject(parent)
{
    m_personal_description = QString(qxTranslate("Doing something..."));
    m_singular_description = QString(qxTranslate("is doing something..."));
    m_plural_description = QString(qxTranslate("are doing something..."));
}

QString QxTdChatAction::personal_description()
{
    return m_personal_description;
}

QString QxTdChatAction::singular_description()
{
    return m_singular_description;
}

QString QxTdChatAction::plural_description()
{
    return m_plural_description;
}

QxTdChatActionCancel::QxTdChatActionCancel(QObject *parent)
    : QxTdChatAction(parent)
{
    setType(CHAT_ACTION_CANCEL);
}

QxTdChatActionChoosingContact::QxTdChatActionChoosingContact(QObject *parent)
    : QxTdChatAction(parent)
{
    setType(CHAT_ACTION_CHOOSING_CONTACT);
    m_personal_description = QString(qxTranslate("Choosing a contact..."));
    m_singular_description = QString(qxTranslate("is choosing a contact..."));
    m_plural_description = QString(qxTranslate("are choosing a contact..."));
}

QxTdChatActionRecordingVideo::QxTdChatActionRecordingVideo(QObject *parent)
    : QxTdChatAction(parent)
{
    setType(CHAT_ACTION_RECORDING_VIDEO);
    m_personal_description = QString(qxTranslate("Recording a video..."));
    m_singular_description = QString(qxTranslate("is recording a video..."));
    m_plural_description = QString(qxTranslate("are recording a video..."));
}

QxTdChatActionChoosingLocation::QxTdChatActionChoosingLocation(QObject *parent)
    : QxTdChatAction(parent)
{
    setType(CHAT_ACTION_CHOOSING_LOCATION);
    m_personal_description = QString(qxTranslate("Choosing a location..."));
    m_singular_description = QString(qxTranslate("is choosing a location..."));
    m_plural_description = QString(qxTranslate("are choosing a location..."));
}

QxTdChatActionRecordingVideoNote::QxTdChatActionRecordingVideoNote(QObject *parent)
    : QxTdChatAction(parent)
{
    setType(CHAT_ACTION_RECORDING_VIDEO_NOTE);
    m_personal_description = QString(qxTranslate("Recording a video note..."));
    m_singular_description = QString(qxTranslate("is recording a video note..."));
    m_plural_description = QString(qxTranslate("are recording a video note..."));
}

QxTdChatActionRecordingVoiceNote::QxTdChatActionRecordingVoiceNote(QObject *parent)
    : QxTdChatAction(parent)
{
    setType(CHAT_ACTION_RECORDING_VOICE_NOTE);
    m_personal_description = QString(qxTranslate("Recording a voice note..."));
    m_singular_description = QString(qxTranslate("is recording a voice note..."));
    m_plural_description = QString(qxTranslate("are recording a voice note..."));
}

QxTdChatActionStartPlayingGame::QxTdChatActionStartPlayingGame(QObject *parent)
    : QxTdChatAction(parent)
{
    setType(CHAT_ACTION_START_PLAYING_GAME);
    m_personal_description = QString(qxTranslate("Starting a game..."));
    m_singular_description = QString(qxTranslate("is starting a game..."));
    m_plural_description = QString(qxTranslate("are starting a game..."));
}

QxTdChatActionTyping::QxTdChatActionTyping(QObject *parent)
    : QxTdChatAction(parent)
{
    setType(CHAT_ACTION_TYPING);
    m_personal_description = QString(qxTranslate("Typing..."));
    m_singular_description = QString(qxTranslate("is typing..."));
    m_plural_description = QString(qxTranslate("are typing..."));
}

QxTdChatActionUploadingDocument::QxTdChatActionUploadingDocument(QObject *parent)
    : QxTdChatAction(parent)
{
    setType(CHAT_ACTION_UPLOADING_DOCUMENT);
    m_personal_description = QString(qxTranslate("Uploading a document..."));
    m_singular_description = QString(qxTranslate("is uploading a document..."));
    m_plural_description = QString(qxTranslate("are uploading a document..."));
}

QxTdChatActionUploadingPhoto::QxTdChatActionUploadingPhoto(QObject *parent)
    : QxTdChatAction(parent)
{
    setType(CHAT_ACTION_UPLOADING_PHOTO);
    m_personal_description = QString(qxTranslate("Uploading a photo..."));
    m_singular_description = QString(qxTranslate("is uploading a photo..."));
    m_plural_description = QString(qxTranslate("are uploading a photo..."));
}

QxTdChatActionUploadingVideo::QxTdChatActionUploadingVideo(QObject *parent)
    : QxTdChatAction(parent)
{
    setType(CHAT_ACTION_UPLOADING_VIDEO);
    m_personal_description = QString(qxTranslate("Uploading a video..."));
    m_singular_description = QString(qxTranslate("is uploading a video..."));
    m_plural_description = QString(qxTranslate("are uploading a video..."));
}

QxTdChatActionUploadingVideoNote::QxTdChatActionUploadingVideoNote(QObject *parent)
    : QxTdChatAction(parent)
{
    setType(CHAT_ACTION_UPLOADING_VIDEO_NOTE);
    m_personal_description = QString(qxTranslate("Uploading a video note..."));
    m_singular_description = QString(qxTranslate("is uploading a video note..."));
    m_plural_description = QString(qxTranslate("are uploading a video note..."));
}

QxTdChatActionUploadingVoiceNote::QxTdChatActionUploadingVoiceNote(QObject *parent)
    : QxTdChatAction(parent)
{
    setType(CHAT_ACTION_UPLOADING_VOICE_NOTE);
    m_personal_description = QString(qxTranslate("Uploading a voice note..."));
    m_singular_description = QString(qxTranslate("is uploading a voice note..."));
    m_plural_description = QString(qxTranslate("are uploading a voice note..."));
}

QxTdChatActionChoosingSticker::QxTdChatActionChoosingSticker(QObject *parent)
    : QxTdChatAction(parent)
{
    setType(CHAT_ACTION_CHOOSING_STICKER);
    m_personal_description = QString(qxTranslate("Choosing a sticker..."));
    m_singular_description = QString(qxTranslate("is choosing a sticker..."));
    m_plural_description = QString(qxTranslate("are choosing a sticker..."));
}

QxTdChatActionRecordingAudio::QxTdChatActionRecordingAudio(QObject *parent)
    : QxTdChatAction(parent)
{
    setType(CHAT_ACTION_RECORDING_AUDIO);
    m_personal_description = QString(qxTranslate("Recording audio..."));
    m_singular_description = QString(qxTranslate("is recording audio..."));
    m_plural_description = QString(qxTranslate("are recording audio..."));
}

QxTdChatActionUploadingAudio::QxTdChatActionUploadingAudio(QObject *parent)
    : QxTdChatAction(parent)
{
    setType(CHAT_ACTION_UPLOADING_AUDIO);
    m_personal_description = QString(qxTranslate("Uploading audio..."));
    m_singular_description = QString(qxTranslate("is uploading audio..."));
    m_plural_description = QString(qxTranslate("are uploading audio..."));
}

QxTdChatActionUnknown::QxTdChatActionUnknown(QObject *parent)
    : QxTdChatAction(parent)
{
    setType(CHAT_ACTION_UNKNOWN);
}
