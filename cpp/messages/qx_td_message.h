#ifndef QX_TD_MESSAGE_H
#define QX_TD_MESSAGE_H

#include <QDateTime>

#include "qx_td_message_content.h"
#include "qx_td_message_interaction_info.h"
#include "qx_td_message_sender.h"
#include "qx_td_message_sending_state.h"
#include "qx_td_message_scheduling_state.h"
#include "forwardinfo/qx_td_message_forward_info.h"
#include "replymarkup/qx_td_reply_markup.h"

class QxTdMessage : public QxAbstractInt64Id
{
    Q_OBJECT
    Q_PROPERTY(QxTdMessageSender *sender READ sender NOTIFY senderChanged)
    Q_PROPERTY(QString chatId READ qmlChatId NOTIFY messageChanged)
    Q_PROPERTY(QxTdMessageSendingState *sendingState READ sendingState NOTIFY sendingStateChanged)
    Q_PROPERTY(QxTdMessageSchedulingState *schedulingState READ schedulingState NOTIFY messageChanged)
    Q_PROPERTY(bool isOutgoing READ isOutgoing NOTIFY messageChanged)
    Q_PROPERTY(bool isPinned READ isPinned NOTIFY messageChanged)
    Q_PROPERTY(bool canBeEdited READ canBeEdited NOTIFY messageChanged)
    Q_PROPERTY(bool canBeForwarded READ canBeForwarded NOTIFY messageChanged)
    Q_PROPERTY(bool canBeSaved READ canBeSaved NOTIFY messageChanged)
    Q_PROPERTY(bool canBeDeletedOnlyForSelf READ canBeDeletedOnlyForSelf NOTIFY messageChanged)
    Q_PROPERTY(bool canBeDeletedForAllUsers READ canBeDeletedForAllUsers NOTIFY messageChanged)
    Q_PROPERTY(bool canGetStatistics READ canGetStatistics NOTIFY messageChanged)
    Q_PROPERTY(bool canGetMessageThread READ canGetMessageThread NOTIFY messageChanged)
    Q_PROPERTY(bool canGetViewers READ canGetViewers NOTIFY messageChanged)
    Q_PROPERTY(bool canGetMediaTimestampLinks READ canGetMediaTimestampLinks NOTIFY messageChanged)
    Q_PROPERTY(bool hasTimestampedMedia READ hasTimestampedMedia NOTIFY messageChanged)
    Q_PROPERTY(bool isChannelPost READ isChannelPost NOTIFY messageChanged)
    Q_PROPERTY(bool containsUnreadMention READ containsUnreadMention NOTIFY messageChanged)
    Q_PROPERTY(QDateTime date READ qmlDate NOTIFY messageChanged)
    Q_PROPERTY(QDateTime editDate READ qmlEditDate NOTIFY messageChanged)
    Q_PROPERTY(QxTdMessageForwardInfo *forwardInfo READ forwardInfo NOTIFY messageChanged)
    Q_PROPERTY(QxTdMessageInteractionInfo *interactionInfo READ interactionInfo NOTIFY messageChanged)
    Q_PROPERTY(QString replyToMessageId READ qmlReplyToMessageId NOTIFY messageChanged)
    Q_PROPERTY(QString messageThreadId READ qmlMessageThreadId NOTIFY messageChanged)
    Q_PROPERTY(qint32 ttl READ ttl NOTIFY messageChanged)

    Q_PROPERTY(bool isEdited READ isEdited WRITE setIsEdited NOTIFY messageChanged)
    Q_PROPERTY(QString views READ views NOTIFY messageChanged)
    Q_PROPERTY(QxTdMessageContent *content READ content NOTIFY messageChanged)
    Q_PROPERTY(QxTdReplyMarkup *replyMarkup READ replyMarkup NOTIFY messageChanged)
    // These aren't original properties of the tdlib message class but we can
    // can make life easier for use in QML.
    // Provide a summary text for display in the chatlist
    Q_PROPERTY(QString summary READ summary NOTIFY senderChanged)
    // Shows if the sender of the previous message is the same as this one.
    Q_PROPERTY(bool sameSenderAsPreviousMessage READ sameSenderAsPreviousMessage NOTIFY previousSenderChanged)
    // Shows if the sender of the next message is the same as this one.
    Q_PROPERTY(bool sameSenderAsNextMessage READ sameSenderAsNextMessage NOTIFY nextSenderChanged)
    // Indicates if this message is the first/latest message in the model
    Q_PROPERTY(bool isLatest READ isLatest NOTIFY nextSenderChanged)
    Q_PROPERTY(QxTdMessage *messageRepliedTo READ messageRepliedTo NOTIFY messageRepliedToChanged)
    Q_PROPERTY(bool isReply READ isReply NOTIFY messageChanged)
    Q_PROPERTY(bool isCollapsed READ isCollapsed NOTIFY messageChanged)
    Q_PROPERTY(bool isForwarded READ isForwarded NOTIFY messageChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessage cannot be created in QML.")
public:
    explicit QxTdMessage(QObject *parent = nullptr);

    QString qmlChatId() const;
    qint64 chatId() const;
    QString getSenderInitials() const;

    QxTdMessageSender *sender() const;

    void unmarshalJson(const QJsonObject &json) override;
    void unmarshalUpdateContent(const QJsonObject &content);

    QxTdMessageSendingState *sendingState() const;

    QxTdMessageSchedulingState *schedulingState() const;

    bool isOutgoing() const;

    bool isPinned() const;

    bool isEdited() const;

    void setIsEdited(const bool value);

    bool canBeEdited() const;

    bool canBeForwarded() const;

    bool canBeSaved() const;

    bool canBeDeletedOnlyForSelf() const;

    bool canBeDeletedForAllUsers() const;

    bool canGetStatistics() const;

    bool canGetMessageThread() const;

    bool canGetViewers() const;

    bool canGetMediaTimestampLinks() const;

    bool hasTimestampedMedia() const;

    bool isChannelPost() const;

    bool containsUnreadMention() const;

    QDateTime qmlDate() const;
    qint32 date() const;

    QDateTime qmlEditDate() const;
    qint32 editDate() const;

    QxTdMessageForwardInfo *forwardInfo() const;

    QxTdMessageInteractionInfo *interactionInfo() const;

    qint64 replyToMessageId() const;
    QString qmlReplyToMessageId() const;

    qint64 messageThreadId() const;
    QString qmlMessageThreadId() const;

    qint32 ttl() const;



    QString views() const;


    QxTdMessageContent *content() const;

    QxTdReplyMarkup *replyMarkup() const;

    bool isForwarded() const;

    QString summary() const;

    Q_INVOKABLE QString formatDate(const QDateTime &dt);

    bool isValid() const;

    bool sameSenderAsPreviousMessage() const;

    void setPreviousSender(QxTdMessageSender *sender);

    bool sameSenderAsNextMessage() const;

    void setNextSender(QxTdMessageSender *sender);

    bool isLatest() const;

    bool isCollapsed() const;

    void collapse();

    bool isReply() const;
    QxTdMessage *messageRepliedTo();

signals:
    void messageChanged();
    void senderChanged();
    void sendingStateChanged();
    void previousSenderChanged();
    void nextSenderChanged();
    void messageRepliedToChanged();
    void highlight();

private slots:
    void updateSendingState(const QJsonObject &json);
    void updateSchedulingState(const QJsonObject &json);
    void handleMessage(const QJsonObject &json);

private:
    QScopedPointer<QxTdMessageSender> m_sender;
    QxTdInt64 m_chatId;
    QScopedPointer<QxTdMessageSendingState> m_sendingState;
    QScopedPointer<QxTdMessageSchedulingState> m_schedulingState;
    bool m_isOutgoing;
    bool m_isPinned;
    bool m_canBeEdited;
    bool m_canBeForwarded;
    bool m_canBeSaved;
    bool m_canBeDeletedOnlyForSelf;
    bool m_canBeDeletedForAllUsers;
    bool m_canGetStatistics;
    bool m_canGetMessageThread;
    bool m_canGetViewers;
    bool m_canGetMediaTimestampLinks;
    bool m_hasTimestampedMedia;
    bool m_isChannelPost;
    bool m_containsUnreadMention;
    qint32 m_date;
    qint32 m_editDate;
    QScopedPointer<QxTdMessageForwardInfo> m_forwardInfo;
    QScopedPointer<QxTdMessageInteractionInfo> m_interactionInfo;
    qint64 m_replyInChatId;
    QxTdInt64 m_replyToMessageId;
    QxTdInt64 m_messageThreadId;
    qint32 m_ttl;
    qint64 m_viaBotUserId;
    qint64 m_mediaAlbumId;
    QString m_restrictionReason;
    QScopedPointer<QxTdMessageContent> m_content;
    QScopedPointer<QxTdReplyMarkup> m_replyMarkup;

    bool m_isEdited;
    bool m_isValid;
    QPointer<QxTdMessageSender> m_previousSender, m_nextSender;
    QPointer<QxTdMessage> m_messageRepliedTo;
    bool m_isCollapsed;

};

#endif // QX_TD_MESSAGE_H
