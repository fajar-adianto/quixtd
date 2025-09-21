#ifndef QX_TD_GET_CHAT_HISTORY_REQUEST_H
#define QX_TD_GET_CHAT_HISTORY_REQUEST_H

#include "common/qx_td_request.h"

/**
 * @brief The QxTdDeleteMessagesRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1view_messages.html
 */
class QxTdGetChatHistoryRequest : public QxTdRequest
{
    Q_OBJECT
    qint64 m_chatId;
    qint64 m_fromMessageId;
    qint32 m_offset;
    qint32 m_limit;
    bool m_onlyLocal;

public:
    explicit QxTdGetChatHistoryRequest(QObject *parent = nullptr);
    void setChatId(const qint64 &id);
    void setFromMessageId(const qint64 &fromMessageId);
    void setOffset(const qint32 &offset);
    void setLimit(const qint32 &limit);
    void setOnlyLocal(bool value);
    QJsonObject marshalJson();
    QFuture<QxTdResponse> sendAsync();
};

#endif // QX_TD_GET_CHAT_HISTORY_REQUEST_H
