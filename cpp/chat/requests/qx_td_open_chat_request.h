#ifndef QX_TD_OPEN_CHAT_REQUEST_H
#define QX_TD_OPEN_CHAT_REQUEST_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdOpenChatRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1open_chat.html
 */
class QxTdOpenChatRequest : public QxTdOkRequest
{
    Q_OBJECT
    qint64 m_chatId;

public:
    explicit QxTdOpenChatRequest(QObject *parent = nullptr);
    void setChatId(const qint64 &id);
    QJsonObject marshalJson();
};

#endif // QX_TD_OPEN_CHAT_REQUEST_H
