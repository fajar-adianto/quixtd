#ifndef QX_TD_GET_CHATS_REQUEST_H
#define QX_TD_GET_CHATS_REQUEST_H

#include <QObject>
#include <QtConcurrent>
#include <QString>
#include "common/qx_td_request.h"
#include "common/qx_td_response.h"

/**
 * @brief The QxTdGetChatsRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_chats.html
 */
class QxTdGetChatsRequest : public QxTdRequest
{
    Q_OBJECT
public:
    explicit QxTdGetChatsRequest(QObject *parent = nullptr);

    void setChatList(const QString chatList);

    void setLimit(const qint64 value);

    QJsonObject marshalJson();

    QFuture<QxTdResponse> sendAsync();

private:
    QString m_chatList;
    qint64 m_limit;
};

#endif // QX_TD_GET_CHATS_REQUEST_H
