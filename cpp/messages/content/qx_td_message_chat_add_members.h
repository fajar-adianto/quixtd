#ifndef QX_TD_MESSAGE_CHAT_ADD_MEMBERS_H
#define QX_TD_MESSAGE_CHAT_ADD_MEMBERS_H

#include "messages/qx_td_message_content.h"
#include "user/qx_td_users.h"

/**
 * @brief The QxTdMessageChatAddMembers class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_chat_add_members.html
 */
class QxTdMessageChatAddMembers : public QxTdMessageContent
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdMessageChatAddMembers)
    Q_PROPERTY(QObject *members READ members NOTIFY membersChanged)
    Q_PROPERTY(qint64 firstMemberId READ firstMemberId NOTIFY membersChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageChatAddMembers cannot be created in QML.")
public:
    explicit QxTdMessageChatAddMembers(QObject *parent = nullptr);

    QObject *members() const;

    QList<qint64> memberUserIds() const;
    qint64 firstMemberId() const;
    void setSenderUserId(const qint64 senderUserId);

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void membersChanged();

private:
    void updateTypeText();
    std::unique_ptr<QxTdUsersSortFilterModel> m_model;
    QList<qint64> m_member_user_ids;
    qint64 m_senderUserId;
};

#endif // QX_TD_MESSAGE_CHAT_ADD_MEMBERS_H
