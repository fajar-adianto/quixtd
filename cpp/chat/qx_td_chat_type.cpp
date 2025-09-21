#include "chat/qx_td_chat_type.h"
#include "client/qx_td_client.h"
#include "user/qx_td_users.h"
#include "qx_td_chat_type.h"

QxTdChatType::QxTdChatType(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

QxTdChatTypeBasicGroup::QxTdChatTypeBasicGroup(QObject *parent)
    : QxTdChatType(parent)
    , m_groupId(0)
{
    setType(CHAT_TYPE_BASIC_GROUP);
}

QString QxTdChatTypeBasicGroup::qmlBasicGroupId() const
{
    return m_groupId.toQmlValue();
}

qint64 QxTdChatTypeBasicGroup::basicGroupId() const
{
    return m_groupId.value();
}

void QxTdChatTypeBasicGroup::unmarshalJson(const QJsonObject &json)
{
    QxTdChatType::unmarshalJson(json);
    m_groupId = json["basic_group_id"];
    emit groupIdChanged();
}

QxTdChatTypePrivate::QxTdChatTypePrivate(QObject *parent)
    : QxTdChatType(parent)
    , m_userId(0)
    , m_waitingForUser(false)
{
    setType(CHAT_TYPE_PRIVATE);
}

QString QxTdChatTypePrivate::qmlUserId() const
{
    return m_userId.toQmlValue();
}

qint64 QxTdChatTypePrivate::userId() const
{
    return m_userId.value();
}

QxTdUser *QxTdChatTypePrivate::user() const
{
    return m_user;
}

void QxTdChatTypePrivate::unmarshalJson(const QJsonObject &json)
{
    QxTdChatType::unmarshalJson(json);
    m_userId = json["user_id"].toVariant().toLongLong();
    emit userIdChanged();
    updateUser(m_userId.value());
}

void QxTdChatTypePrivate::updateUser(const qint64 &userId)
{
    if (userId != m_userId.value()) {
        return;
    }
    if (m_user) {
        m_user = nullptr;
    }

    auto *users = QxTdUsers::instance()->model();
    m_user = users->getByUid(QString::number(userId));
    if (m_user) {
        emit userChanged();
        if (m_waitingForUser) {
            disconnect(QxTdUsers::instance(), &QxTdUsers::userCreated, this, &QxTdChatTypePrivate::updateUser);
            m_waitingForUser = false;
        }
        return;
    }
    connect(QxTdUsers::instance(), &QxTdUsers::userCreated, this, &QxTdChatTypePrivate::updateUser);
    QxTdClient::instance()->send(QJsonObject{
            { "@type", "getUser" },
            { "user_id", m_userId.value() } });
    m_waitingForUser = true;
}

QxTdChatTypeSecret::QxTdChatTypeSecret(QObject *parent)
    : QxTdChatTypePrivate(parent)
    , m_chatId(0)
{
    setType(CHAT_TYPE_SECRET);
}

QString QxTdChatTypeSecret::qmlSecretChatId() const
{
    return m_chatId.toQmlValue();
}

qint64 QxTdChatTypeSecret::secretChatId() const
{
    return m_chatId.value();
}

void QxTdChatTypeSecret::unmarshalJson(const QJsonObject &json)
{
    QxTdChatTypePrivate::unmarshalJson(json);
    m_chatId = json["secret_chat_id"].toVariant().toLongLong();
    emit secretChatIdChanged();
}

QxTdChatTypeSuperGroup::QxTdChatTypeSuperGroup(QObject *parent)
    : QxTdChatType(parent)
    , m_groupId(0)
    , m_isChannel(false)
{
    setType(CHAT_TYPE_SUPERGROUP);
}

QString QxTdChatTypeSuperGroup::qmlSuperGroupId() const
{
    return m_groupId.toQmlValue();
}

qint64 QxTdChatTypeSuperGroup::superGroupId() const
{
    return m_groupId.value();
}

bool QxTdChatTypeSuperGroup::isChannel() const
{
    return m_isChannel;
}

void QxTdChatTypeSuperGroup::unmarshalJson(const QJsonObject &json)
{
    QxTdChatType::unmarshalJson(json);
    m_groupId = json["supergroup_id"];
    emit superGroupIdChanged();
    m_isChannel = json["is_channel"].toBool();
    emit isChannelChanged();
}
