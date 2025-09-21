#ifndef QX_TD_SEND_MESSAGE_REQUEST_H
#define QX_TD_SEND_MESSAGE_REQUEST_H

#include <QScopedPointer>

#include "common/qx_td_request.h"
#include "qx_td_input_message_content.h"
#include "qx_td_message_send_options.h"

/**
 * @brief The QxTdSendMessageRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1send_message.html
 */
class QxTdSendMessageRequest : public QxTdRequest
{
    Q_OBJECT

public:
    explicit QxTdSendMessageRequest(QObject *parent = nullptr);
    void setContent(QxTdInputMessageContent *content);
    void setChatId(const qint64 &id);
    void setReplyToMessageId(const qint64 &id);
    void setDisableNotification(const bool value);
    void setSendDate(const qint32 value);
    QJsonObject marshalJson();
    QFuture<QxTdResponse> sendAsync();

private:
    Q_DISABLE_COPY(QxTdSendMessageRequest)
    qint64 m_chatId;
    qint64 m_replyMessageId;
    QxTdInputMessageContent *m_content;
    QScopedPointer<QxTdMessageSendOptions> m_messageSendOptions;

};

#endif // QX_TD_SEND_MESSAGE_REQUEST_H
