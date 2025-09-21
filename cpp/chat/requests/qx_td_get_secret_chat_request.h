#ifndef QX_TD_GET_SECRET_CHAT_REQUEST_H
#define QX_TD_GET_SECRET_CHAT_REQUEST_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdGetSecretChatRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_secret_chat.html
 */
class QxTdGetSecretChatRequest : public QxTdRequest
{
    Q_OBJECT
public:
    explicit QxTdGetSecretChatRequest(QObject *parent = nullptr);

    void setSecretChatId(const qint64 &id);
    QJsonObject marshalJson();

    QFuture<QxTdResponse> sendAsync();

private:
    Q_DISABLE_COPY(QxTdGetSecretChatRequest)
    qint64 m_chatId;
};

#endif // QX_TD_GET_SECRET_CHAT_REQUEST_H
