#include "qx_td_message_sender_chat.h"
#include "chat/qx_td_chat.h"
#include "chat/qx_td_chat_list_model.h"
#include "client/qx_td_client.h"
#include "utils/debug.h"

QxTdMessageSenderChat::QxTdMessageSenderChat(QObject *parent)
    : QxTdMessageSender(parent)
{
    setType(MESSAGE_SENDER_CHAT);
}

void QxTdMessageSenderChat::unmarshalJson(const QJsonObject &json, const QString &id_key)
{
    QxTdMessageSender::unmarshalJson(json, "chat_id");
    updateChat(id());
}

void QxTdMessageSenderChat::updateChat(const qint64 &chatId)
{
    if (chatId != id()) {
        return;
    }
    if (m_chat) {
        m_chat = nullptr;
    }

    auto *chats = QxTdChatListModel::instance();
    m_chat = chats->chatById(chatId);
    if (m_chat) {
        emit chatChanged();
        if (m_waitingForChat) {
            disconnect(QxTdChatListModel::instance(), &QxTdChatListModel::chatCreated, this, &QxTdMessageSenderChat::updateChat);
            m_waitingForChat = false;
        }
        return;
    }
    connect(QxTdChatListModel::instance(), &QxTdChatListModel::chatCreated, this, &QxTdMessageSenderChat::updateChat);
    QxTdClient::instance()->send(QJsonObject {
            { "@type", "getChat" },
            { "chat_id", chatId } });
    m_waitingForChat = true;
}

QString QxTdMessageSenderChat::displayName() const
{
    if (!m_chat) {
        return QString();
    }

    return m_chat->title();
}

QString QxTdMessageSenderChat::fullName() const
{
    return displayName();
}

QxTdPhoto *QxTdMessageSenderChat::photo() const
{
    if (!m_chat) {
        return nullptr;
    }

    return m_chat->chatPhoto();
}

QString QxTdMessageSenderChat::initials() const
{
    if (!m_chat) {
        return QString();
    }

    return m_chat->initials();
}

QString QxTdMessageSenderChat::smallPhotoPath() const {
    return photo()->smallPhotoPath();
}

QJsonObject QxTdMessageSenderChat::marshalJson() const
{
    return QJsonObject {
        { "@type", "messageSenderChat" },
        { "chat_id", id() }
    };
}
