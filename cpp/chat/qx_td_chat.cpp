#include "utils/qx_td_translate_tools.h"
#include "qx_td_chat.h"
#include <QDebug>
#include <QJsonArray>
#include "qx_td_chat_type_factory.h"
#include "qx_td_chat_action_factory.h"
#include "client/qx_td_client.h"
#include "qx_td_secret_chat.h"
#include "qx_td_chat_list_model.h"
#include "chat/requests/qx_td_open_chat_request.h"
#include "chat/requests/qx_td_close_chat_request.h"
#include "chat/requests/qx_td_close_secret_chat_request.h"
#include "chat/requests/qx_td_set_chat_title_request.h"
#include "chat/requests/qx_td_send_chat_action_request.h"
#include "chat/requests/qx_td_delete_chat_history_request.h"
#include "chat/requests/qx_td_leave_chat_request.h"
#include "chat/requests/qx_td_close_secret_chat_request.h"
#include "chat/requests/qx_td_set_chat_notification_settings.h"
#include "user/qx_td_users.h"
#include "common/qx_td_helpers.h"
#include "messages/requests/qx_td_get_message_request.h"
#include "utils/qx_td_await.h"

QxTdChat::QxTdChat(QObject *parent)
    : QxAbstractInt64Id(parent)
    , m_chatType(nullptr)
    , m_chatActionBar(nullptr)
    , m_chatPhoto(new QxTdChatPhoto)
    , m_lastMessage(new QxTdMessage)
    , m_position(new QxTdChatPosition)
    , m_canBeReported(false)
    , m_unreadCount(0)
    , m_lastReadInboxMsg(0)
    , m_lastReadOutboxMsg(0)
    , m_unreadMentionCount(0)
    , m_notifySettings(new QxTdNotificationSettings)
    , m_messages(0)
    , m_chatOpen(false)
    , m_draftMessage(new QxTdDraftMessage)
{
    setType(CHAT);
    m_my_id = QxTdClient::instance()->getOption("my_id").toLongLong();
    m_messages = new QxTdObjectListModel<QxTdMessage>(this, "", "id");
    connect(QxTdClient::instance(), &QxTdClient::updateChatAction, this, &QxTdChat::handleUpdateChatAction);
    connect(QxTdClient::instance(), &QxTdClient::updateChatActionBar, this, &QxTdChat::handleUpdateChatActionBar);
    connect(QxTdClient::instance(), &QxTdClient::updateChatIsBlocked, this, &QxTdChat::handleUpdateChatIsBlocked);
    connect(QxTdClient::instance(), &QxTdClient::foundChatMessages, this, &QxTdChat::handleFoundChatMessages);
    connect(m_lastMessage.data(), &QxTdMessage::senderChanged, this, &QxTdChat::summaryChanged);
    emit messagesChanged();
}

void QxTdChat::unmarshalJson(const QJsonObject &json)
{
    QxAbstractInt64Id::unmarshalJson(json);
    updateChatReadInbox(json);
    updateChatReadOutbox(json);
    updateChatTitle(json);
    updateChatBlocked(json);

    m_chatType.reset(QxTdChatFactory::createType(json["type"].toObject(), this));
    emit chatTypeChanged(m_chatType.data());

    updateChatActionBar(json["action_bar"].toObject());
    updateChatPosition(json);

    if (isSecret()) {
        auto c = static_cast<QxTdSecretChat *>(this);
        c->getSecretChatData();
    }
    updateLastMessage(json["last_message"].toObject());

    m_canBeReported = json["can_be_reported"].toBool();
    emit canBeReportedChanged();
    updateChatUnreadMentionCount(json);
    updateChatReplyMarkup(json);
    updateChatDraftMessage(json["draft_message"].toObject());
    m_notifySettings->unmarshalJson(json["notification_settings"].toObject());
    emit notificationSettingsChanged();
    updateChatPhoto(json["photo"].toObject());
    onChatDeserialized();
}

QString QxTdChat::title() const
{
    if (isMyself())
        return qxTranslate("Saved Messages");
    else if (isPrivate() || isSecret()) {
        if (user()->isDeleted()) {
            return qxTranslate("Deleted User");
        }
    }
    return m_title;
}

QxTdMessage *QxTdChat::lastMessage() const
{
    return m_lastMessage.data();
}

QxTdChatPhoto *QxTdChat::chatPhoto() const
{
    return m_chatPhoto.data();
}

QString QxTdChat::initials() const
{
    return QxTdHelpers::initials(m_title);
}

QString QxTdChat::avatarColor(qint64 userId)
{
    return isMyself() ? QxTdHelpers::selfColor() : QxTdHelpers::avatarColor(userId);
}

void QxTdChat::sendChatAction(bool isTyping)
{
    //TODO: Make more actions available
    QScopedPointer<QxTdSendChatActionRequest> req(new QxTdSendChatActionRequest);
    req->setChatId(id());
    QxTdClient::instance()->send(req.data());
}

bool QxTdChat::isMuted() const
{
    return m_notifySettings->muteFor() > 0;
}

bool QxTdChat::isPrivate() const
{
    return qobject_cast<QxTdChatTypePrivate *>(m_chatType.data()) != nullptr;
}

bool QxTdChat::isSecret() const
{
    return qobject_cast<QxTdChatTypeSecret *>(m_chatType.data()) != nullptr;
}

bool QxTdChat::isGroup() const
{
    return isBasicGroup() || isSuperGroup();
}

bool QxTdChat::isBasicGroup() const
{
    return qobject_cast<QxTdChatTypeBasicGroup *>(m_chatType.data()) != nullptr;
}

bool QxTdChat::isSuperGroup() const
{
    auto result = qobject_cast<QxTdChatTypeSuperGroup *>(m_chatType.data());
    return result != nullptr && !result->isChannel();
}

bool QxTdChat::isChannel() const
{
    auto result = qobject_cast<QxTdChatTypeSuperGroup *>(m_chatType.data());
    return result != nullptr && result->isChannel();
}

bool QxTdChat::isMyself() const
{
    return id() == m_my_id;
}

bool QxTdChat::isWritable() const
{
    return true;
}

bool QxTdChat::isOpen() const
{
    return m_chatOpen;
}

bool QxTdChat::isPinned() const
{
    return m_position->isPinned();
}

bool QxTdChat::isBot() const {
    if (isPrivate()) {
        auto userChatType = qobject_cast<QxTdChatTypePrivate *>(m_chatType.data());
        if (userChatType->user()->isBot()) {
            return true;
        }
    }
    return false;
}

bool QxTdChat::isBlocked() const {
    return m_chatBlocked;
}

bool QxTdChat::canBeReported() const
{
    return m_canBeReported;
}

bool QxTdChat::hasUnreadMessages() const
{
    return unreadCount() > 0;
}

QString QxTdChat::qmlUnreadCount() const
{
    return m_unreadCount.toQmlValue();
}

qint32 QxTdChat::unreadCount() const
{
    return m_unreadCount.value();
}

QString QxTdChat::qmlLastReadInboxMessageId() const
{
    return m_lastReadInboxMsg.toQmlValue();
}

qint64 QxTdChat::lastReadInboxMessageId() const
{
    return m_lastReadInboxMsg.value();
}

QString QxTdChat::qmlLastReadOutboxMessageId() const
{
    return m_lastReadOutboxMsg.toQmlValue();
}

qint64 QxTdChat::lastReadOutboxMessageId() const
{
    return m_lastReadOutboxMsg.value();
}

bool QxTdChat::hasUnreadMentions() const
{
    return unreadMentionCount() > 0;
}

QString QxTdChat::qmlUnreadMentionCount() const
{
    return m_unreadMentionCount.toQmlValue();
}

qint32 QxTdChat::unreadMentionCount() const
{
    return m_unreadMentionCount.value();
}

QString QxTdChat::qmlOnlineMemberCount() const
{
    return m_onlineMemberCount.toQmlValue();
}

qint32 QxTdChat::onlineMemberCount() const
{
    return m_onlineMemberCount.value();
}

QString QxTdChat::qmlReplyMarkupMessageId() const
{
    return m_replyMarkupMessageId.toQmlValue();
}

qint64 QxTdChat::replyMarkupMessageId() const
{
    return m_replyMarkupMessageId.value();
}

QxTdMessage *QxTdChat::replyMarkupMessage() const
{
    return m_replyMarkupMessage.data();
}

bool QxTdChat::hasReplyMarkup() const
{
    return m_replyMarkupMessageId.value() != 0;
}

void QxTdChat::loadReplyMarkupMessage()
{
    if (!hasReplyMarkup()) {
        return;
    }
    QScopedPointer<QxTdGetMessageRequest> req(new QxTdGetMessageRequest);
    req->setChatId(id());
    req->setMessageId(m_replyMarkupMessageId.value());
    QFuture<QxTdResponse> resp = req->sendAsync();
    qxAwait(resp);
    if (resp.result().isError()) {
        qWarning() << "Failed to get reply markup message with error: " << resp.result().errorString();
        return;
    }
    m_replyMarkupMessage.reset(new QxTdMessage(this));
    m_replyMarkupMessage->unmarshalJson(resp.result().json());
    emit replyMarkupMessageChanged();
}

QxTdNotificationSettings *QxTdChat::notificationSettings() const
{
    return m_notifySettings.data();
}
QxTdChatPosition *QxTdChat::position() const
{
    return m_position.data();
}

QString QxTdChat::action() const
{
    auto *users = QxTdUsers::instance()->model();
    QString actionMessage;
    switch (m_chatActions.count()) {
    case 0:
        return "";
    case 1: {
        auto *user = users->getByUid(QString::number(m_chatActions.first().userId.value()));

        if (user) {
            if (m_chatActions.first().isPersonal)
                actionMessage = m_chatActions.first().personal_description;
            else
                actionMessage = QString("%1 %2 ").arg(user->firstName(), m_chatActions.first().singular_description);
        }
    } break;
    case 2: {
        auto *user1 = users->getByUid(
                QString::number(m_chatActions.first().userId.value()));

        auto *user2 = users->getByUid(
                QString::number(m_chatActions.last().userId.value()));

        if (user1 && user2)
            actionMessage = QString("%1, %2 %3").arg( 
                    user1->firstName(), user2->firstName(), m_chatActions.last().plural_description);
    } break;
    default: {
        actionMessage = QString("%1 %2").arg(
                                                m_chatActions.count())
                                .arg(m_chatActions.first().plural_description);
    }
    }
    return actionMessage;
}

QxTdUser *QxTdChat::user() const {
    if (isPrivate() || isSecret()) {
        auto userChatType = qobject_cast<QxTdChatTypePrivate *>(m_chatType.data());
        return userChatType->user();
    }
    return nullptr;
}

QVariant QxTdChat::summary()
{
    QVariantList summary;
    if (draftMessage()->inputMessageText()->text() != "" || draftMessage()->replyToMessageId() != 0) {
        summary.insert(0, QString(qxTranslate("Draft:")));
        summary.insert(1, draftMessage()->inputMessageText()->text());
    } else {
        summary.insert(0, QString());
        if (action() != "") {
            summary.insert(1, action());
        } else if (!m_lastMessage->isValid()) {
            summary.insert(1, QString());
        } else if ((isPrivate() || isSecret()) && !m_lastMessage->isOutgoing()) {
            summary.insert(1, m_lastMessage->summary());
        } else if (!m_lastMessage->sender()->displayName().isEmpty()) {
            summary.insert(1, QString("%1: %2").arg(m_lastMessage->isOutgoing() ? qxTranslate("Me") : m_lastMessage->sender()->displayName(), m_lastMessage->summary()));
        } else {
            summary.insert(1, m_lastMessage->summary());
        }
    }
    return QVariant::fromValue(summary);
}

QObject *QxTdChat::messages() const
{
    return m_messages;
}

QList<QString> QxTdChat::foundMessages() const
{
    return m_foundMessages;
}

QString QxTdChat::nextFromMessageId() const
{
    return m_nextFromMessageId;
}

qint32 QxTdChat::foundMessagesTotalCount() const
{
    return m_foundMessagesTotalCount;
}

void QxTdChat::openChat()
{
    m_chatOpen = true;
    emit isOpenChanged();
    QScopedPointer<QxTdOpenChatRequest> req(new QxTdOpenChatRequest);
    req->setChatId(id());
    QxTdClient::instance()->send(req.data());
    onChatOpened();
    QxTdChat::loadReplyMarkupMessage();
}

void QxTdChat::closeChat()
{
    m_chatOpen = false;
    QScopedPointer<QxTdCloseChatRequest> req(new QxTdCloseChatRequest);
    req->setChatId(id());
    QxTdClient::instance()->send(req.data());
    m_currentMessageIndex = -1;
    m_foundMessages = QList<QString>();
    m_nextFromMessageId = "0";
    m_foundMessagesTotalCount = 0;
    emit foundMessagesChanged();
    emit nextFromMessageIdChanged();
    emit foundMessagesTotalCountChanged();
    emit closed();
    emit isOpenChanged();
}

void QxTdChat::setTitle(const QString &title)
{
    if (m_title != title) {
        QScopedPointer<QxTdSetChatTitleRequest> req(new QxTdSetChatTitleRequest);
        req->setTitle(id(), title);
        QxTdClient::instance()->send(req.data());
    }
}

void QxTdChat::deleteChatHistory(const bool &removeFromChatlist, const bool &forAllUsers)
{
    if (m_chatType->type() == QxTdChat::CHAT_TYPE_SUPERGROUP || isChannel()) {
        qWarning() << "Cannot delete chat history for supergroups or channels";
        return;
    }
    if (isSecret()) {
        auto secretChatType = qobject_cast<QxTdChatTypeSecret *>(m_chatType.data());
        QScopedPointer<QxTdCloseSecretChatRequest>
                req(new QxTdCloseSecretChatRequest);
        req->setSecretChatId(secretChatType->secretChatId());
        QxTdClient::instance()->send(req.data());
    }
    QScopedPointer<QxTdDeleteChatHistoryRequest> req(new QxTdDeleteChatHistoryRequest);
    req->setChatId(id());
    req->setRemoveFromChatList(removeFromChatlist);
    req->setRevoke(forAllUsers);
    QxTdClient::instance()->send(req.data());
}

void QxTdChat::leaveSecretChat() {
    if (m_chatType->type() == QxTdChat::CHAT_TYPE_SECRET) {
        QScopedPointer<QxTdCloseSecretChatRequest> req(new QxTdCloseSecretChatRequest);
        auto c = static_cast<QxTdSecretChat *>(this);
        req->setSecretChatId(c->secretChatId());
        QxTdClient::instance()->send(req.data());
    }
}

void QxTdChat::leaveChat()
{
    /**
     * Because telegram likes to have all different types of
     * groups and it is probably going to change again. SO let's
     * for the sake of simplicity use a switch and handle each type
     * appropriately.
     *
     * Currently private & secret chats can only delete history and be removed
     * from chatlist.
     *
     * Supergroups and basicgroups can be left using the id()
     * Strangely it takes the id and not superGroupId and basicGroupId
     */
    QScopedPointer<QxTdLeaveChatRequest> req(new QxTdLeaveChatRequest);
    switch (m_chatType->type()) {
    case QxTdChat::CHAT_TYPE_PRIVATE:
        return deleteChatHistory(true);
    case QxTdChat::CHAT_TYPE_SECRET: {
        leaveSecretChat();
        return deleteChatHistory(true);
    }
    case QxTdChat::CHAT_TYPE_SUPERGROUP:
    case QxTdChat::CHAT_TYPE_BASIC_GROUP: {
        req->setChatId(id());
        break;
    }
    default:
        break;
    }
    QxTdClient::instance()->send(req.data());
    QxTdChatListModel::instance()->model()->remove(this);
}

void QxTdChat::updateChatReadInbox(const QJsonObject &json)
{
    m_lastReadInboxMsg = json["last_read_inbox_message_id"].toVariant().toLongLong();
    emit lastReadInboxMessageIdChanged();
    m_unreadCount = json["unread_count"].toInt();
    emit unreadCountChanged();
    QxTdClient::instance()->setUnreadMapEntry(id(), unreadCount());
}

void QxTdChat::updateChatReadOutbox(const QJsonObject &json)
{
    m_lastReadOutboxMsg = json["last_read_outbox_message_id"].toVariant().toLongLong();
    emit lastReadOutboxMessageIdChanged();
}

void QxTdChat::updateNonFilterChatListPosition(const QJsonObject &new_position)
{
    auto chatList = new_position["list"].toObject();
    if (!chatList.isEmpty() && chatList["@type"].toString() != "chatListFilter") {
        m_position->unmarshalJson(new_position);
        emit positionChanged();
        emit isPinnedChanged();
    }
}

void QxTdChat::updateChatPosition(const QJsonObject &json)
{
    auto new_position = json["position"].toObject();
    if (!new_position.isEmpty()) {
        updateNonFilterChatListPosition(new_position);
    }
}

void QxTdChat::updateChatPositions(const QJsonObject &json)
{
    auto positions = json["positions"].toArray();
    for (auto position : positions) {
        // TODO: re: #258.2 - handle multiple chat lists
        updateNonFilterChatListPosition(position.toObject());
    }
}

void QxTdChat::updateChatPhoto(const QJsonObject &photo)
{
    m_chatPhoto->unmarshalJson(photo);
    emit chatPhotoChanged(m_chatPhoto.data());

    if (m_chatPhoto->small()->local()->path().isEmpty()) {
        connect(m_chatPhoto->small()->local(), &QxTdLocalFile::pathChanged, this, &QxTdChat::handleChatPhotoDownloaded);
        m_chatPhoto->small()->downloadFile();
    } else {
        QxTdClient::instance()->setAvatarMapEntry(id(), m_chatPhoto->small()->local()->path());
    }
}

void QxTdChat::updateChatReplyMarkup(const QJsonObject &json)
{
    m_replyMarkupMessageId = json["reply_markup_message_id"];
    if (hasReplyMarkup() && m_chatOpen) {
        loadReplyMarkupMessage();
    }
}

void QxTdChat::updateChatDraftMessage(const QJsonObject &json)
{
    if (json.isEmpty()) {
        m_draftMessage.reset(new QxTdDraftMessage);
    } else {
        m_draftMessage->unmarshalJson(json);
    }
    emit summaryChanged();
    emit draftMessageChanged();
}

void QxTdChat::updateChatTitle(const QJsonObject &json)
{
    m_title = json["title"].toString();
    emit titleChanged(m_title);
}

void QxTdChat::updateChatBlocked(const QJsonObject &json)
{
    m_chatBlocked = json["is_blocked"].toBool();
    emit isBlockedChanged();
}

void QxTdChat::updateChatUnreadMentionCount(const QJsonObject &json)
{
    m_unreadMentionCount = json["unread_mention_count"];
    emit unreadMentionCountChanged();
}

void QxTdChat::updateChatOnlineMemberCount(const QJsonObject &json)
{
    m_onlineMemberCount = json["online_member_count"];
    emit onlineMemberCountChanged();
}

void QxTdChat::updateChatNotificationSettings(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }
    m_notifySettings->unmarshalJson(json["notification_settings"].toObject());
    emit notificationSettingsChanged();
}

void QxTdChat::updateLastMessage(const QJsonObject &json)
{
    if (json.isEmpty()) {
        m_lastMessage.reset(new QxTdMessage);
    } else {
        m_lastMessage->unmarshalJson(json);
    }
    emit lastMessageChanged(m_lastMessage.data());
    emit summaryChanged();
}

void QxTdChat::handleUpdateChatAction(const QJsonObject &json)
{
    const qint64 cid = json["chat_id"].toVariant().toLongLong();
    if (cid != id()) {
        return;
    }
    updateChatAction(json);
}

void QxTdChat::handleUpdateChatActionBar(const QJsonObject &json)
{
    const qint64 cid = json["chat_id"].toVariant().toLongLong();
    if (cid != id()) {
        return;
    }
    updateChatActionBar(json["action_bar"].toObject());
}

void QxTdChat::handleUpdateChatIsBlocked(const QJsonObject &data)
{
    const qint64 cid = data["chat_id"].toVariant().toLongLong();
    if (cid != id()) {
        return;
    }
    updateChatBlocked(data);
}

void QxTdChat::handleChatPhotoDownloaded()
{
    QxTdClient::instance()->setAvatarMapEntry(id(), m_chatPhoto->small()->local()->path());
}

void QxTdChat::onChatOpened() {

}

void QxTdChat::onChatClosed()
{
}

void QxTdChat::onChatDeserialized()
{
}

void QxTdChat::forwardMessage(const QString &messageId)
{
    QStringList forwardingMessages = QStringList(messageId);
    emit forwardingMessagesAction(forwardingMessages, this);
}

void QxTdChat::mute(const qint32 &duration) {
    QScopedPointer<QxTdSetChatNotificationSettings> req(new QxTdSetChatNotificationSettings);
    req->setNotificationSettings(m_notifySettings.data());
    req->setChatId(id());
    m_notifySettings->setMuteFor(duration);
    m_notifySettings->setUseDefaultMuteFor(false);
    QxTdClient::instance()->send(req.data());
}

void QxTdChat::updateChatAction(const QJsonObject &json)
{
    const qint64 user_id = json["sender_id"].toObject()["user_id"].toVariant().toLongLong();
    const QJsonObject data = json["action"].toObject();
    QxTdChatAction *action = QxTdChatActionFactory::create(data, this);
    if (action->type() == QxTdChatAction::Type::CHAT_ACTION_CANCEL && m_chatActions.contains(user_id)) {
        m_chatActions.remove(user_id);
    } else if (action->type() != QxTdChatAction::Type::CHAT_ACTION_CANCEL && !m_chatActions.contains(user_id)) {
        m_chatActions.insert(user_id, useraction(user_id, user_id == id(), action->personal_description(), action->singular_description(),
                                                 action->plural_description()));
    }
    action->deleteLater();
    emit summaryChanged();
}

void QxTdChat::updateChatActionBar(const QJsonObject &json)
{
    m_chatActionBar.reset(QxTdChatActionBarFactory::create(json, this));
    emit chatActionBarChanged();
}

QxTdChatType *QxTdChat::chatType() const
{
    return m_chatType.data();
}

QxTdChatPhoto::QxTdChatPhoto(QObject *parent)
    : QxTdPhoto(parent)
{
    setType(CHAT_PHOTO);
}

QString QxTdChat::formatDate(const QDateTime &dt)
{
    return QxTdHelpers::formatDate(dt);
}

int QxTdChat::currentMessageIndex() const
{
    return m_currentMessageIndex;
}

void QxTdChat::positionMessageListViewAtIndex(int index)
{
    m_currentMessageIndex = index;
    emit currentMessageIndexChanged();
}

QxTdDraftMessage *QxTdChat::draftMessage() const
{
    return m_draftMessage.data();
}

QString QxTdChat::smallPhotoPath() const
{
    if (isPrivate() || isSecret() ) {
        auto userChatType = qobject_cast<QxTdChatTypePrivate *>(m_chatType.data());
        if (userChatType->user()->isDeleted()) {
            return "image://theme/account";
        }
    }
    return m_chatPhoto->smallPhotoPath();
}

bool QxTdChat::hasChatActionBar() const {
    return !m_chatActionBar.isNull();
}

QxTdChatActionBar *QxTdChat::chatActionBar() const {
    return m_chatActionBar.data();
}

void QxTdChat::setFoundMessages(QList<QString> foundMessages) {
    m_foundMessages = QList<QString>();
    emit foundMessagesChanged();
}

void QxTdChat::setNextFromMessageId(QString &nextFromMessageId) {
    if (m_nextFromMessageId == nextFromMessageId) {
        return;
    }
    m_nextFromMessageId = nextFromMessageId;
    emit nextFromMessageIdChanged();
}

void QxTdChat::handleFoundChatMessages(const QJsonObject &json)
{
    auto messages = json["messages"].toArray();
    if (messages.isEmpty()) {
        return;
    }
    for (auto message : messages) {
        if (message.toObject()["chat_id"].toVariant().toLongLong() != id()) {
            return;
        }
        m_foundMessages.append(message.toObject()["id"].toVariant().toString());
    }
    m_foundMessagesTotalCount = json["total_count"].toVariant().toInt();
    if (messages.size() == m_foundMessagesTotalCount) {
        m_nextFromMessageId = "0";
    } else {
        m_nextFromMessageId = json["next_from_message_id"].toVariant().toString();
    }
    emit foundMessagesChanged();
    emit nextFromMessageIdChanged();
    emit foundMessagesTotalCountChanged();
}
