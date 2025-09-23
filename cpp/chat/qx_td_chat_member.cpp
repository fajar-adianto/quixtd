#include "qx_td_chat_member.h"

QxTdChatMember::QxTdChatMember(QObject *parent)
    : QxTdObject(parent)
    , m_inviteUserId(0)
    , m_joinedChatDate(0)
    , m_status(nullptr)
{
    setType(CHAT_MEMBER);
}

QxTdMessageSender *QxTdChatMember::memberId() const
{
    return m_memberId.get();
}

QString QxTdChatMember::qmlInviteUserId() const
{
    return m_inviteUserId.toQmlValue();
}

qint64 QxTdChatMember::inviteUserId() const
{
    return m_inviteUserId.value();
}

QDateTime QxTdChatMember::qmlJoinedChatDate() const
{
    return QDateTime::fromSecsSinceEpoch(m_joinedChatDate.value());
}

qint32 QxTdChatMember::joinedChatDate() const
{
    return m_joinedChatDate.value();
}

QxTdChatMemberStatus *QxTdChatMember::status() const
{
    return m_status.get();
}

void QxTdChatMember::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_memberId.reset(QxTdMessageSenderFactory::create(json["member_id"].toObject(), this));
    m_inviteUserId = json["inviter_user_id"].toVariant().toLongLong();
    m_joinedChatDate = json["joined_chat_date"];
    m_status.reset(QxTdChatMemberStatusFactory::create(json["status"].toObject(), this));

    emit chatMemberChanged();
}
