#include "qx_td_message_sender_user.h"
#include "client/qx_td_client.h"
#include "user/qx_td_users.h"
#include "utils/debug.h"

QxTdMessageSenderUser::QxTdMessageSenderUser(QObject *parent)
    : QxTdMessageSender(parent)
    , m_user(nullptr)
    , m_waitingForUser(false)
{
    setType(MESSAGE_SENDER_USER);
}

QxTdUser *QxTdMessageSenderUser::user() const
{
    return m_user;
}

void QxTdMessageSenderUser::unmarshalJson(const QJsonObject &json, const QString &id_key)
{
    QxTdMessageSender::unmarshalJson(json, "user_id");
    updateUser(id());
}

void QxTdMessageSenderUser::updateUser(const qint64 &userId)
{
    if (userId != id()) {
        return;
    }
    if (m_user) {
        m_user = nullptr;
    }

    auto *users = QxTdUsers::instance()->model();
    m_user = users->getByUid(QString::number(userId));
    if (m_user) {
        emit userChanged();
        emit dataChanged();
        if (m_waitingForUser) {
            disconnect(QxTdUsers::instance(), &QxTdUsers::userCreated, this, &QxTdMessageSenderUser::updateUser);
            m_waitingForUser = false;
        }
        return;
    }
    connect(QxTdUsers::instance(), &QxTdUsers::userCreated, this, &QxTdMessageSenderUser::updateUser);
    QxTdClient::instance()->send(QJsonObject {
            { "@type", "getUser" },
            { "user_id", userId } });
    m_waitingForUser = true;
}

QString QxTdMessageSenderUser::displayName() const
{
    if (!m_user) {
        return QString();
    }

    QString name = m_user->firstName();

    if (name.isEmpty()) {
        name = m_user->username();
    }

    return name;
}

QString QxTdMessageSenderUser::fullName() const
{
    if (!m_user) {
        return QString();
    }

    return m_user->fullName();
}

QxTdPhoto *QxTdMessageSenderUser::photo() const
{
    if (!m_user) {
        return nullptr;
    }

    return m_user->profilePhoto();
}

QString QxTdMessageSenderUser::initials() const
{
    if (!m_user) {
        return QString();
    }

    return m_user->initials();
}

QString QxTdMessageSenderUser::smallPhotoPath() const {
    return m_user->smallPhotoPath();
}

QJsonObject QxTdMessageSenderUser::marshalJson() const
{
    return QJsonObject {
        { "@type", "messageSenderUser" },
        { "user_id", id() }
    };
}
