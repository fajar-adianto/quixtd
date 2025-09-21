#ifndef QX_TD_SET_CHAT_TITLE_REQUEST_H
#define QX_TD_SET_CHAT_TITLE_REQUEST_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdSetChatTitleRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1set_chat_title.html
 */
class QxTdSetChatTitleRequest : public QxTdOkRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdSetChatTitleRequest)
    QString m_title;
    qint64 m_chatId;

public:
    explicit QxTdSetChatTitleRequest(QObject *parent = nullptr);

    void setTitle(const qint64 &chatId, const QString &title);
    QJsonObject marshalJson();
};

#endif // QX_TD_SET_CHAT_TITLE_REQUEST_H
