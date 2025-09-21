#include "common/qx_td_object.h"
#include "qx_td_message_forward_origin.h"
#include "common/qx_td_helpers.h"
#include "user/qx_td_users.h"
#include "user/qx_td_user.h"
#include "user/requests/qx_td_get_user_request.h"
#include "chat/qx_td_chat_list_model.h"
#include "chat/qx_td_chat.h"
#include "chat/requests/qx_td_get_chat_request.h"
#include "utils/qx_td_await.h" 

QxTdMessageForwardOrigin::QxTdMessageForwardOrigin(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

QxTdMessageForwardOriginChat::QxTdMessageForwardOriginChat(QObject *parent)
    : QxTdMessageForwardOrigin(parent)
    , m_senderChatId(0)
{
    setType(MESSAGE_FORWARD_ORIGIN_CHAT);
}

QString QxTdMessageForwardOriginChat::originSummary() const
{
    return m_senderChatname;
}

QString QxTdMessageForwardOriginChat::qmlChatId() const
{
    return m_senderChatId.toQmlValue();
}
qint64 QxTdMessageForwardOriginChat::chatId() const
{
    return m_senderChatId.value();
}

QString QxTdMessageForwardOriginChat::authorSignature() const
{
    return m_authorSignature;
}

void QxTdMessageForwardOriginChat::unmarshalJson(const QJsonObject &json)
{
     QxTdMessageForwardOrigin::unmarshalJson(json);
    if (json.isEmpty()) {
        return;
    }
    m_senderChatId = json["sender_chat_id"].toVariant().toLongLong();
    m_authorSignature = json["author_signature"].toString();

    auto *chat = QxTdChatListModel::instance()->chatById(m_senderChatId.value());
    if (chat) {
        m_senderChatname = chat->title();
    } else {
        QScopedPointer<QxTdGetChatRequest> req(new QxTdGetChatRequest);
        req->setChatId(m_senderChatId.value());
        QFuture<QxTdResponse> resp = req->sendAsync();
        qxAwait(resp);
        if (resp.result().isError()) {
            qWarning() << "QxTdMessageForwardOriginChat::unmarshalJson Failed to get chat with error: " << resp.result().errorString();
            m_senderChatname = "";
        } else if (!resp.result().json().isEmpty()) {
            m_senderChatname = resp.result().json()["title"].toString();
        }
    }
    emit forwardOriginChanged();
}

QxTdMessageForwardOriginChannel::QxTdMessageForwardOriginChannel(QObject *parent)
    : QxTdMessageForwardOrigin(parent)
    , m_chatId(0)
    , m_messageId(0)
{
    setType(MESSAGE_FORWARD_ORIGIN_CHANNEL);
}

QString QxTdMessageForwardOriginChannel::originSummary() const
{
    return m_senderChannelname;
}

QString QxTdMessageForwardOriginChannel::qmlChatId() const
{
    return m_chatId.toQmlValue();
}
qint64 QxTdMessageForwardOriginChannel::chatId() const
{
    return m_chatId.value();
}

QString QxTdMessageForwardOriginChannel::qmlMessageId() const
{
    return m_messageId.toQmlValue();
}
qint64 QxTdMessageForwardOriginChannel::messageId() const
{
    return m_messageId.value();
}

QString QxTdMessageForwardOriginChannel::authorSignature() const
{
    return m_authorSignature;
}

void QxTdMessageForwardOriginChannel::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageForwardOrigin::unmarshalJson(json);
    if (json.isEmpty()) {
        return;
    }
    m_chatId = json["chat_id"].toVariant().toLongLong();
    m_messageId = json["message_id"].toVariant().toLongLong();
    m_authorSignature = json["author_signature"].toString();
    auto *chat = QxTdChatListModel::instance()->chatById(m_chatId.value());
    if (chat) {
        m_senderChannelname = chat->title();
    } else {
        QScopedPointer<QxTdGetChatRequest> req(new QxTdGetChatRequest);
        req->setChatId(m_chatId.value());
        QFuture<QxTdResponse> resp = req->sendAsync();
        qxAwait(resp);
        if (resp.result().isError()) {
            qWarning() << "QxTdMessageForwardOriginChannel::unmarshalJson Failed to get channel with error: " << resp.result().errorString();
            m_senderChannelname = "";
        } else if (!resp.result().json().isEmpty()) {
            m_senderChannelname = resp.result().json()["title"].toString();
        }
    }
    emit forwardOriginChanged();
}

QxTdMessageForwardOriginHiddenUser::QxTdMessageForwardOriginHiddenUser(QObject *parent)
    : QxTdMessageForwardOrigin(parent)
{
    setType(MESSAGE_FORWARD_ORIGIN_HIDDEN_USER);
}

QString QxTdMessageForwardOriginHiddenUser::originSummary() const
{
    return senderName();
}

QString QxTdMessageForwardOriginHiddenUser::senderName() const
{
    return m_senderName;
}

void QxTdMessageForwardOriginHiddenUser::unmarshalJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }
    QxTdMessageForwardOrigin::unmarshalJson(json);
    m_senderName = json["sender_name"].toString();
    emit forwardOriginChanged();
}

QxTdMessageForwardOriginUser::QxTdMessageForwardOriginUser(QObject *parent)
    : QxTdMessageForwardOrigin(parent)
    , m_senderUserId(0)
{
    setType(MESSAGE_FORWARD_ORIGIN_USER);
}

QString QxTdMessageForwardOriginUser::originSummary() const
{
    return m_senderUsername;
}

QString QxTdMessageForwardOriginUser::qmlSenderUserId() const
{
    return m_senderUserId.toQmlValue();
}

qint64 QxTdMessageForwardOriginUser::senderUserId() const
{
    return m_senderUserId.value();
}

void QxTdMessageForwardOriginUser::unmarshalJson(const QJsonObject &json)
{
    QString firstName, lastName;

    if (json.isEmpty()) {
        return;
    }
    QxTdMessageForwardOrigin::unmarshalJson(json);
    m_senderUserId = json["sender_user_id"].toVariant().toLongLong();
    auto *user = QxTdUsers::instance()->model()->getByUid(QString::number(m_senderUserId.value()));
    if (user) {
        firstName = user->firstName();
        lastName = user->lastName();
    } else {
        QScopedPointer<QxTdGetUserRequest> req(new QxTdGetUserRequest);
        req->setUserId(m_senderUserId.value());
        QFuture<QxTdResponse> resp = req->sendAsync();
        qxAwait(resp);
        if (resp.result().isError()) {
            qWarning() << "Failed to get user with error: " << resp.result().errorString();
        } else {
            auto tempUser = new QxTdUser(this);
            tempUser->unmarshalJson(resp.result().json());
            firstName = tempUser->firstName();
            lastName = tempUser->lastName();
            delete tempUser;
        }
    }
    m_senderUsername = firstName;
    if (!lastName.isEmpty()) {
        m_senderUsername += " " + lastName;
    }
    emit forwardOriginChanged();
}
