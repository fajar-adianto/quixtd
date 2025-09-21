#ifndef QX_TD_DELETE_MESSAGES_REQUEST_H
#define QX_TD_DELETE_MESSAGES_REQUEST_H

#include "common/qx_td_request.h"

/**
 * @brief The QxTdDeleteMessagesRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1view_messages.html
 */
class QxTdDeleteMessagesRequest : public QxTdOkRequest
{
    Q_OBJECT
    qint64 m_chatId;
    QList<qint64> m_messageIds;
    bool m_revoke;

public:
    explicit QxTdDeleteMessagesRequest(QObject *parent = nullptr);
    void setMessageIds(const QList<qint64> &messageIds);
    void setChatId(const qint64 &id);
    void setRevoke(bool value);
    QJsonObject marshalJson();
};

#endif // QX_TD_DELETE_MESSAGES_REQUEST_H
