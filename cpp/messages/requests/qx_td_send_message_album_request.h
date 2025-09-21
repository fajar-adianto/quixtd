#ifndef QX_TD_SEND_MESSAGE_ALBUM_REQUEST_H
#define QX_TD_SEND_MESSAGE_ALBUM_REQUEST_H

#include <QScopedPointer>
#include <QList>

#include "common/qx_td_request.h"
#include "qx_td_input_message_content.h"
#include "qx_td_message_send_options.h"

/**
 * @brief The QxTdSendMessageAlbumRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1send_message_album.html
 */
class QxTdSendMessageAlbumRequest : public QxTdRequest
{
    Q_OBJECT

public:
    explicit QxTdSendMessageAlbumRequest(QObject *parent = nullptr);
    void setContents(const QList<QxTdInputMessageContent*> &contents);
    void setChatId(const qint64 &id);
    void setReplyToMessageId(const qint64 &id);
    void setDisableNotification(const bool value);
    void setSendDate(const qint32 value);
    QJsonObject marshalJson();
    QFuture<QxTdResponse> sendAsync();

private:
    Q_DISABLE_COPY(QxTdSendMessageAlbumRequest)
    qint64 m_chatId;
    qint64 m_replyMessageId;
    QList<QxTdInputMessageContent*> m_contents;
    QScopedPointer<QxTdMessageSendOptions> m_messageSendOptions;

};

#endif // QX_TD_SEND_MESSAGE_ALBUM_REQUEST_H
