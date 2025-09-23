#include "qx_td_chat_invite_link_info.h"
#include "client/qx_td_client.h"
#include "user/requests/qx_td_get_user_request.h"
#include "utils/qx_td_await.h"
#include "user/qx_td_users.h"
#include "common/qx_td_helpers.h"

#include <QRandomGenerator>

QxTdChatInviteLinkInfo::QxTdChatInviteLinkInfo(QObject *parent)
    : QxTdObject(parent)
    , m_inviteLink("")
    , m_chatId(0)
    , m_type(new QxTdChatType)
    , m_title("")
    , m_photo(new QxTdChatPhoto)
    , m_memberCount(0)
    , m_highlightedMemberCount(0)
    , m_memberUsers(nullptr)
{
    m_memberUsers.reset(new QxTdObjectListModel<QxTdUser>(this));
}

QString QxTdChatInviteLinkInfo::inviteLink() const
{
    return m_inviteLink;
}

qint64 QxTdChatInviteLinkInfo::chatId() const
{
    return m_chatId.value();
}

QString QxTdChatInviteLinkInfo::qmlChatId() const
{
    return m_chatId.toQmlValue();
}

QxTdChatType *QxTdChatInviteLinkInfo::type() const
{
    return m_type.get();
}

QString QxTdChatInviteLinkInfo::title() const
{
    return m_title;
}

QxTdChatPhoto *QxTdChatInviteLinkInfo::photo() const
{
    return m_photo.get();
}

qint32 QxTdChatInviteLinkInfo::memberCount() const
{
    return m_memberCount.value();
}

QString QxTdChatInviteLinkInfo::qmlMemberCount() const
{
    return m_memberCount.toQmlValue();
}

QList<qint64> QxTdChatInviteLinkInfo::memberUserIds() const
{
    return m_memberUserIds;
}
QString QxTdChatInviteLinkInfo::highlightedMemberCount() const
{
    return m_highlightedMemberCount.toQmlValue();
}

QxTdObjectListModel<QxTdUser> *QxTdChatInviteLinkInfo::memberUsers() const
{
    return m_memberUsers.get();
}

bool QxTdChatInviteLinkInfo::isPublic() const
{
    return m_isPublic;
}

QString QxTdChatInviteLinkInfo::initials() const
{
    return m_initials;
}
QString QxTdChatInviteLinkInfo::avatarColor() const
{
    return m_avatarColor;
}

void QxTdChatInviteLinkInfo::unmarshalJson(QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_inviteLink = json["invite_link"].toString();
    m_chatId = json["chat_id"].toVariant().toLongLong();
    m_type->unmarshalJson(json["type"].toObject());
    m_title = json["title"].toString();
    m_photo->unmarshalJson(json["photo"].toObject());
    m_photo->small()->downloadFile();
    m_memberCount = json["member_count"].toInt();

    auto userIds = json["member_user_ids"].toArray();
    for (const QJsonValue &userId : userIds) {
        m_memberUserIds << userId.toVariant().toLongLong();
    }
    for (const qint64 &userId : m_memberUserIds) {
        std::unique_ptr<QxTdUser> user(QxTdUsers::instance()->model()->getByUid(QString::number(userId)));
        if (user == nullptr) {
            std::unique_ptr<QxTdGetUserRequest> req(new QxTdGetUserRequest);
            req->setUserId(userId);
            QFuture<QxTdResponse> resp = req->sendAsync();
            qxAwait(resp);
            if (resp.result().isError()) {
                qWarning() << "Failed to get user with error: " << resp.result().errorString();
                return;
            }
            std::unique_ptr<QxTdUser> reqUser(new QxTdUser);
            reqUser->unmarshalJson(resp.result().json());
            m_memberUsers->append(reqUser.release());
        } else {
            m_memberUsers->append(user.release());
        }
    }
    m_isPublic = json["is_public"].toBool();
    m_initials = QxTdHelpers::initials(m_title);
    m_highlightedMemberCount = m_memberUserIds.count();
    m_avatarColor = QxTdHelpers::avatarColor(QRandomGenerator::global()->generate64());
    emit chatInviteLinkInfoChanged();
}
