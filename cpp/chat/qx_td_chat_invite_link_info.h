#ifndef QX_TD_CHAT_INVITE_LINK_INFO_H
#define QX_TD_CHAT_INVITE_LINK_INFO_H

#include "qx_td_chat.h"
#include "common/qx_td_request.h"
#include "user/qx_td_user.h"

/**
 * @brief The QxTdChatInviteLinkInfo class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_invite_link_info.html
 */
class QxTdChatInviteLinkInfo : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString inviteLink READ inviteLink NOTIFY chatInviteLinkInfoChanged)
    Q_PROPERTY(QString chatId READ qmlChatId NOTIFY chatInviteLinkInfoChanged)
    Q_PROPERTY(QObject *type READ type NOTIFY chatInviteLinkInfoChanged)
    Q_PROPERTY(QString title READ title NOTIFY chatInviteLinkInfoChanged)
    Q_PROPERTY(QObject *photo READ photo NOTIFY chatInviteLinkInfoChanged)
    Q_PROPERTY(QString memberCount READ qmlMemberCount NOTIFY chatInviteLinkInfoChanged)
    Q_PROPERTY(QObject *memberUsers READ memberUsers NOTIFY chatInviteLinkInfoChanged)
    Q_PROPERTY(bool isPublic READ isPublic NOTIFY chatInviteLinkInfoChanged)
    // These aren't original properties of the tdlib message class but we can
    // can make life easier for use in QML.
    Q_PROPERTY(QString initials READ initials NOTIFY chatInviteLinkInfoChanged)
    Q_PROPERTY(QString avatarColor READ avatarColor NOTIFY chatInviteLinkInfoChanged)
    Q_PROPERTY(QString highlightedMemberCount READ highlightedMemberCount NOTIFY chatInviteLinkInfoChanged)
    QML_ELEMENT
public:
    explicit QxTdChatInviteLinkInfo(QObject *parent = nullptr);

    QString inviteLink() const;
    qint64 chatId() const;
    QString qmlChatId() const;
    QxTdChatType *type() const;
    QString title() const;
    QxTdChatPhoto *photo() const;
    qint32 memberCount() const;
    QString qmlMemberCount() const;
    QxTdObjectListModel<QxTdUser> *memberUsers() const;
    QList<qint64> memberUserIds() const;
    bool isPublic() const;

    QString initials() const;
    QString highlightedMemberCount() const;
    QString avatarColor() const;

    void unmarshalJson(QJsonObject &json);

signals:
    void chatInviteLinkInfoChanged();

private:
    QString m_inviteLink;
    QxTdInt64 m_chatId;
    std::unique_ptr<QxTdChatType> m_type;
    QString m_title;
    std::unique_ptr<QxTdChatPhoto> m_photo;
    QxTdInt32 m_memberCount;
    std::unique_ptr<QxTdObjectListModel<QxTdUser>> m_memberUsers;
    QList<qint64> m_memberUserIds;
    bool m_isPublic;

    QString m_initials;
    QString m_avatarColor;
    QxTdInt32 m_highlightedMemberCount;
};

#endif // QX_TD_CHAT_INVITE_LINK_INFO_H
