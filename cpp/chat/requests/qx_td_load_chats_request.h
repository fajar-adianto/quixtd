#ifndef QX_TD_LOAD_CHATS_REQUEST_H
#define QX_TD_LOAD_CHATS_REQUEST_H

#include <QString>
#include "common/qx_td_request.h"
#include "common/qx_td_response.h"

/**
 * @brief The QxTdLoadChatsRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1load_chats.html
 */
class QxTdLoadChatsRequest : public QxTdOkRequest
{
    Q_OBJECT
public:
    explicit QxTdLoadChatsRequest(QObject *parent = nullptr);

    void setChatList(const QString chatList);

    void setLimit(const qint64 value);

    QJsonObject marshalJson();

private:
    QString m_chatList;
    qint64 m_limit;
};

#endif // QX_TD_LOAD_CHATS_REQUEST_H
