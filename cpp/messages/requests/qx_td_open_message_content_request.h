#ifndef QX_TD_OPEN_MESSAGE_CONTENT_REQUEST_H
#define QX_TD_OPEN_MESSAGE_CONTENT_REQUEST_H

#include "common/qx_td_request.h"

/**
 * @brief The QxTdSendMessageRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1send_message.html
 */
class QxTdOpenMessageContentRequest : public QxTdRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdOpenMessageContentRequest)
    QString m_chatId;
    QString m_messageId;

public:
    explicit QxTdOpenMessageContentRequest(QObject *parent = nullptr);
    void setChatId(const QString &id);
    void setMessageId(const QString &id);
    QJsonObject marshalJson();
    QFuture<QxTdResponse> sendAsync();
};

#endif // QX_TD_OPEN_MESSAGE_CONTENT_REQUEST_H
