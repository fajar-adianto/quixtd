#include "qx_td_message_chat_add_members.h"

#include "user/requests/qx_td_get_user_request.h"
#include "utils/qx_td_await.h"
#include "utils/qx_td_translate_tools.h"

#include <QDebug>

QxTdMessageChatAddMembers::QxTdMessageChatAddMembers(QObject *parent)
    : QxTdMessageContent(parent)
    , m_model(new QxTdUsersSortFilterModel)
{
    setType(MESSAGE_CHAT_ADD_MEMBERS);
    m_model->setSourceModel(QxTdUsers::instance()->model());
}

QObject *QxTdMessageChatAddMembers::members() const
{
    return m_model.data();
}

QList<qint64> QxTdMessageChatAddMembers::memberUserIds() const
{
    return m_member_user_ids;
}

qint64 QxTdMessageChatAddMembers::firstMemberId() const
{
    return m_member_user_ids.first();
}

void QxTdMessageChatAddMembers::updateTypeText()
{
    m_typeText = m_senderUserId == firstMemberId() ? qxTranslate("joined the group") : qxTranslate("added one or more members");
}

void QxTdMessageChatAddMembers::setSenderUserId(const qint64 senderUserId)
{
    m_senderUserId = senderUserId;
    updateTypeText();
}

void QxTdMessageChatAddMembers::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageContent::unmarshalJson(json);
    const QJsonArray ids = json["member_user_ids"].toArray();
    QScopedPointer<QxTdGetUserRequest> request(new QxTdGetUserRequest);
    for (const QJsonValue &val : ids) {
        m_member_user_ids << val.toVariant().toLongLong();
    }
    m_model->setAllowedUsers(m_member_user_ids);
    emit membersChanged();

    // Now fetch any users that aren't already in the model
    for (const qint64 &id : m_member_user_ids) {
        const QxTdUser *user = QxTdUsers::instance()->model()->getByUid(QString::number(id));
        if (!user) {
            QScopedPointer<QxTdGetUserRequest> req(new QxTdGetUserRequest);
            req->setUserId(id);
            /**
             * We don't need to wait on a response as it will make its
             * way to the users model anyway and then the sort filter will
             * kick in.
             */
            req->send();
        }
    }
    updateTypeText();
}
