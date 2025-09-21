#ifndef QX_TD_CHECK_CHAT_INVITE_LINK_REQUEST_H
#define QX_TD_CHECK_CHAT_INVITE_LINK_REQUEST_H

#include "common/qx_td_request.h"

/**
 * @brief The QxTdCheckChatInviteLinkRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1check_chat_invite_link.html
 */
class QxTdCheckChatInviteLinkRequest : public QxTdRequest
{
    Q_OBJECT
public:
    explicit QxTdCheckChatInviteLinkRequest(QObject *parent = nullptr);

    void setInviteLink(const QString &inviteLink);

    QJsonObject marshalJson();
    QFuture<QxTdResponse> sendAsync();

private:
    QString m_inviteLink;
};

#endif // QX_TD_CHECK_CHAT_INVITE_LINK_REQUEST_H
