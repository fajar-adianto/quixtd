#ifndef QX_TD_CREATE_PRIVATE_CHAT_REQUEST_H
#define QX_TD_CREATE_PRIVATE_CHAT_REQUEST_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdCreatePrivateChatRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1close_chat.html
 */
class QxTdCreatePrivateChatRequest : public QxTdRequest
{
    Q_OBJECT
    qint64 m_userId;
    bool m_force;

public:
    explicit QxTdCreatePrivateChatRequest(QObject *parent = nullptr);

    /**
     * @brief setChatId
     * @param id of chat to close
     */
    void setUserId(const qint64 &id);
    void setForce(const bool &force);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();

    QFuture<QxTdResponse> sendAsync();
};

#endif // QX_TD_CREATE_PRIVATE_CHAT_REQUEST_H
