#ifndef QX_TD_CLOSE_SECRET_CHAT_REQUEST_H
#define QX_TD_CLOSE_SECRET_CHAT_REQUEST_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdCloseSecretChatRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1close_secret_chat.html
 */
class QxTdCloseSecretChatRequest : public QxTdOkRequest
{
    Q_OBJECT
    qint64 m_secretChatId;
    bool m_removeFromChatList;

public:
    explicit QxTdCloseSecretChatRequest(QObject *parent = nullptr);
    void setSecretChatId(const qint64 &id);
    QJsonObject marshalJson();
};

#endif // QX_TD_CLOSE_SECRET_CHAT_REQUEST_H
