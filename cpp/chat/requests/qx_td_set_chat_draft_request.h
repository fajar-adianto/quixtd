#ifndef QX_TD_SET_CHAT_DRAFT_REQUEST_H
#define QX_TD_SET_CHAT_DRAFT_REQUEST_H

#include <QObject>
#include <QJsonArray>

#include "common/qx_td_request.h"
#include "messages/qx_td_draft_message.h"

/**
 * @brief The QxTdSetChatDraftRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1set_chat_draft_message.html
 */
class QxTdSetChatDraftRequest : public QxTdRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdSetChatDraftRequest)
    qint64 m_chatId;
    QScopedPointer<QxTdDraftMessage> m_draftMessage;

public:
    explicit QxTdSetChatDraftRequest(QObject *parent = nullptr);
    void setDraftMessage(QxTdDraftMessage *draftMessage);
    void setChatId(const qint64 &id);
    QJsonObject marshalJson();
    QFuture<QxTdResponse> sendAsync();
};

#endif // QX_TD_SET_CHAT_DRAFT_REQUEST_H
