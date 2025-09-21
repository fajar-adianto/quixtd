#ifndef QX_TD_MESSAGE_LIST_MODEL_H
#define QX_TD_MESSAGE_LIST_MODEL_H

#include "qx_td_message.h"
#include "chat/qx_td_chat.h"
#include "chat/requests/qx_td_chat_report_reason.h"
#include "files/qx_td_sticker.h"
#include "models/qx_td_object_list_model.h"
#include "requests/qx_td_input_message_content_factory.h"
#include "requests/qx_td_input_message_content.h"
#include "requests/content/imessageattachmentcontent.h"
#include "requests/content/imessagecaptioncontent.h"
#include "utils/qx_td_media_tools.h"

#define MESSAGE_LOAD_WINDOW 60

class QxTdMessageListModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QxTdChat *chat READ chat WRITE setChat NOTIFY chatChanged)
    Q_PROPERTY(QObject *model READ qmlModel NOTIFY modelChanged)
    QML_ELEMENT
public:
    explicit QxTdMessageListModel(QObject *parent = nullptr);

    QxTdChat *chat() const;
    QObject *qmlModel() const;

    class QxTdAbstractMessageHandler : public QObject
    {
    public:
        virtual ~QxTdAbstractMessageHandler() {}
        virtual void handle(QxTdMessageListModel &messageListModel, const QJsonArray &messages) const = 0;
        QxTdMessage *messageFromJson(const QJsonValue &msgData) const
        {
            const QJsonObject data = msgData.toObject();
            auto *message = new QxTdMessage;
            message->unmarshalJson(data);
            return message;
        }
    };

    class QxTdNewerMessagesHandler : public QxTdAbstractMessageHandler
    {
        void handle(QxTdMessageListModel &messageListModel, const QJsonArray &messages) const;
    };

    class QxTdOlderMessagesHandler : public QxTdAbstractMessageHandler
    {
        void handle(QxTdMessageListModel &messageListModel, const QJsonArray &messages) const;
    };

    class QxTdJumpToWindowMessageHandler : public QxTdAbstractMessageHandler
    {
        void handle(QxTdMessageListModel &messageListModel, const QJsonArray &messages) const;
    };

signals:
    void chatChanged(QxTdChat *chat);
    void modelChanged();
    void importFileFinished(QString fileName);
    void error(const QString &errorMessage);
    void messageLinkReceived(const QString messageLink);

public slots:
    void setChat(QxTdChat *chat);
    void loadNewer();
    void loadOlder();

    void setCaptionProperties(IMessageCaptionContent *contentObj, const QString &caption);
    void setAttachmentProperties(IMessageAttachmentContent *contentObj, const QString &attachmentUrl);
    void prepareAndSendAttachmentMessage(QxTdInputMessageContent *contentObj, const qint64 &replyToMessageId);
    void prepareAndSendAttachmentMessageAlbum(const QList<QxTdInputMessageContent*> &contents, const qint64 &replyToMessageId);
    void sendMessage(const QString &message, const bool clearDraft = false, const bool disableNotification = false, const qint32 sendDate = 0, const QString &replyToMessageId = "0");

    void sendPhoto(const QString &url, const QString &caption, const qint64 &replyToMessageId);
    void sendAudio(const QString &url, const QString &caption, const qint64 &replyToMessageId);
    void sendAudioAlbum(const QList<QString> &urls, const QString &caption, const qint64 &replyToMessageId);
    void sendVideo(const QString &url, const QString &caption, const qint64 &replyToMessageId);
    void sendPhotoAlbum(const QList<QString> &urls, const QString &caption, const qint64 &replyToMessageId);
    void sendVideoAlbum(const QList<QString> &urls, const QString &caption, const qint64 &replyToMessageId);
    void sendContact(const QString &firstName, const QString &lastName, const QString &phone, const qint64 &replyToMessageId);
    void sendDocument(const QString &url, const QString &caption, const qint64 &replyToMessageId);
    void sendDocumentAlbum(const QList<QString> &urls, const QString &caption, const qint64 &replyToMessageId);
    void sendLocation(const double latitude, const double longitude, const qint32 livePeriod, const qint64 &replyToMessageId);
    void sendSticker(QxTdSticker *sticker, const QString &replyToMessageId = "");
    void sendVoiceNote(const QString &filename, const qint64 &replyToMessageId);

    void editMessageText(qint64 messageId, const QString &message);
    void editMessageText(const QString &messageId, const QString &message);
    void editMessageCaption(qint64 messageId, const QString &message);
    void editMessageCaption(const QString &messageId, const QString &message);
    //void sendReplyToMessage(const qint64 &replyToMessageId, const QString &message, const bool disableNotification = false, const qint32 sendDate = 0);
    //void sendReplyToMessage(const QString &replyToMessageId, const QString &message, const bool disableNotification = false, const qint32 sendDate = 0);
    //sendMessage(message, true, replyToMessageId, disableNotification, sendDate);
    void deleteMessage(const qint64 messageId, const bool revoke);
    void deleteMessages(const QList<qint64> &messageIds, const bool revoke);
    void jumpToMessage(const qint64 messageId, const bool isToBeHighlighted);
    void registerVoiceNote(const QString &filename);
    void stopVoiceNote();
    void deleteVoiceNote(const QString &filename);
    void handleUpdateFileGenerationStart(const QJsonObject &json);
    void handleUpdateFileGenerationStop(const QJsonObject &json);
    void handleUpdateMessageInteractionInfo(const QJsonObject &json);

    void removeChatActionBar();
    void reportChat(const QString chatId, const QxTdChatReportReason::ChatReportReasonType &reason, const QString &text);
    void requestMessageLink(const QString chatId, const QString messageId);
    void toggleMessageSenderIsBlocked(const qint64 id, const bool isBlocked, const QxTdMessageSender::SenderType type);
    void searchChatMessages(const QString chatId, const QString query, const QString fromMessageId);

private slots:
    void cleanUp();
    void handleMessages(const QJsonObject &json);
    void handleUpdateChatLastMessage(const QJsonObject &json);
    void handleUpdateMessageSendStatus(const QJsonObject &json);
    void handleUpdateMessageContent(const QJsonObject &json);
    void handleUpdateDeleteMessages(const QJsonObject &json);
    void handleUpdateMessageEdited(const QJsonObject &json);
    void loadMessages(qint64 fromMsgId,
                      unsigned int amountBefore,
                      unsigned int amountAfter);
    void handleRequestMessageLinkCompleted(const QJsonObject &json);

private:
    Q_DISABLE_COPY(QxTdMessageListModel)
    QPointer<QxTdObjectListModel<QxTdMessage>> m_model;
    QPointer<QxTdChat> m_chat;
    QPointer<QxTdAbstractMessageHandler> m_messageHandler;
    QxTdNewerMessagesHandler newerMessagesHandler;
    QxTdOlderMessagesHandler olderMessagesHandler;
    QxTdJumpToWindowMessageHandler jumpToWindowMessageHandler;
    bool m_isHandleUpdateLastChatMessageConnected;
    qint64 m_jumpToMessageId;
    bool m_highlightJumpedMessage;
    QString m_fileGenerationId;
    QScopedPointer<QxTdMediaSizeExtractor> m_mediaSizeExtractor;

    QxTdMessage *getDateLabelIfNeeded(QxTdMessage *firstMessage, QxTdMessage *secondMessage);
    void setMessagesRead(QList<qint64> &messages);
    void appendMessage(QxTdMessage *message);
    void prependMessage(QxTdMessage *message);
    bool isUpToDateAndFollowing() const;
    bool hasNewer() const;
    void sendMedia(const QString &url, const QString &caption, const qint64 &replyToMessageId, InputMessageType inputMessageType);
    void sendAlbum(const QList<QString> &urls, const QString &caption, const qint64 &replyToMessageId, const InputMessageType type);
};

#endif // QX_TD_MESSAGE_LIST_MODEL_H
