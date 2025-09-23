#include "qx_td_chat_list_model.h"

#include "client/qx_td_client.h"
#include "chat/requests/qx_td_load_chats_request.h"
#include "chat/requests/qx_td_create_new_secret_chat_request.h"
#include "chat/requests/qx_td_create_private_chat_request.h"
#include "chat/requests/qx_td_get_chat_request.h"
#include "chat/requests/qx_td_set_pinned_chats_request.h"
#include "chat/requests/qx_td_leave_chat_request.h"
#include "chat/requests/qx_td_forward_messages_request.h"
#include "chat/requests/qx_td_set_chat_draft_request.h"
#include "chat/requests/qx_td_search_public_chat_request.h"
#include "chat/requests/qx_td_join_chat_request.h"
#include "chat/requests/qx_td_check_chat_invite_link_request.h"
#include "chat/requests/qx_td_join_chat_by_invite_link_request.h"
#include "chat/requests/qx_td_set_chat_message_ttl_request.h"
#include "messages/requests/qx_td_send_message_request.h"
#include "messages/requests/qx_td_open_message_content_request.h"
#include "messages/requests/qx_td_set_poll_answer_request.h"
#include "messages/requests/content/qx_td_input_message_text.h"
#include "common/qx_td_helpers.h"

#include "utils/qx_td_await.h"
#include "utils/qx_td_translate_tools.h"
#include "chat/qx_td_chat_type_factory.h"
#include "qx_td_secret_chat.h"

#include <QList>
#include <QVariant>

QPointer<QxTdChatListModel> QxTdChatListModel::s_chatlistmodel;

QxTdChatListModel::QxTdChatListModel(QObject *parent)
    : QObject(parent)
    , m_model(nullptr)
    , m_currentChat(nullptr)
    , m_forwardedFromChat(nullptr)
    , m_forwardingMessages(QStringList())
    , m_listMode(ListMode::Idle)
    , m_positionWaitTimer(new QTimer(this))
    , m_chatToOpenOnUpdate(0)
{
    if (s_chatlistmodel.isNull()) {
        s_chatlistmodel = this;
    }

    m_model = new QxTdObjectListModel<QxTdChat>(this, "", "id");
    m_positionWaitTimer->setInterval(180000);
    m_positionWaitTimer->setSingleShot(true);
    connect(this->m_positionWaitTimer, &QTimer::timeout, this, &QxTdChatListModel::onPositionInfoTimeout);

    connect(QxTdClient::instance(), &QxTdClient::chats, this, &QxTdChatListModel::handleChats);
    connect(QxTdClient::instance(), &QxTdClient::chat, this, &QxTdChatListModel::handleChat);
    connect(QxTdClient::instance(), &QxTdClient::updateNewChat, this, &QxTdChatListModel::handleUpdateNewChat);
    connect(QxTdClient::instance(), &QxTdClient::authStateChanged, this, &QxTdChatListModel::handleAuthStateChanges);
    connect(QxTdClient::instance(), &QxTdClient::updateChatPosition, this, &QxTdChatListModel::handleUpdateChatPosition);
    connect(QxTdClient::instance(), &QxTdClient::updateChatLastMessage, this, &QxTdChatListModel::handleUpdateChatLastMessage);
    connect(QxTdClient::instance(), &QxTdClient::updateChatReadInbox, this, &QxTdChatListModel::updateChatReadInbox);
    connect(QxTdClient::instance(), &QxTdClient::updateChatReadOutbox, this, &QxTdChatListModel::updateChatReadOutbox);
    connect(QxTdClient::instance(), &QxTdClient::updateChatPhoto, this, &QxTdChatListModel::handleUpdateChatPhoto);
    connect(QxTdClient::instance(), &QxTdClient::updateChatReplyMarkup, this, &QxTdChatListModel::handleUpdateChatReplyMarkup);
    connect(QxTdClient::instance(), &QxTdClient::updateChatDraftMessage, this, &QxTdChatListModel::handleUpdateChatDraftMessage);
    connect(QxTdClient::instance(), &QxTdClient::updateChatTitle, this, &QxTdChatListModel::handleUpdateChatTitle);
    connect(QxTdClient::instance(), &QxTdClient::updateChatUnreadMentionCount, this, &QxTdChatListModel::handleUpdateChatUnreadMentionCount);
    connect(QxTdClient::instance(), &QxTdClient::updateChatNotificationSettings, this, &QxTdChatListModel::handleUpdateChatNotificationSettings);
    connect(QxTdClient::instance(), &QxTdClient::updateChatOnlineMemberCount, this, &QxTdChatListModel::handleUpdateChatOnlineMemberCount);
}

QxTdChatListModel *QxTdChatListModel::instance()
{
    return s_chatlistmodel;
}

QxTdObjectListModel<QxTdChat> *QxTdChatListModel::model() const
{
    return m_model;
}

QxTdChat *QxTdChatListModel::currentChat() const
{
    return m_currentChat;
}

QxTdChat *QxTdChatListModel::chatById(const qint64 &chatId) const
{
    return m_model->getByUid(QString::number(chatId));
}

void QxTdChatListModel::createOrOpenSecretChat(const qint64 &userId)
{
    qint64 chatId = 0;
    foreach (QxTdChat *chat, m_model->toList()) {
        if (chat->isSecret()) {
            auto c = static_cast<QxTdSecretChat *>(chat);
            if (!c->isClosed() && c->userId() == userId) {
                chatId = c->id();
                break;
            }
        }
    }
    if (chatId == 0) {
        std::unique_ptr<QxTdCreateNewSecretChatRequest> req(new QxTdCreateNewSecretChatRequest);
        req->setUserId(userId);
        QFuture<QxTdResponse> resp = req->sendAsync();
        qxAwait(resp);
        if (resp.result().isError()) {
            qWarning() << "Error during secret chat creation:" << resp.result().errorString();
            return;
        }
        chatId = resp.result().json()["id"].toVariant().toLongLong();
        if (chatId == 0) {
            return;
        }
    }
    setCurrentChatById(chatId);
}

void QxTdChatListModel::createOrOpenPrivateChat(const qint64 &userId)
{
    std::unique_ptr<QxTdCreatePrivateChatRequest> req(new QxTdCreatePrivateChatRequest);
    req->setUserId(userId);
    QFuture<QxTdResponse> resp = req->sendAsync();
    qxAwait(resp);
    if (resp.result().isError()) {
        qWarning() << "Error during private chat creation:" << resp.result().errorString();
        return;
    }
    qint64 chatId = resp.result().json()["id"].toVariant().toLongLong();
    setCurrentChatById(chatId);
}

void QxTdChatListModel::createOrOpenSavedMessages() {
    createOrOpenPrivateChat(QxTdClient::instance()->getOption("my_id").toLongLong());
}

void QxTdChatListModel::setCurrentChatById(const qint64 &chatId)
{
    QxTdChat *currentChat = chatById(chatId);
    setCurrentChat(currentChat);
}

void QxTdChatListModel::setCurrentChatByUsername(const QString &username)
{
    qDebug() << "OPENING CHAT" << username;
    std::unique_ptr<QxTdSearchPublicChatRequest> req(new QxTdSearchPublicChatRequest);
    req->setChatUsername(username);
    QFuture<QxTdResponse> resp = req->sendAsync();
    qxAwait(resp);
    if (resp.result().isError()) {
        qWarning() << "Error during public chat search:" << resp.result().errorString();
        if (resp.result().errorCode() == 400)
            emit invalidChatUsername(username);
        return;
    }
    qint64 chatId = resp.result().json()["id"].toVariant().toLongLong();
    setCurrentChatById(chatId);
}

qint64 QxTdChatListModel::chatIdByUsername(const QString &username)
{
    std::unique_ptr<QxTdSearchPublicChatRequest> req(new QxTdSearchPublicChatRequest);
    req->setChatUsername(username);
    QFuture<QxTdResponse> resp = req->sendAsync();
    qxAwait(resp);
    if (resp.result().isError()) {
        qWarning() << "Error during public chat search:" << resp.result().errorString();
        return -1;
    }
    return resp.result().json()["id"].toVariant().toLongLong();
}

qint32 QxTdChatListModel::forwardingMessagesCount() const
{
    return m_forwardingMessages.length();
}

void QxTdChatListModel::setCurrentChat(QxTdChat *currentChat)
{
    if (currentChat == nullptr) {
        return;
    }
    if (m_currentChat && m_currentChat->isOpen()) {
        if (m_currentChat == currentChat)
            return;
        else
            m_currentChat->closeChat();
    }

    m_currentChat = currentChat;
    emit currentChatChanged();
}

QxTdChat *QxTdChatListModel::forwardedFromChat() const
{
    return m_forwardedFromChat;
}

void QxTdChatListModel::setForwardedFromChat(QxTdChat *forwardedFromChat)
{
    if (m_forwardedFromChat == forwardedFromChat)
        return;
    m_forwardedFromChat = forwardedFromChat;
}

QStringList QxTdChatListModel::forwardingMessages() const
{
    return m_forwardingMessages;
}

void QxTdChatListModel::setForwardingMessages(QStringList forwardingMessages)
{
    if (m_forwardingMessages == forwardingMessages)
        return;
    m_forwardingMessages = forwardingMessages;
}

void QxTdChatListModel::handleChat(const QJsonObject &data)
{
    std::unique_ptr<QxTdChat> chat(new QxTdChat);
    chat->unmarshalJson(data);
    handleUpdateNewChat(data);
}

void QxTdChatListModel::handleChats(const QJsonObject &data)
{
    QJsonArray chats = data["chat_ids"].toArray();
    if (chats.count() == 0) {
        qDebug() << "No more chats found, completing initial load.";
        m_receivedChatIds.clear();
        return;
    }
    qDebug() << "Received" << chats.count() << "chats";
    foreach (QJsonValue chat, chats) {
        auto chatId = chat.toVariant().toLongLong();
        if (chatId == 0) {
            continue;
        }
        m_receivedChatIds.append(chatId);
        //Only request chats that we did not receive already
        if (!chatById(chatId)) {
            std::unique_ptr<QxTdGetChatRequest> chatReq(new QxTdGetChatRequest);
            chatReq->setChatId(chatId);
            qDebug() << "Request chat id" << chatId << "to be added to chatmodel";
            chatReq->sendAsync();
        } else {
            qDebug() << "Chat" << chatId << "already received, ignoring";
        }
    }
    emit modelPopulatedCompleted();
}

void QxTdChatListModel::handleUpdateNewChat(const QJsonObject &data)
{
    const qint64 id = data["id"].toVariant().toLongLong();
    // Need to remember the model actually indexes on the qmlId variant which is a QString
    QxTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->unmarshalJson(data);
    } else {
        tdchat = QxTdChatFactory::createChat(data["type"].toObject());
        tdchat->unmarshalJson(data);
        m_model->append(tdchat);
        connect(tdchat, &QxTdChat::chatStatusChanged, this, &QxTdChatListModel::chatStatusChanged);
        connect(tdchat, &QxTdChat::forwardingMessagesAction, this, &QxTdChatListModel::handleForwardingMessagesAction);
        emit chatCreated(tdchat->id());
    }
    emit contentsChanged();
    if (m_chatToOpenOnUpdate == tdchat->id()) {
        qDebug() << "Auto-opening chat" << tdchat->id();
        setCurrentChat(tdchat);
        m_chatToOpenOnUpdate = 0;
    }
}

void QxTdChatListModel::handleUpdateChatPosition(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QxTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateChatPosition(data);
        // We also need to update the internal pinned chats list now
        // otherwise any pinned chats will get removed when togglePinChat() is called
        auto position = data["position"].toObject();
        if (!position.isEmpty() && position["list"].toObject()["@type"].toString() != "chatListFilter") {
            long long order = position["order"].toVariant().toLongLong();
            PinnedChat pinnedChat(id, order);
            if (position["is_pinned"].toVariant().toBool()) {
                if (!m_pinnedChats.contains(pinnedChat)) {
                    m_pinnedChats.append(pinnedChat);
                    std::sort(m_pinnedChats.begin(), m_pinnedChats.end());
                }
            } else {
                m_pinnedChats.removeAll(pinnedChat);
            }
        }
        emit contentsChanged();
    }
}

void QxTdChatListModel::handleUpdateChatLastMessage(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QxTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateLastMessage(data["last_message"].toObject());
        tdchat->updateChatPositions(data);
        emit contentsChanged();
    }
}

void QxTdChatListModel::handleAuthStateChanges(const QxTdAuthState *state)
{
    switch (state->type()) {
        case QxTdAuthState::Type::AUTHORIZATION_STATE_CLOSED: {
            m_model->clear();
            break;
        }
        default:
            break;
    }
}

void QxTdChatListModel::updateChatReadInbox(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QxTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateChatReadInbox(data);
        emit contentsChanged();
    }
}

void QxTdChatListModel::updateChatReadOutbox(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QxTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateChatReadOutbox(data);
        emit contentsChanged();
    }
}

void QxTdChatListModel::handleUpdateChatPhoto(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QxTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateChatPhoto(data["photo"].toObject());
        emit contentsChanged();
    }
}

void QxTdChatListModel::handleUpdateChatReplyMarkup(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QxTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateChatReplyMarkup(data);
        emit contentsChanged();
    }
}

void QxTdChatListModel::handleUpdateChatDraftMessage(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QxTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateChatDraftMessage(data["draft_message"].toObject());
        tdchat->updateChatPositions(data);
        emit contentsChanged();
    }
}

void QxTdChatListModel::handleUpdateChatTitle(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QxTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateChatTitle(data);
        emit contentsChanged();
    }
}

void QxTdChatListModel::handleUpdateChatUnreadMentionCount(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QxTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateChatUnreadMentionCount(data);
        emit contentsChanged();
    }
}

void QxTdChatListModel::handleUpdateChatNotificationSettings(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QxTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateChatNotificationSettings(data);
        emit contentsChanged();
    }
}

void QxTdChatListModel::handleUpdateChatOnlineMemberCount(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QxTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateChatOnlineMemberCount(data);
        emit contentsChanged();
    }
}

void QxTdChatListModel::sendForwardMessage(const QStringList &forwardMessageIds,
                                          const qint64 &recievingChatId,
                                          const qint64 &fromChatId,
                                          const QString &message)
{

    QString plainText;
    QJsonArray formatEntities = QxTdHelpers::formatPlainTextMessage(message, plainText);
    QxTdInputMessageText *messageText = new QxTdInputMessageText();
    messageText->setText(message);
    messageText->setEntities(formatEntities);
    std::unique_ptr<QxTdForwardMessagesRequest> request(new QxTdForwardMessagesRequest);
    request->setChatId(recievingChatId);
    request->setFromChatId(fromChatId);
    std::unique_ptr<QxTdSendMessageRequest> additionalTextMessagerequest(new QxTdSendMessageRequest);
    additionalTextMessagerequest->setChatId(recievingChatId);
    additionalTextMessagerequest->setContent(messageText);
    QList<qint64> forwardingMessageIntIds;
    foreach (QString msgId, forwardMessageIds) {
        forwardingMessageIntIds.append(msgId.toLongLong());
    }
    request->setMessageIds(forwardingMessageIntIds);
    QxTdClient::instance()->send(request.get());
    if (message != "") {
        QxTdClient::instance()->send(additionalTextMessagerequest.get());
    }
}

void QxTdChatListModel::togglePinChat(const qint64 &chatId, const bool &pinned)
{
    qlonglong maxPinnableChats = QxTdClient::instance()->getOption("pinned_chat_count_max").toLongLong();
    if (pinned && m_pinnedChats.size() == maxPinnableChats) {
        emit showNotification(qxTranslate("Maximum number of pinned chat exceeded"));
        return;
    }
    // Copy the internal list as we will wait for the updateChatPosition events
    // to update m_pinnedChats. This prevents us from prematurely updating and
    // having to handle errors when updating the pinned chats list.
    QList<qint64> chats;
    for (int i = 0; i < m_pinnedChats.size(); ++i) {
        chats.append(m_pinnedChats.at(i).id());
    }

    if (pinned && !chats.contains(chatId)) {
        chats.prepend(chatId);
    } else if (!pinned && chats.contains(chatId)) {
        chats.removeAll(chatId);
    }
    std::unique_ptr<QxTdSetPinnedChatsRequest> req(new QxTdSetPinnedChatsRequest);
    req->setPinnedChats(chats);
    QxTdClient::instance()->send(req.get());
}

void QxTdChatListModel::handleForwardingMessagesAction()
{
    setListMode(ListMode::ForwardingMessages);
}

QxTdChatListModel::ListMode QxTdChatListModel::listMode() const
{
    return m_listMode;
}

void QxTdChatListModel::setListMode(ListMode listMode)
{
    m_listMode = listMode;
    emit listModeChanged();
}

void QxTdChatListModel::requestPositionInfo()
{
    if (!m_positionInfoSource) {
        m_positionInfoSource = QGeoPositionInfoSource::createDefaultSource(this);
        if (!m_positionInfoSource) {
            qWarning() << "Could not initialize position info source!";
            return;
        }
    }
    connect(m_positionInfoSource, &QGeoPositionInfoSource::positionUpdated,
            this, &QxTdChatListModel::positionUpdated);
    m_positionInfoSource->requestUpdate(180000);
    m_positionWaitTimer->start();
}

void QxTdChatListModel::cancelPositionInfo()
{
    disconnect(m_positionInfoSource, &QGeoPositionInfoSource::positionUpdated,
               this, &QxTdChatListModel::positionUpdated);
    m_positionWaitTimer->stop();
}

void QxTdChatListModel::onPositionInfoTimeout()
{
    cancelPositionInfo();
    emit positionInfoTimeout();
}

void QxTdChatListModel::positionUpdated(const QGeoPositionInfo &positionInfo)
{
    cancelPositionInfo();
    emit positionInfoReceived(positionInfo.coordinate().latitude(), positionInfo.coordinate().longitude());
}

void QxTdChatListModel::setChatDraftMessage(const QString &draftText,
                                           const qint64 &replyToMessageId,
                                           const qint64 &chatId)
{
    std::unique_ptr<QxTdInputMessageText> messageText(new QxTdInputMessageText);
    messageText->setText(draftText);
    messageText->setClearDraft(false);
    std::unique_ptr<QxTdDraftMessage> draftMessage(new QxTdDraftMessage);
    draftMessage->setInputMessageText(messageText.release());
    draftMessage->setReplyToMessageId(replyToMessageId);
    std::unique_ptr<QxTdSetChatDraftRequest> request(new QxTdSetChatDraftRequest);
    request->setChatId(chatId);
    request->setDraftMessage(draftMessage.release());
    QxTdClient::instance()->send(request.get());
}

void QxTdChatListModel::joinChat(const qint64 &chatId) const
{
    std::unique_ptr<QxTdJoinChatRequest> req(new QxTdJoinChatRequest);
    req->setChatId(chatId);
    QFuture<QxTdResponse> resp = req->sendAsync();
    qxAwait(resp);
    qDebug() << resp.result().json();
    if (resp.result().isError()) {
        qWarning() << "Error during chat joining:" << resp.result().errorString();
    }
}

void QxTdChatListModel::setChatToOpenOnUpdate(const qint64 &chatId)
{
    m_chatToOpenOnUpdate = chatId;
}

void QxTdChatListModel::loadMoreChats(const QString &chatList) {
    std::unique_ptr<QxTdLoadChatsRequest> req(new QxTdLoadChatsRequest);

    if (m_model->isEmpty()) {
        req->setChatList(chatList);
    }
    req->setLimit(10);
    req->sendAsync();
}

void QxTdChatListModel::checkChatInviteLink(const QString &inviteLink)
{
    std::unique_ptr<QxTdCheckChatInviteLinkRequest> req(new QxTdCheckChatInviteLinkRequest);
    req->setInviteLink(inviteLink);
    QFuture<QxTdResponse> resp = req->sendAsync();
    qxAwait(resp);
    if (resp.result().isError()) {
        qWarning() << "Error during checking invite link:" << resp.result().errorString();
    }
    QPointer<QxTdChatInviteLinkInfo> info(new QxTdChatInviteLinkInfo);
    QJsonObject json = resp.result().json();
    info->unmarshalJson(json);
    if (info->chatId() != 0) {
        setCurrentChatById(info->chatId());
    } else {
        emit showChatInviteLinkInfo(info, inviteLink);
    }
}

void QxTdChatListModel::joinChatByInviteLink(const QString &inviteLink)
{
    qDebug() << inviteLink;
    std::unique_ptr<QxTdJoinChatByInviteLinkRequest> req(new QxTdJoinChatByInviteLinkRequest);
    req->setInviteLink(inviteLink);
    QFuture<QxTdResponse> resp = req->sendAsync();
    qxAwait(resp);
    qDebug() << resp.result().json();
    if (resp.result().isError()) {
        qWarning() << "Error during joining chat by invite link:" << resp.result().errorString();
    }
    std::unique_ptr<QxTdChat> chat(new QxTdChat);
    QJsonObject json = resp.result().json();
    chat->unmarshalJson(json);
    setChatToOpenOnUpdate(chat->id());
    setCurrentChatById(chat->id());
}

void QxTdChatListModel::openMessageContent(const QString chatId, const QString messageId)
{
    std::unique_ptr<QxTdOpenMessageContentRequest> req(new QxTdOpenMessageContentRequest);
    req->setChatId(chatId);
    req->setMessageId(messageId);
    QFuture<QxTdResponse> resp = req->sendAsync();
}

void QxTdChatListModel::sendSetTTL(const QString &chatId, const int &ttl)
{
    std::unique_ptr<QxTdSetChatMessageTtlRequest> req(new QxTdSetChatMessageTtlRequest);
    req->setChatId(chatId.toLong());
    req->setTTL(ttl);
    QxTdClient::instance()->send(req.get());
}

/**
 * @brief Set the answer (chosen option(s)) for a poll 
 */
void QxTdChatListModel::setPollAnswer(const QString &chatId, const QString &messageId, const QVariantList &optionIds) {
    std::unique_ptr<QxTdSetPollAnswerRequest> req(new QxTdSetPollAnswerRequest);
    QList<qint32> targetList;
    foreach(QVariant v, optionIds) {
        targetList << v.value<qint32>();
    }
    req->setChatId(chatId.toLong());
    req->setMessageId(messageId.toLong());
    req->setPollOptions(targetList);
    QxTdClient::instance()->send(req.get());
}
