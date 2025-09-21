#ifndef QX_TD_CREATE_NEW_SECRET_CHAT_REQUEST_H
#define QX_TD_CREATE_NEW_SECRET_CHAT_REQUEST_H

#include "common/qx_td_request.h"

/**
 * @brief The QxTdCloseChatRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1close_chat.html
 */
class QxTdCreateNewSecretChatRequest : public QxTdRequest
{
    Q_OBJECT
    qint64 m_userId;

public:
    explicit QxTdCreateNewSecretChatRequest(QObject *parent = nullptr);

    /**
     * @brief setChatId
     * @param id of chat to close
     */
    void setUserId(const qint64 &id);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();

    QFuture<QxTdResponse> sendAsync();
};

#endif // QX_TD_CREATE_NEW_SECRET_CHAT_REQUEST_H
