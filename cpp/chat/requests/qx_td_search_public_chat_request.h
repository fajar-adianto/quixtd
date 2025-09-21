#ifndef QX_TD_SEARCH_PUBLIC_CHAT_REQUEST_H
#define QX_TD_SEARCH_PUBLIC_CHAT_REQUEST_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdSearchPublicChatRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1search_public_chat.html
 */
class QxTdSearchPublicChatRequest : public QxTdRequest
{
    Q_OBJECT
public:
    explicit QxTdSearchPublicChatRequest(QObject *parent = nullptr);

    void setChatUsername(const QString &username);
    QJsonObject marshalJson();
    QFuture<QxTdResponse> sendAsync();

private:
    QString m_username;
};

#endif // QX_TD_SEARCH_PUBLIC_CHAT_REQUEST_H
