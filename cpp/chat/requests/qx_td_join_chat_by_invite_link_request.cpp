#include "qx_td_join_chat_by_invite_link_request.h"
#include "client/qx_td_client.h"

QxTdJoinChatByInviteLinkRequest::QxTdJoinChatByInviteLinkRequest(QObject *parent)
    : QxTdRequest(parent)
    , m_inviteLink("")
{
    // Intentionally left empty.
}

void QxTdJoinChatByInviteLinkRequest::setInviteLink(const QString &inviteLink)
{
    if (inviteLink.startsWith("https://t.me/joinchat/") || inviteLink.startsWith("https://telegram.me/joinchat/") || inviteLink.startsWith("https://telegram.dog/joinchat/")) {
        m_inviteLink = inviteLink;
    } else {
        m_inviteLink = "https://t.me/joinchat/" + inviteLink;
    }
}

QJsonObject QxTdJoinChatByInviteLinkRequest::marshalJson()
{
    return QJsonObject {
        { "@type", "joinChatByInviteLink" },
        { "invite_link", m_inviteLink }
    };
}

QFuture<QxTdResponse> QxTdJoinChatByInviteLinkRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::chat);
}
