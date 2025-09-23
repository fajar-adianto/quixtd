#include "qx_td_super_group_chat.h"
#include <QDateTime>
#include "chat/requests/qx_td_get_super_group_request.h"
#include "chat/requests/qx_td_get_super_group_full_info_request.h"
#include "client/qx_td_client.h"
#include "common/qx_td_object.h"
#include "utils/qx_td_await.h"

QxTdSuperGroupChat::QxTdSuperGroupChat(QObject *parent)
    : QxTdChat(parent)
    , m_sgId(0)
    , m_date(0)
    , m_status(nullptr)
    , m_memberCount(0)
    , m_signMessages(false)
    , m_isChannel(false)
    , m_isVerified(false)
    , m_adminCount(0)
    , m_restrictedCount(0)
    , m_bannedCount(0)
    , m_canGetMembers(false)
    , m_canSetUsername(false)
    , m_canSetStickerSet(false)
    , m_historyAvailable(false)
    , m_stickerSet(0)
    , m_pinnedMessageId(0)
    , m_upgradeGroupId(0)
    , m_upgradeMaxMsgId(0)
{
    connect(QxTdClient::instance(), &QxTdClient::superGroup, this, &QxTdSuperGroupChat::updateSuperGroup);
    connect(QxTdClient::instance(), &QxTdClient::updateSuperGroup, this, &QxTdSuperGroupChat::updateSuperGroup);
    connect(QxTdClient::instance(), &QxTdClient::updateSupergroupFullInfo, this, &QxTdSuperGroupChat::updateSuperGroupFullInfo);
}

QString QxTdSuperGroupChat::qmlSuperGroupId() const
{
    return m_sgId.toQmlValue();
}

qint64 QxTdSuperGroupChat::superGroupId() const
{
    return m_sgId.value();
}

QString QxTdSuperGroupChat::userName() const
{
    return m_userNames->editableUsername();
}

QDateTime QxTdSuperGroupChat::qmlDate() const
{
    return QDateTime::fromSecsSinceEpoch(m_date);
}

qint32 QxTdSuperGroupChat::date() const
{
    return m_date;
}

QxTdChatMemberStatus *QxTdSuperGroupChat::status() const
{
    return m_status.get();
}

QString QxTdSuperGroupChat::qmlMemberCount() const
{
    return m_memberCount.toQmlValue();
}

qint32 QxTdSuperGroupChat::memberCount() const
{
    return m_memberCount.value();
}

bool QxTdSuperGroupChat::signMessages() const
{
    return m_signMessages;
}

bool QxTdSuperGroupChat::isChannel() const
{
    return m_isChannel;
}

bool QxTdSuperGroupChat::isVerified() const
{
    return m_isVerified;
}

bool QxTdSuperGroupChat::isWritable() const
{
    auto statusType = m_status->type();
    switch (statusType) {
        case QxTdObject::Type::CHAT_MEMBER_STATUS_ADMIN: {
            if (m_isChannel) {
                auto adminStatus = qobject_cast<QxTdChatMemberStatusAdministrator *>(m_status.get());
                if (adminStatus->rights())
                    return adminStatus->rights()->canPostMessages();
                else
                    return false;
            }
            return true;
        }
        case QxTdObject::Type::CHAT_MEMBER_STATUS_CREATOR: {
            auto creatorStatus = qobject_cast<QxTdChatMemberStatusCreator *>(m_status.get());
            return creatorStatus->isMember();
        }
        case QxTdObject::Type::CHAT_MEMBER_STATUS_BANNED:
        case QxTdObject::Type::CHAT_MEMBER_STATUS_LEFT: {
            return false;
        }
        case QxTdObject::Type::CHAT_MEMBER_STATUS_MEMBER: {
            return !m_isChannel;
        }
        case QxTdObject::Type::CHAT_MEMBER_STATUS_RESTRICTED: {
            auto restrictedStatus = qobject_cast<QxTdChatMemberStatusRestricted *>(m_status.get());
            if (restrictedStatus->permissions()) {
                return restrictedStatus->isMember() && restrictedStatus->permissions()->canSendMessages();
            }
            return false;
        }
        default:
            return false;
    }
}

QString QxTdSuperGroupChat::restrictionReason() const
{
    return m_restrictionReason;
}

QString QxTdSuperGroupChat::description() const
{
    return m_description;
}

QString QxTdSuperGroupChat::qmlAdminCount() const
{
    return m_adminCount.toQmlValue();
}

qint32 QxTdSuperGroupChat::adminCount() const
{
    return m_adminCount.value();
}

QString QxTdSuperGroupChat::qmlRestrictedCount() const
{
    return m_restrictedCount.toQmlValue();
}

qint32 QxTdSuperGroupChat::restrictedCount() const
{
    return m_restrictedCount.value();
}

QString QxTdSuperGroupChat::qmlBannedCount() const
{
    return m_bannedCount.toQmlValue();
}

qint32 QxTdSuperGroupChat::bannedCount() const
{
    return m_bannedCount.value();
}

bool QxTdSuperGroupChat::isHistoryAvailable() const
{
    return m_historyAvailable;
}

QString QxTdSuperGroupChat::qmlStickerSetId() const
{
    return m_stickerSet.toQmlValue();
}

qint64 QxTdSuperGroupChat::stickerSetId() const
{
    return m_stickerSet.value();
}

QString QxTdSuperGroupChat::inviteLink() const
{
    return m_inviteLink;
}

QString QxTdSuperGroupChat::qmlPinnedMessageId() const
{
    return m_pinnedMessageId.toQmlValue();
}

qint64 QxTdSuperGroupChat::pinnedMessageId() const
{
    return m_pinnedMessageId.value();
}

QString QxTdSuperGroupChat::qmlUpgradedFromBasicGroupId() const
{
    return m_upgradeGroupId.toQmlValue();
}

qint64 QxTdSuperGroupChat::upgradedFromBasicGroupId() const
{
    return m_upgradeGroupId.value();
}

QString QxTdSuperGroupChat::qmlUpgradedFromMaxMessageId() const
{
    return m_upgradeMaxMsgId.toQmlValue();
}

qint64 QxTdSuperGroupChat::upgradedFromMaxMessageId() const
{
    return m_upgradeMaxMsgId.value();
}

void QxTdSuperGroupChat::onChatDeserialized()
{
    getSuperGroupData();
}

void QxTdSuperGroupChat::parseSuperGroupId() {
    QxTdChatTypeSuperGroup *group = qobject_cast<QxTdChatTypeSuperGroup *>(chatType());
    if (group && group->superGroupId() > 0) {
        m_sgId = group->superGroupId();
    }
}
void QxTdSuperGroupChat::getSuperGroupFullInfo()
{
    if (m_sgId.value() == 0) {
        parseSuperGroupId();
    }
    std::unique_ptr<QxTdGetSuperGroupFullInfoRequest> req(new QxTdGetSuperGroupFullInfoRequest);
    req->setSupergroupId(superGroupId());
    QFuture<QxTdResponse> resp = req->sendAsync();
    qxAwait(resp);
    if (resp.result().isError()) {
        qWarning() << "Error during fetching supergroup full info:" << resp.result().errorString();
        return;
    }
    superGroupFullInfo(resp.result().json());
}

void QxTdSuperGroupChat::getSuperGroupData()
{
    if (m_sgId.value() == 0) {
        parseSuperGroupId();
    }
    std::unique_ptr<QxTdGetSuperGroupRequest> req(new QxTdGetSuperGroupRequest);
    req->setSuperGroupId(superGroupId());
    QxTdClient::instance()->send(req.get());
}

void QxTdSuperGroupChat::updateSuperGroup(const QJsonObject &json)
{
    const qint64 gid = json["id"].toVariant().toLongLong();
    if (gid != superGroupId()) {
        return;
    }

    const QJsonObject status = json["status"].toObject();
    m_status.reset(QxTdChatMemberStatusFactory::create(status, this));

    m_signMessages = json["sign_messages"].toBool();
    m_isChannel = json["is_channel"].toBool();
    m_isVerified = json["is_verified"].toBool();
    m_restrictionReason = json["restriction_reason"].toString();
    m_userNames.reset(new QxTdUsernames(this));
    m_userNames->unmarshalJson(json["usernames"].toObject());
    emit isWritableChanged();
    emit superGroupChanged();
    emit chatStatusChanged();
    getSuperGroupFullInfo();
}

void QxTdSuperGroupChat::updateSuperGroupFullInfo(const QJsonObject &json)
{
    const qint64 sid = json["supergroup_id"].toVariant().toLongLong();
    if (sid != superGroupId()) {
        return;
    }
    const QJsonObject info = json["supergroup_full_info"].toObject();
    superGroupFullInfo(info);
}

void QxTdSuperGroupChat::superGroupFullInfo(const QJsonObject &info)
{
    m_description = info["description"].toString();
    m_memberCount = info["member_count"];
    m_adminCount = info["administrator_count"];
    m_restrictedCount = info["restricted_count"];
    m_bannedCount = info["banned_count"];
    m_canGetMembers = info["can_get_members"].toBool();
    m_canSetUsername = info["can_set_username"].toBool();
    m_canSetStickerSet = info["can_set_sticker_set"].toBool();
    m_historyAvailable = info["is_all_history_available"].toBool();
    m_stickerSet = info["sticker_set_id"];
    m_inviteLink = info["invite_link"].toString();
    m_upgradeGroupId = info["upgraded_from_basic_group_id"];
    m_upgradeMaxMsgId = info["upgraded_from_max_message_id"];
    emit superGroupInfoChanged();
}
