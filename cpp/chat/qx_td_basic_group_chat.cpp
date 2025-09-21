#include "qx_td_basic_group_chat.h"
#include <QDebug>
#include "chat/requests/qx_td_get_basic_group_request.h"
#include "client/qx_td_client.h"

QxTdBasicGroupChat::QxTdBasicGroupChat(QObject *parent)
    : QxTdChat(parent)
    , m_groupId(0)
    , m_memberCount(0)
    , m_status(nullptr)
    , m_isActive(false)
    , m_upgradedSGID(0)
    , m_creatorId(0)
    , m_members(nullptr)
{
    m_members = new QxTdObjectListModel<QxTdChatMember>(this, "", "userId");
    connect(QxTdClient::instance(), &QxTdClient::basicGroup, this, &QxTdBasicGroupChat::updateGroupData);
    connect(QxTdClient::instance(), &QxTdClient::updateBasicGroup, this, &QxTdBasicGroupChat::updateGroupData);
    connect(QxTdClient::instance(), &QxTdClient::updateBasicGroupFullInfo, this, &QxTdBasicGroupChat::updateGroupInfo);
}

QString QxTdBasicGroupChat::qmlGroupId() const
{
    return m_groupId.toQmlValue();
}

qint64 QxTdBasicGroupChat::groupId() const
{
    return m_groupId.value();
}

QString QxTdBasicGroupChat::qmlMemberCount() const
{
    return m_memberCount.toQmlValue();
}

qint32 QxTdBasicGroupChat::memberCount() const
{
    return m_memberCount.value();
}

QxTdChatMemberStatus *QxTdBasicGroupChat::status() const
{
    return m_status.data();
}

bool QxTdBasicGroupChat::isActive() const
{
    return m_isActive;
}

QString QxTdBasicGroupChat::qmlUpgradedToSuperGroupId() const
{
    return m_upgradedSGID.toQmlValue();
}

qint64 QxTdBasicGroupChat::upgradedToSuperGroupId() const
{
    return m_upgradedSGID.value();
}

QString QxTdBasicGroupChat::qmlCreatorUserId() const
{
    return m_creatorId.toQmlValue();
}

qint64 QxTdBasicGroupChat::creatorUserId() const
{
    return m_creatorId.value();
}

QObject *QxTdBasicGroupChat::qmlMembers() const
{
    return m_members;
}

QxTdObjectListModel<QxTdChatMember> *QxTdBasicGroupChat::members() const
{
    return m_members;
}

QString QxTdBasicGroupChat::inviteLink() const
{
    return m_inviteLink;
}

void QxTdBasicGroupChat::unmarshalJson(const QJsonObject &json)
{
    QxTdChat::unmarshalJson(json);
    if (m_status.isNull()) {
        requestGroupData();
    }
}

void QxTdBasicGroupChat::onChatDeserialized()
{
    requestGroupData();
}

void QxTdBasicGroupChat::requestGroupData()
{
    QxTdChatTypeBasicGroup *group = qobject_cast<QxTdChatTypeBasicGroup *>(chatType());
    if (group->basicGroupId() > 0) {
        std::unique_ptr<QxTdGetBasicGroupRequest> req(new QxTdGetBasicGroupRequest);
        req->setGroupId(group->basicGroupId());
        QxTdClient::instance()->send(req.get());
    }
}

void QxTdBasicGroupChat::updateGroupData(const QJsonObject &json)
{
    QxTdChatTypeBasicGroup *group = qobject_cast<QxTdChatTypeBasicGroup *>(chatType());
    const qint64 gid = json["id"].toVariant().toLongLong();
    if (gid != group->basicGroupId()) {
        return;
    }
    m_groupId = gid;
    m_memberCount = json["member_count"];

    const QJsonObject status = json["status"].toObject();
    m_status.reset(QxTdChatMemberStatusFactory::create(status, this));

    m_isActive = json["is_active"].toBool();
    m_upgradedSGID = json["upgraded_to_supergroup_id"];
    emit groupChanged();
    emit chatStatusChanged();
}

void QxTdBasicGroupChat::updateGroupInfo(const QJsonObject &json)
{
    const qint64 gid = json["basic_group_id"].toVariant().toLongLong();
    if (gid != groupId()) {
        return;
    }
    // We always update the full list in one go so clear all
    // the current members
    m_members->clear();

    const QJsonObject info = json["basic_group_full_info"].toObject();
    m_creatorId = info["creator_user_id"].toVariant().toLongLong();
    m_inviteLink = info["invite_link"].toString();

    const QJsonArray members = info["members"].toArray();
    for (const QJsonValue &memberData : members) {
        auto *member = new QxTdChatMember;
        member->unmarshalJson(memberData.toObject());
        m_members->append(member);
    }

    emit groupInfoChanged();
}
