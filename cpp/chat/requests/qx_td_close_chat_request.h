#ifndef QX_TD_CLOSE_CHAT_REQUEST_H
#define QX_TD_CLOSE_CHAT_REQUEST_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdCloseChatRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1close_chat.html
 */
class QxTdCloseChatRequest : public QxTdOkRequest
{
    Q_OBJECT
    qint64 m_chatId;

public:
    explicit QxTdCloseChatRequest(QObject *parent = nullptr);

    /**
     * @brief setChatId
     * @param id of chat to close
     */
    void setChatId(const qint64 &id);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();
};

#endif // QX_TD_CLOSE_CHAT_REQUEST_H
