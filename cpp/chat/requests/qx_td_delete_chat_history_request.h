#ifndef QX_TD_DELETE_CHAT_HISTORY_REQUEST_H
#define QX_TD_DELETE_CHAT_HISTORY_REQUEST_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdDeleteChatHistoryRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1delete_chat_history.html
 */
class QxTdDeleteChatHistoryRequest : public QxTdOkRequest
{
    Q_OBJECT
    qint64 m_chatId;
    bool m_removeFromChatList;
    bool m_revoke;

public:
    explicit QxTdDeleteChatHistoryRequest(QObject *parent = nullptr);
    void setChatId(const qint64 &id);
    void setRemoveFromChatList(const bool &remove);
    void setRevoke(const bool &value);
    QJsonObject marshalJson();
};

#endif // QX_TD_DELETE_CHAT_HISTORY_REQUEST_H
