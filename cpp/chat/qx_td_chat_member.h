#ifndef QX_TD_CHAT_MEMBER_H
#define QX_TD_CHAT_MEMBER_H

#include <QObject>
#include <QScopedPointer>
#include <QDateTime>
#include "messages/qx_td_message_sender.h"
#include "qx_td_chat_member_status.h"

/**
 * @brief The QxTdChatMember class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_member.html
 */
class QxTdChatMember : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QxTdMessageSender *memberId READ memberId NOTIFY chatMemberChanged)
    Q_PROPERTY(QString inviteUserId READ qmlInviteUserId NOTIFY chatMemberChanged)
    Q_PROPERTY(QDateTime joinedChatDate READ qmlJoinedChatDate NOTIFY chatMemberChanged)
    Q_PROPERTY(QxTdChatMemberStatus *status READ status NOTIFY chatMemberChanged)
    QML_ELEMENT
    // TODO: botInfo https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1bot_info.html
public:
    explicit QxTdChatMember(QObject *parent = nullptr);

    QxTdMessageSender *memberId() const;
    QString qmlInviteUserId() const;
    qint64 inviteUserId() const;
    QDateTime qmlJoinedChatDate() const;
    qint32 joinedChatDate() const;
    QxTdChatMemberStatus *status() const;

    void unmarshalJson(const QJsonObject &json) override;
    // TODO: allow admins to set status on a member
    //    Q_INVOKABLE void setStatus();

signals:
    void chatMemberChanged();
    void userChanged();

private:
    Q_DISABLE_COPY(QxTdChatMember)
    QScopedPointer<QxTdMessageSender> m_memberId;
    QxTdInt64 m_inviteUserId;
    QxTdInt32 m_joinedChatDate;
    QScopedPointer<QxTdChatMemberStatus> m_status;
};

#endif // QX_TD_CHAT_MEMBER_H
