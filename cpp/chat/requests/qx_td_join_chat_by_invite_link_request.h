#ifndef QX_TD_JOIN_CHAT_BY_INVITE_LINK_REQUEST_H
#define QX_TD_JOIN_CHAT_BY_INVITE_LINK_REQUEST_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdJoinChatByInviteLinkRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1join_chat_by_invite_link.html
 */
class QxTdJoinChatByInviteLinkRequest : public QxTdRequest
{
    Q_OBJECT
public:
    explicit QxTdJoinChatByInviteLinkRequest(QObject *parent = nullptr);

    /**
     * @brief Invite link to import; should begin with "https://t.me/joinchat/", "https://telegram.me/joinchat/", or "https://telegram.dog/joinchat/".
     */
    void setInviteLink(const QString &inviteLink);

    QJsonObject marshalJson();
    QFuture<QxTdResponse> sendAsync();

private:
    QString m_inviteLink;
};

#endif // QX_TD_JOIN_CHAT_BY_INVITE_LINK_REQUEST_H
