#ifndef QX_TD_GET_MESSAGE_LINK_REQUEST_H
#define QX_TD_GET_MESSAGE_LINK_REQUEST_H

#include "common/qx_td_request.h"

/**
 * @brief The QxTdGetMessageLinkRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_message_link.html
 */
class QxTdGetMessageLinkRequest : public QxTdRequest
{
    Q_OBJECT
public:
    explicit QxTdGetMessageLinkRequest(QObject *parent = nullptr);

    void setChatId(const qint64 &chat);
    void setMessageId(const qint64 &msg);
    void setMediaTimestamp(const qint32 &timestamp);
    void setForAlbum(const bool &forAlbum);
    void setForComment(const bool &forComment);

    QJsonObject marshalJson();

    QFuture<QxTdResponse> sendAsync();

private:
    qint64 m_chat { 0 };
    qint64 m_msg { 0 };
    qint32 m_media_timestamp { 0 };
    bool m_for_album { false };
    bool m_for_comment { false };

};

#endif // QX_TD_GET_MESSAGE_LINK_REQUEST_H
