#include "qx_td_check_chat_invite_link_request.h"
#include "client/qx_td_client.h"

QxTdCheckChatInviteLinkRequest::QxTdCheckChatInviteLinkRequest(QObject *parent)
    : QxTdRequest(parent)
    , m_inviteLink("")
{
    // Intentionally left empty.
}

void QxTdCheckChatInviteLinkRequest::setInviteLink(const QString &inviteLink)
{
    if (inviteLink.startsWith("https://t.me/joinchat/") || inviteLink.startsWith("https://telegram.me/joinchat/") || inviteLink.startsWith("https://telegram.dog/joinchat/")) {
        m_inviteLink = inviteLink;
    } else {
        m_inviteLink = "https://t.me/joinchat/" + inviteLink;
    }
}

QJsonObject QxTdCheckChatInviteLinkRequest::marshalJson()
{
    return QJsonObject {
        { "@type", "checkChatInviteLink" },
        { "invite_link", m_inviteLink }
    };
}

QFuture<QxTdResponse> QxTdCheckChatInviteLinkRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::chatInviteLinkInfo);
}
