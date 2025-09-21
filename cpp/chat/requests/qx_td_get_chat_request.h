#ifndef QX_TD_GET_CHAT_REQUEST_H
#define QX_TD_GET_CHAT_REQUEST_H

#include <QObject>
#include <QtConcurrent>
#include "common/qx_td_request.h"
#include "common/qx_td_response.h"

/**
 * @brief The QxTdGetChatRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_chat.html
 */
class QxTdGetChatRequest : public QxTdRequest
{
    Q_OBJECT
public:
    explicit QxTdGetChatRequest(QObject *parent = nullptr);

    QJsonObject marshalJson();

    QFuture<QxTdResponse> sendAsync();

    void setChatId(const QString &id);

    void setChatId(const qint64 &id);

private:
    qint64 m_chat_id;
};

#endif // QX_TD_GET_CHAT_REQUEST_H
