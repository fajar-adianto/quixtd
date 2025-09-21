#include "qx_td_message.h"
#include <QDebug>
#include "client/qx_td_client.h"
#include "user/qx_td_users.h"
#include "qx_td_message_content_factory.h"
#include "content/qx_td_message_call.h"
#include "content/qx_td_message_text.h"
#include "content/qx_td_message_date.h"
#include "content/qx_td_message_unread_label.h"
#include "content/qx_td_message_sticker.h"
#include "content/qx_td_message_document.h"
#include "content/qx_td_message_location.h"
#include "content/qx_td_message_custom_service_action.h"
#include "content/qx_td_message_chat_delete_member.h"
#include "content/qx_td_message_chat_add_members.h"
#include "common/qx_td_helpers.h"
#include "requests/qx_td_get_message_request.h"
#include "user/requests/qx_td_get_user_request.h"
#include "chat/requests/qx_td_get_chat_request.h"
#include "chat/qx_td_chat.h"
#include "utils/qx_td_await.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessage::QxTdMessage(QObject *parent)
    : QxAbstractInt64Id(parent)
    , m_date(0)
    , m_chatId(0)
    , m_sender(nullptr)
    , m_sendingState(nullptr)
    , m_schedulingState(nullptr)
    , m_isOutgoing(false)
    , m_canBeEdited(false)
    , m_canBeForwarded(false)
    , m_canBeDeletedOnlyForSelf(false)
    , m_canBeDeletedForAllUsers(false)
    , m_isChannelPost(false)
    , m_containsUnreadMention(false)
    , m_content(nullptr)
    , m_isValid(false)
    , m_previousSender(nullptr)
    , m_nextSender(nullptr)
    , m_replyMarkup(nullptr)
    , m_forwardInfo(nullptr)
    , m_interactionInfo(nullptr)
    , m_messageRepliedTo(nullptr)
    , m_replyToMessageId(0)
    , m_isCollapsed(false)
{
    setType(MESSAGE);
}

QDateTime QxTdMessage::qmlDate() const
{
    return QDateTime::fromSecsSinceEpoch(m_date);
}

qint32 QxTdMessage::date() const
{
    return m_date;
}

QDateTime QxTdMessage::qmlEditDate() const
{
    return QDateTime::fromSecsSinceEpoch(m_editDate);
}

qint32 QxTdMessage::editDate() const
{
    return m_editDate;
}

QString QxTdMessage::qmlChatId() const
{
    return m_chatId.toQmlValue();
}

qint64 QxTdMessage::chatId() const
{
    return m_chatId.value();
}

QxTdMessageSender *QxTdMessage::sender() const
{
    return m_sender.data();
}

void QxTdMessage::unmarshalJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    QxAbstractInt64Id::unmarshalJson(json);

    // This is a special case to insert a date and unread labels into the
    // model so messages can be grouped by day and by read-state. No data
    // beyond so we just return early.
    if (json.keys().contains("dateLabel")) {
        auto *md = new QxTdMessageDate(this);
        md->setDate(json["dateLabel"].toInt());
        m_content.reset(md);
        return;
    }
    if (json.keys().contains("unreadLabel")) {
        auto *md = new QxTdMessageUnreadLabel(this);
        md->setLabel(json["unreadLabel"].toString());
        m_content.reset(md);
        return;
    }

    m_isValid = false;
    m_date = qint32(json["date"].toInt());
    m_editDate = qint32(json["edit_date"].toInt());
    m_isEdited = m_editDate > 0;
    const QJsonObject sender = json["sender_id"].toObject();
    m_sender.reset(QxTdMessageSenderFactory::create(sender, this));

    m_chatId = json["chat_id"].toVariant().toLongLong();

    updateSendingState(json);
    
    updateSchedulingState(json);
    
    m_isOutgoing = json["is_outgoing"].toBool();

    m_canBeEdited = json["can_be_edited"].toBool();
    m_canBeForwarded = json["can_be_forwarded"].toBool();
    m_canBeDeletedOnlyForSelf = json["can_be_deleted_only_for_self"].toBool();
    m_canBeDeletedForAllUsers = json["can_be_deleted_for_all_users"].toBool();
    m_canGetStatistics = json["can_get_statistics"].toBool();
    m_canGetMessageThread = json["can_get_message_thread"].toBool();
    m_canGetViewers = json["can_get_viewers"].toBool();
    m_canGetMediaTimestampLinks = json["can_get_media_timestamp_links"].toBool();
    m_hasTimestampedMedia = json["has_timestamped_media"].toBool();
    m_isChannelPost = json["is_channel_post"].toBool();
    m_containsUnreadMention = json["contains_unread_mention"].toBool();
    m_replyToMessageId = json["reply_to_message_id"];
    if (isReply() && !isCollapsed()) {
        if (m_messageRepliedTo == nullptr) {
            connect(QxTdClient::instance(), &QxTdClient::message, this, &QxTdMessage::handleMessage);
        }
        QScopedPointer<QxTdGetMessageRequest> request(new QxTdGetMessageRequest);
        request->setChatId(chatId());
        request->setMessageId(replyToMessageId());
        QxTdClient::instance()->send(request.data());
    }

    const QJsonObject content = json["content"].toObject();
    m_content.reset(QxTdMessageContentFactory::create(content, this));
    m_content->unmarshalJson(content);
    switch (m_content->type()) {
    case QxTdObject::MESSAGE_CALL: {
        auto *c = qobject_cast<QxTdMessageCall *>(m_content.data());
        c->setOutgoing(m_isOutgoing);
        break;
    }
    case QxTdObject::MESSAGE_CHAT_ADD_MEMBERS: {
        auto *c = qobject_cast<QxTdMessageChatAddMembers *>(m_content.data());
        c->setSenderUserId(m_sender->id());
        break;
    }
    case QxTdObject::MESSAGE_CHAT_DELETE_MEMBER: {
        auto *c = qobject_cast<QxTdMessageChatDeleteMember *>(m_content.data());
        c->setSenderUserId(m_sender->id());
        break;
    }
    default:
        break;
    }

    const QJsonObject replyMarkup = json["reply_markup"].toObject();
    if (!replyMarkup.isEmpty()) {
        m_replyMarkup.reset(QxTdReplyMarkupFactory::create(replyMarkup, this));
    } else {
        m_replyMarkup.reset();
    }

    m_interactionInfo.reset(new QxTdMessageInteractionInfo(this));
    const QJsonObject interactionInfo = json["interaction_info"].toObject();
    if (!interactionInfo.isEmpty()) {
        m_interactionInfo->unmarshalJson(interactionInfo);
    }

    qint64 forwardedFromId = 0;
    const QJsonObject forwardInfo = json["forward_info"].toObject();
    if (!forwardInfo.isEmpty()) {
        m_forwardInfo.reset(new QxTdMessageForwardInfo(this));
        m_forwardInfo->unmarshalJson(forwardInfo);
    }
    m_ttl = json["ttl"].toInt();
    m_isValid = true;
    emit messageChanged();
}

void QxTdMessage::unmarshalUpdateContent(const QJsonObject &content)
{
    if (content.isEmpty()) {
        m_content.reset();
                qWarning() << "Empty updated message content";
        return;
    }

    m_isValid = false;
    m_content.reset(QxTdMessageContentFactory::create(content, this));
    m_content->unmarshalJson(content);

    emit messageChanged();
    m_isValid = true;
}

QxTdMessageSendingState *QxTdMessage::sendingState() const
{
    return m_sendingState.data();
}

QxTdMessageSchedulingState *QxTdMessage::schedulingState() const
{
    return m_schedulingState.data();
}

bool QxTdMessage::isOutgoing() const
{
    return m_isOutgoing && !m_isChannelPost;
}

bool QxTdMessage::isPinned() const
{
    return m_isPinned;
}

bool QxTdMessage::isEdited() const
{
    return m_isEdited;
}

void QxTdMessage::setIsEdited(const bool value)
{
    m_isEdited = value;
    emit messageChanged();
}

bool QxTdMessage::canBeEdited() const
{
    return m_canBeEdited;
}

bool QxTdMessage::canBeForwarded() const
{
    return m_canBeForwarded;
}

bool QxTdMessage::canBeSaved() const
{
    return m_canBeSaved;
}

bool QxTdMessage::canBeDeletedOnlyForSelf() const
{
    return m_canBeDeletedOnlyForSelf;
}

bool QxTdMessage::canBeDeletedForAllUsers() const
{
    return m_canBeDeletedForAllUsers;
}

bool QxTdMessage::canGetStatistics() const
{
    return m_canGetStatistics;
}

bool QxTdMessage::canGetMessageThread() const
{
    return m_canGetMessageThread;
}

bool QxTdMessage::canGetViewers() const
{
    return m_canGetViewers;
}

bool QxTdMessage::canGetMediaTimestampLinks() const
{
    return m_canGetMediaTimestampLinks;
}

bool QxTdMessage::hasTimestampedMedia() const
{
    return m_hasTimestampedMedia;
}

bool QxTdMessage::isChannelPost() const
{
    return m_isChannelPost;
}

qint32 QxTdMessage::ttl() const
{
    return m_ttl;
}

QString QxTdMessage::views() const
{
    if (!m_interactionInfo) {
        return "";
    }

    qint32 viewCount = m_interactionInfo->viewCount();

    if (viewCount > 9999 && viewCount <= 999999) {
        return QString("%1K").arg(((double)(viewCount / 100)) / 10, 0, 'd', 1);
    } else if (viewCount > 999999) {
        return QString("%1M").arg(((double)(viewCount / 100000)) / 10, 0, 'd', 1);
    } else if (viewCount > 0) {
        return QString("%1").arg(viewCount);
    }
    return "";
}

bool QxTdMessage::containsUnreadMention() const
{
    return m_containsUnreadMention;
}

QxTdMessageContent *QxTdMessage::content() const
{
    return m_content.data();
}

QxTdReplyMarkup *QxTdMessage::replyMarkup() const
{
    return m_replyMarkup.data();
}

QxTdMessageForwardInfo *QxTdMessage::forwardInfo() const
{
    return m_forwardInfo.data();
}

QxTdMessageInteractionInfo *QxTdMessage::interactionInfo() const
{
    return m_interactionInfo.data();
}

bool QxTdMessage::isForwarded() const
{
    return m_forwardInfo != nullptr;
}

QString QxTdMessage::summary() const
{
    QString content;
    if (!m_content.isNull())
    {
        if (m_content->typeText() != "") {
            content = QString("%1 %2").arg(m_content->typeText(), m_content->infoText());
        } else {
            content = m_content->infoText();
        }
    }
    return content;
}

QString QxTdMessage::formatDate(const QDateTime &dt)
{
    return QxTdHelpers::formatDate(dt);
}

bool QxTdMessage::isValid() const
{
    return m_isValid;
}

bool QxTdMessage::sameSenderAsPreviousMessage() const
{
    return !m_previousSender.isNull() && m_sender->type() == m_previousSender->type() && m_sender->id() == m_previousSender->id();
}

void QxTdMessage::setPreviousSender(QxTdMessageSender *sender)
{
    m_previousSender = sender;
    emit previousSenderChanged();
}

bool QxTdMessage::sameSenderAsNextMessage() const
{
    return !m_nextSender.isNull() && m_sender->type() == m_nextSender->type() && m_sender->id() == m_nextSender->id();
}

void QxTdMessage::setNextSender(QxTdMessageSender *sender)
{
    m_nextSender = sender;
    emit nextSenderChanged();
}

bool QxTdMessage::isLatest() const
{
    // Only the latest message should not have a nextSender
    return m_nextSender.isNull();
}

qint64 QxTdMessage::replyToMessageId() const
{
    return m_replyToMessageId.value();
}

QString QxTdMessage::qmlReplyToMessageId() const
{
    return m_replyToMessageId.toQmlValue();
}

qint64 QxTdMessage::messageThreadId() const
{
    return m_messageThreadId.value();
}

QString QxTdMessage::qmlMessageThreadId() const
{
    return m_messageThreadId.toQmlValue();
}

void QxTdMessage::updateSchedulingState(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    QxTdMessageSchedulingState *obj = nullptr;
    if (json.contains("scheduling_state")) {
        const QString type  = json["scheduling_state"].toObject()["@type"].toString();
        if (type == "messageSchedulingStateSendAtDate") {
            obj = new QxTdMessageSchedulingStateSendAtDate(this);
        } else if (type == "messageSchedulingStateSendWhenOnline") {
            obj = new QxTdMessageSchedulingStateSendWhenOnline(this);
        } else {
            qWarning() << "Unknown message scheduling state: " << type;
        }
    }
    m_schedulingState.reset(obj);
}

void QxTdMessage::updateSendingState(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    QxTdMessageSendingState *obj = nullptr;
    if (json.contains("sending_state")) {
        const QString type  = json["sending_state"].toObject()["@type"].toString();
        if (type == "messageSendingStatePending") {
            obj = new QxTdMessageSendingStatePending(this);
        } else if (type == "messageSendingStateFailed") {
            obj = new QxTdMessageSendingStateFailed(this);
        } else {
            qWarning() << "Unknown message sending state: " << type;
        }
    }
    m_sendingState.reset(obj);
    emit sendingStateChanged();
}

bool QxTdMessage::isReply() const
{
    return (m_replyToMessageId.value() > 0);
}

QxTdMessage *QxTdMessage::messageRepliedTo()
{
    if (replyToMessageId() <= 0) {
        return nullptr;
    }

    if (!m_messageRepliedTo) {
        m_messageRepliedTo = new QxTdMessage();
    }

    return m_messageRepliedTo;
}

void QxTdMessage::handleMessage(const QJsonObject &json)
{
    if (json.isEmpty() || json["id"] != replyToMessageId()) {
        return;
    }

    auto *msgRepliedTo = messageRepliedTo();
    msgRepliedTo->collapse();

    if (!msgRepliedTo) {
        return;
    }

    msgRepliedTo->unmarshalJson(json);
    emit messageRepliedToChanged();
}

bool QxTdMessage::isCollapsed() const
{
    return m_isCollapsed;
}

void QxTdMessage::collapse()
{
    m_isCollapsed = true;
}
