#ifndef QX_TD_CHAT_ACTION_H
#define QX_TD_CHAT_ACTION_H

#include <QObject>
#include "common/qx_td_object.h"

class QxTdChatAction : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString personal_description READ personal_description)
    Q_PROPERTY(QString singular_description READ singular_description)
    Q_PROPERTY(QString plural_description READ plural_description)
    QML_ELEMENT
    Q_DISABLE_COPY(QxTdChatAction)
public:
    explicit QxTdChatAction(QObject *parent = nullptr);

    QString personal_description();
    QString singular_description();
    QString plural_description();

protected:
    QString m_personal_description;
    QString m_singular_description;
    QString m_plural_description;
};

class QxTdChatActionCancel : public QxTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionCancel)
public:
    explicit QxTdChatActionCancel(QObject *parent = nullptr);
};

class QxTdChatActionChoosingContact : public QxTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionChoosingContact)
public:
    explicit QxTdChatActionChoosingContact(QObject *parent = nullptr);
};

class QxTdChatActionChoosingLocation : public QxTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionChoosingLocation)
public:
    explicit QxTdChatActionChoosingLocation(QObject *parent = nullptr);
};

class QxTdChatActionRecordingVideo : public QxTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionRecordingVideo)
public:
    explicit QxTdChatActionRecordingVideo(QObject *parent = nullptr);
};

class QxTdChatActionRecordingVideoNote : public QxTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionRecordingVideoNote)
public:
    explicit QxTdChatActionRecordingVideoNote(QObject *parent = nullptr);
};

class QxTdChatActionRecordingVoiceNote : public QxTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionRecordingVoiceNote)
public:
    explicit QxTdChatActionRecordingVoiceNote(QObject *parent = nullptr);
};

class QxTdChatActionStartPlayingGame : public QxTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionStartPlayingGame)
public:
    explicit QxTdChatActionStartPlayingGame(QObject *parent = nullptr);
};

class QxTdChatActionTyping : public QxTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionTyping)
public:
    explicit QxTdChatActionTyping(QObject *parent = nullptr);
};

class QxTdChatActionUploadingDocument : public QxTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionUploadingDocument)
public:
    explicit QxTdChatActionUploadingDocument(QObject *parent = nullptr);
};

class QxTdChatActionUploadingPhoto : public QxTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionUploadingPhoto)
public:
    explicit QxTdChatActionUploadingPhoto(QObject *parent = nullptr);
};

class QxTdChatActionUploadingVideo : public QxTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionUploadingVideo)
public:
    explicit QxTdChatActionUploadingVideo(QObject *parent = nullptr);
};

class QxTdChatActionUploadingVideoNote : public QxTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionUploadingVideoNote)
public:
    explicit QxTdChatActionUploadingVideoNote(QObject *parent = nullptr);
};

class QxTdChatActionUploadingVoiceNote : public QxTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionUploadingVoiceNote)
public:
    explicit QxTdChatActionUploadingVoiceNote(QObject *parent = nullptr);
};

class QxTdChatActionChoosingSticker : public QxTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionChoosingSticker)
public:
    explicit QxTdChatActionChoosingSticker(QObject *parent = nullptr);
};

class QxTdChatActionRecordingAudio : public QxTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionRecordingAudio)
public:
    explicit QxTdChatActionRecordingAudio(QObject *parent = nullptr);
};

class QxTdChatActionUploadingAudio : public QxTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionUploadingAudio)
public:
    explicit QxTdChatActionUploadingAudio(QObject *parent = nullptr);
};

class QxTdChatActionUnknown : public QxTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionUnknown)
public:
    explicit QxTdChatActionUnknown(QObject *parent = nullptr);
};

#endif // QX_TD_CHAT_ACTION_H
