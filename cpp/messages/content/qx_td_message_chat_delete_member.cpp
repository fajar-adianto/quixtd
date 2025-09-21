#include "qx_td_message_chat_delete_member.h"
#include "user/qx_td_users.h"
#include "user/requests/qx_td_get_user_request.h"
#include "utils/qx_td_await.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageChatDeleteMember::QxTdMessageChatDeleteMember(QObject *parent)
    : QxTdMessageContent(parent)
    , m_user(nullptr)
{
    setType(MESSAGE_CHAT_DELETE_MEMBER);
    connect(&m_watcher, &QFutureWatcher<QxTdResponse>::finished, this, &QxTdMessageChatDeleteMember::handleResponse);
}

QxTdUser *QxTdMessageChatDeleteMember::user() const
{
    return m_user;
}

QString QxTdMessageChatDeleteMember::qmlUserId() const
{
    return m_uid.toQmlValue();
}

qint64 QxTdMessageChatDeleteMember::userId() const
{
    return m_uid.value();
}

void QxTdMessageChatDeleteMember::updateTypeText()
{
    m_typeText = m_senderUserId == userId() ? qxTranslate("left the group") : qxTranslate("removed a member");
}

void QxTdMessageChatDeleteMember::setSenderUserId(const qint64 senderUserId)
{
    m_senderUserId = senderUserId;
    updateTypeText();
}

void QxTdMessageChatDeleteMember::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageContent::unmarshalJson(json);
    if (json.contains("user_id")) {
        m_uid = json["user_id"].toVariant().toLongLong();
        emit contentChanged();

        updateTypeText();
        auto *user = QxTdUsers::instance()->model()->getByUid(m_uid.toQmlValue());
        if (user) {
            m_user = user;
            emit userChanged();
            return;
        }

        QScopedPointer<QxTdGetUserRequest> request(new QxTdGetUserRequest);
        request->setUserId(m_uid.value());
        m_watcher.setFuture(request->sendAsync());
    }
}

void QxTdMessageChatDeleteMember::handleResponse()
{
    const QxTdResponse resp = m_watcher.result();
    if (resp.isError()) {
        qWarning() << resp.errorString();
        return;
    }
    m_user = new QxTdUser(this);
    m_user->unmarshalJson(resp.json());
    emit userChanged();
}
