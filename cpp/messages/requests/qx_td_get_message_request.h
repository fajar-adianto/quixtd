#ifndef QX_TD_GET_MESSAGE_REQUEST_H
#define QX_TD_GET_MESSAGE_REQUEST_H

#include "common/qx_td_request.h"

/**
 * @brief The QxTdGetMessageRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_message.html
 */
class QxTdGetMessageRequest : public QxTdRequest
{
    Q_OBJECT
public:
    explicit QxTdGetMessageRequest(QObject *parent = nullptr);

    void setChatId(const qint64 &chat);

    void setMessageId(const qint64 &msg);

    QJsonObject marshalJson();

    QFuture<QxTdResponse> sendAsync();

private:
    qint64 m_chat{ 0 };
    qint64 m_msg{ 0 };
};

#endif // QX_TD_GET_MESSAGE_REQUEST_H
