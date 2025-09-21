#ifndef QX_TD_VIEW_MESSAGES_REQUEST_H
#define QX_TD_VIEW_MESSAGES_REQUEST_H

#include "common/qx_td_request.h"

/**
 * @brief The QxTdViewMessagesRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1view_messages.html
 */
class QxTdViewMessagesRequest : public QxTdOkRequest
{
    Q_OBJECT
    qint64 m_chatId;
    QList<qint64> m_messageIds;

public:
    explicit QxTdViewMessagesRequest(QObject *parent = nullptr);
    void setMessageIds(const QList<qint64> &messageIds);
    void setChatId(const qint64 &id);
    QJsonObject marshalJson();
};

#endif // QX_TD_VIEW_MESSAGES_REQUEST_H
