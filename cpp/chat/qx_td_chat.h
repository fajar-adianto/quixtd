#ifndef QX_TD_CHAT_H
#define QX_TD_CHAT_H

#include "qx_td_chat_type.h"
#include "qx_td_chat_action_bar.h"
#include "qx_td_chat_position.h"
#include "common/qx_abstract_int64_id.h"
#include "files/qx_td_photo.h"
#include "messages/qx_td_message.h"
#include "messages/qx_td_draft_message.h"
#include "models/qx_td_object_list_model.h"
#include "notifications/qx_td_notification_settings.h"

class QxTdChatPhoto : public QxTdPhoto
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdChatPhoto cannot be created in QML.")
    Q_DISABLE_COPY(QxTdChatPhoto)
public:
    explicit QxTdChatPhoto(QObject *parent = nullptr);
};

/**
 * @brief The QxTdChat class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat.html
 *
 * Some extensions have been made to this class to include the messages
 * model for the chat on each instance.
 */
class QxTdChat : public QxAbstractInt64Id
{
    Q_OBJECT
    Q_PROPERTY(QxTdChatType *chatType READ chatType NOTIFY chatTypeChanged)
    Q_PROPERTY(QxTdUser *user READ user NOTIFY chatTypeChanged)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QxTdChatPhoto *chatPhoto READ chatPhoto NOTIFY chatPhotoChanged)
    Q_PROPERTY(QString initials READ initials NOTIFY initialsChanged)
    Q_PROPERTY(QString smallPhotoPath READ smallPhotoPath NOTIFY chatPhotoChanged)
    Q_PROPERTY(QxTdMessage *lastMessage READ lastMessage NOTIFY lastMessageChanged)
    Q_PROPERTY(bool isMuted READ isMuted NOTIFY notificationSettingsChanged)
    Q_PROPERTY(bool isSecret READ isSecret NOTIFY isSecretChanged)
    Q_PROPERTY(bool isGroup READ isGroup NOTIFY isGroupChanged)
    Q_PROPERTY(bool isBasicGroup READ isBasicGroup NOTIFY isBasicGroupChanged)
    Q_PROPERTY(bool isSuperGroup READ isSuperGroup NOTIFY isSuperGroupChanged)
    Q_PROPERTY(bool isWritable READ isWritable NOTIFY isWritableChanged)
    Q_PROPERTY(bool isChannel READ isChannel NOTIFY isChannelChanged)
    Q_PROPERTY(bool isPrivate READ isPrivate NOTIFY isPrivateChanged)
    Q_PROPERTY(bool isMyself READ isMyself NOTIFY isMyselfChanged)
    Q_PROPERTY(bool isOpen READ isOpen NOTIFY isOpenChanged)
    Q_PROPERTY(bool isBot READ isBot NOTIFY isBotChanged)
    Q_PROPERTY(bool isBlocked READ isBlocked NOTIFY isBlockedChanged)
    Q_PROPERTY(bool canBeReported READ canBeReported NOTIFY canBeReportedChanged)
    Q_PROPERTY(bool hasUnreadMessages READ hasUnreadMessages NOTIFY unreadCountChanged)
    Q_PROPERTY(QString unreadCount READ qmlUnreadCount NOTIFY unreadCountChanged)
    Q_PROPERTY(QString lastReadInboxMessageId READ qmlLastReadInboxMessageId NOTIFY lastReadInboxMessageIdChanged)
    Q_PROPERTY(QString lastReadOutboxMessageId READ qmlLastReadOutboxMessageId NOTIFY lastReadOutboxMessageIdChanged)
    Q_PROPERTY(bool hasUnreadMentions READ hasUnreadMentions NOTIFY unreadMentionCountChanged)
    Q_PROPERTY(QString unreadMentionCount READ qmlUnreadMentionCount NOTIFY unreadMentionCountChanged)
    Q_PROPERTY(QString onlineMemberCount READ qmlOnlineMemberCount NOTIFY onlineMemberCountChanged)
    Q_PROPERTY(QString replyMarkupMessageId READ qmlReplyMarkupMessageId NOTIFY replyMarkupMessageChanged)
    Q_PROPERTY(QxTdMessage *replyMarkupMessage READ replyMarkupMessage NOTIFY replyMarkupMessageChanged)
    Q_PROPERTY(QxTdNotificationSettings *notificationSettings READ notificationSettings NOTIFY notificationSettingsChanged)
    Q_PROPERTY(QVariant summary READ summary NOTIFY summaryChanged)
    Q_PROPERTY(QString action READ action NOTIFY summaryChanged)
    Q_PROPERTY(int currentMessageIndex READ currentMessageIndex NOTIFY currentMessageIndexChanged)
    Q_PROPERTY(QxTdDraftMessage *draftMessage READ draftMessage NOTIFY draftMessageChanged)
    Q_PROPERTY(QxTdChatPosition *position READ position NOTIFY positionChanged)
    Q_PROPERTY(bool hasChatActionBar READ hasChatActionBar NOTIFY chatActionBarChanged)
    Q_PROPERTY(QxTdChatActionBar *chatActionBar READ chatActionBar NOTIFY chatActionBarChanged)
    Q_PROPERTY(bool isPinned READ isPinned NOTIFY isPinnedChanged)

    // TODO:
    // string:client_data
    Q_PROPERTY(QObject *messages READ messages NOTIFY messagesChanged)
    Q_PROPERTY(QList<QString> foundMessages READ foundMessages WRITE setFoundMessages NOTIFY foundMessagesChanged)
    Q_PROPERTY(QString nextFromMessageId READ nextFromMessageId WRITE setNextFromMessageId NOTIFY nextFromMessageIdChanged)
    Q_PROPERTY(qint32 foundMessagesTotalCount READ foundMessagesTotalCount NOTIFY foundMessagesTotalCountChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdChat cannot be created in QML.")

public:
    explicit QxTdChat(QObject *parent = nullptr);
    void unmarshalJson(const QJsonObject &json) override;
    /**
     * @brief Type of the chat
     */
    QxTdChatType *chatType() const;
    /**
     * @brief Chat title
     */
    QString title() const;
    /**
     * @brief Last message in the chat,
     * @return QxTdMessage* or NULL
     */
    QxTdMessage *lastMessage() const;
    /**
     * @brief Chat photo
     * @return QxTdChatPhoto* or NULL
     */
    QxTdChatPhoto *chatPhoto() const;
    /**
     * @brief Chat title initials
     */
    QString initials() const;
    /**
     * @brief Chat title background color
     */
    Q_INVOKABLE QString avatarColor(qint64 userId);

    /**
     * @brief Send various actions a user can do in a chat to all peers
     */
    Q_INVOKABLE void sendChatAction(bool isTyping);
    /**
     * @brief True if chat is muted
     */
    bool isMuted() const;
    /**
     * @brief True if chat is a secret chat
     */
    bool isSecret() const;
    /**
     * @brief True if chat is a group chat (normal or supergroup)
     */
    bool isGroup() const;
    /**
     * @brief True if chat is a basic group chat
     */
    bool isBasicGroup() const;
    /**
     * @brief True if chat is a super group chat
     */
    bool isSuperGroup() const;
    /**
     * @brief True if chat is a channel
     */
    bool isChannel() const;
    /**
     * @brief True if chat is a private conversation
     */
    bool isPrivate() const;
    /**
     * @brief True if chat is a conversation with myself (Saved messages)
     */
    bool isMyself() const;

    bool isOpen() const;

    bool isPinned() const;

    bool isBot() const;

    bool isBlocked() const;
    /**
     * @brief True if chat is writable, i.e. messages can be sent by the user
     * This method must be overridden in child classes
     */
    virtual bool isWritable() const;
    /**
     * @brief True if the chat can be reported to Telegram mods
     *
     * Reports can be made through QxTdReportChatRequest
     */
    bool canBeReported() const;
    /**
     * @brief Chat has unread messages
     */
    bool hasUnreadMessages() const;
    /**
     * @brief String representation of Unread count for qml
     */
    QString qmlUnreadCount() const;
    /**
     * @brief Number of unread messages in the chat
     */
    qint32 unreadCount() const;
    /**
     * @brief Identifier of last read incoming message for qml
     */
    QString qmlLastReadInboxMessageId() const;
    /**
     * @brief Identifier of last read incoming message
     */
    qint64 lastReadInboxMessageId() const;

    /**
     * @brief Identifier of last read outgoing message for qml
     */
    QString qmlLastReadOutboxMessageId() const;
    /**
     * @brief Identifier of last read outgoing message
     */
    qint64 lastReadOutboxMessageId() const;
    /**
     * @brief Chat has unread mentions
     */
    bool hasUnreadMentions() const;
    /**
     * @brief Number of unread mentions for qml
     */
    QString qmlUnreadMentionCount() const;
    /**
     * @brief Number of unread mentions
     */
    qint32 unreadMentionCount() const;
    /**
     * @brief Number of online members for qml
     */
    QString qmlOnlineMemberCount() const;
    /**
     * @brief Number of online members
     */
    qint32 onlineMemberCount() const;
    /**
     * @brief Id of the message from which reply markup needs to be used for qml
     */
    QString qmlReplyMarkupMessageId() const;
    /**
     * @brief Id of the message from which reply markup needs to be used
     * 0 if there is no default custom reply markup in the chat.
     */
    qint64 replyMarkupMessageId() const;
    /**
     * @brief message replyMarkupMessageId is pointing to
     */
    QxTdMessage *replyMarkupMessage() const;
    bool hasReplyMarkup() const;
    void loadReplyMarkupMessage();
    /**
     * @brief Notification settings for this chat
     */
    QxTdNotificationSettings *notificationSettings() const;

    QxTdChatPosition *position() const;

    /**
     * @brief Summary of current chat state in the UI
     *
     * This can be used to show a snippet of last message
     * or "User is typing..." type messages.
     */
    virtual QVariant summary();

    virtual QString action() const;

    QxTdUser *user() const;

    /**
     * @brief Message model
     */
    QObject *messages() const;

    /**
     * @brief current messages index in message list view
     */
    int currentMessageIndex() const;

    /**
     * @brief position message list view at index
     */
    void positionMessageListViewAtIndex(int index);

    /**
     * @brief A draft of a message in the chat; may be null.
     */
    QxTdDraftMessage *draftMessage() const;

    /**
     * @brief found messages of a search in the chat
     */
    QList<QString> foundMessages() const;

    /**
     * @brief next message id to get next search page
     */
    QString nextFromMessageId() const;

    /**
     * @brief total found messages of a search in the chat
     */
    qint32 foundMessagesTotalCount() const;

    /**
     * @brief Open chat
     *
     * This method should be called if the chat is opened by the user.
     * Many useful activities depend on the chat being opened or closed
     * (e.g., in supergroups and channels all updates are received only for opened chats).
     */
    Q_INVOKABLE void openChat();

    /**
     * @brief Close chat
     *
     * This method should be called if the chat is closed by the user.
     * Many useful activities depend on the chat being opened or closed
     */
    Q_INVOKABLE void closeChat();

    /**
     * @brief Set chat title
     */
    Q_INVOKABLE void setTitle(const QString &title);

    /**
     * @brief Delete own messages in the chat
     */
    Q_INVOKABLE void deleteChatHistory(const bool &removeFromChatlist = false, const bool &forAllUsers = false);

    /**
     * @brief Leave chat and clear any history if possible
     */
    Q_INVOKABLE void leaveChat();

    Q_INVOKABLE void leaveSecretChat();

    /**
     * @brief Leave chat and clear any history if possible
     */
    Q_INVOKABLE void forwardMessage(const QString &messageId);

    /**
     * @brief Mute chat for x minutes or unmute chat (x == 0)
     */
    Q_INVOKABLE void mute(const qint32 &duration);

    QJsonObject lastMessageJson() const
    {
        return m_lastMsgJson;
    }

    Q_INVOKABLE QString formatDate(const QDateTime &dt);

    QString smallPhotoPath() const;

    bool hasChatActionBar() const;
    QxTdChatActionBar *chatActionBar() const;
    void setFoundMessages(QList<QString> foundMessages);
    void setNextFromMessageId(QString &nextFromMessageId);

signals:
    void chatTypeChanged(QxTdChatType *chatType);
    void chatActionBarChanged();
    void titleChanged(QString title);
    void lastMessageChanged(QxTdMessage *lastMessage);
    void chatPhotoChanged(QxTdChatPhoto *chatPhoto);
    void initialsChanged(QString initials);
    void isSecretChanged();
    void isGroupChanged();
    void isBasicGroupChanged();
    void isSuperGroupChanged();
    void isChannelChanged();
    void isPrivateChanged();
    void isMyselfChanged();
    void isWritableChanged();
    void isMutedChanged();
    void isOpenChanged();
    void isBotChanged();
    void isBlockedChanged();
    void canBeReportedChanged();
    void unreadCountChanged();
    void lastReadInboxMessageIdChanged();
    void lastReadOutboxMessageIdChanged();
    void unreadMentionCountChanged();
    void onlineMemberCountChanged();
    void replyMarkupMessageChanged();
    void notificationSettingsChanged();
    void messagesChanged();
    void chatStatusChanged();
    void isPinnedChanged();
    void summaryChanged();
    void closed();
    void chatUpdated();
    void forwardingMessagesAction(QStringList forwardingMessages, QxTdChat *forwarded_from_chat);
    void currentMessageIndexChanged();
    void draftMessageChanged();
    void positionChanged();
    void foundMessagesChanged();
    void nextFromMessageIdChanged();
    void foundMessagesTotalCountChanged();

public slots:
    void updateChatReadInbox(const QJsonObject &json);
    void updateChatReadOutbox(const QJsonObject &json);
    void updateChatPhoto(const QJsonObject &photo);
    void updateChatReplyMarkup(const QJsonObject &json);
    void updateChatDraftMessage(const QJsonObject &json);
    void updateChatTitle(const QJsonObject &json);
    void updateChatBlocked(const QJsonObject &json);
    void updateChatPosition(const QJsonObject &json);
    void updateChatPositions(const QJsonObject &json);
    void updateNonFilterChatListPosition(const QJsonObject &new_position);
    void updateChatUnreadMentionCount(const QJsonObject &json);
    void updateChatOnlineMemberCount(const QJsonObject &json);
    void updateChatNotificationSettings(const QJsonObject &json);
    void updateLastMessage(const QJsonObject &json);
    void handleUpdateChatAction(const QJsonObject &json);
    void handleUpdateChatActionBar(const QJsonObject &json);
    void handleUpdateChatIsBlocked(const QJsonObject &data);
    void handleChatPhotoDownloaded();
    void handleFoundChatMessages(const QJsonObject &json);

protected:
    virtual void onChatOpened();
    virtual void onChatClosed();
    virtual void updateChatAction(const QJsonObject &json);
    virtual void updateChatActionBar(const QJsonObject &json);
    virtual void onChatDeserialized();

    QPointer<QxTdObjectListModel<QxTdMessage>> m_messages;

    QList<QString> m_foundMessages;
    QString m_nextFromMessageId;
    qint32 m_foundMessagesTotalCount;

private:
    Q_DISABLE_COPY(QxTdChat)
    QScopedPointer<QxTdChatType> m_chatType;
    QScopedPointer<QxTdChatActionBar> m_chatActionBar;
    QString m_title;
    qint64 m_my_id;
    QScopedPointer<QxTdMessage> m_lastMessage;
    QScopedPointer<QxTdChatPhoto> m_chatPhoto;
    QScopedPointer<QxTdChatPosition> m_position;
    bool m_canBeReported;
    QxTdInt32 m_unreadCount;
    QxTdInt64 m_lastReadInboxMsg;
    QxTdInt64 m_lastReadOutboxMsg;
    QxTdInt32 m_unreadMentionCount;
    QxTdInt32 m_onlineMemberCount;
    QxTdInt64 m_replyMarkupMessageId;
    QScopedPointer<QxTdMessage> m_replyMarkupMessage;
    QScopedPointer<QxTdNotificationSettings> m_notifySettings;
    bool m_chatOpen;
    bool m_chatBlocked;

    struct useraction
    {
        QxTdInt64 userId;
        bool isPersonal;
        QString personal_description;
        QString singular_description;
        QString plural_description;
        useraction() {}
        useraction(const qint64 id, const bool personal, const QString personal_desc, const QString singular_desc, const QString plural_desc)
            : userId(id)
            , isPersonal(personal)
            , personal_description(personal_desc)
            , singular_description(singular_desc)
            , plural_description(plural_desc)
        {
        }
    };

    QMap<qint64, useraction> m_chatActions;
    QJsonObject m_lastMsgJson;
    int m_currentMessageIndex = -1;
    QScopedPointer<QxTdDraftMessage> m_draftMessage;
};

#endif // QX_TD_CHAT_H
