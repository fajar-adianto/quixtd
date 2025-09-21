#ifndef QX_TD_SET_PINNED_CHATS_REQUEST_H
#define QX_TD_SET_PINNED_CHATS_REQUEST_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdSetPinnedChatsRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1set_pinned_chats.html
 */
class QxTdSetPinnedChatsRequest : public QxTdOkRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdSetPinnedChatsRequest)
    QList<qint64> m_chatIds;

public:
    explicit QxTdSetPinnedChatsRequest(QObject *parent = nullptr);

    void setPinnedChats(const QList<qint64> &chatIds);
    QJsonObject marshalJson();
};

#endif // QX_TD_SET_PINNED_CHATS_REQUEST_H
