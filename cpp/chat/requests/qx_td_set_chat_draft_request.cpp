#include "qx_td_set_chat_draft_request.h"
#include <QJsonArray>
#include "client/qx_td_client.h"
#include "messages/qx_td_draft_message.h"

QxTdSetChatDraftRequest::QxTdSetChatDraftRequest(QObject *parent)
    : QxTdRequest(parent)
    , m_chatId(0)
    , m_draftMessage(new QxTdDraftMessage)
{
    // Intentionally left empty.
}

void QxTdSetChatDraftRequest::setDraftMessage(QxTdDraftMessage *draftMessage)
{
    m_draftMessage.reset(draftMessage);
}

void QxTdSetChatDraftRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

QJsonObject QxTdSetChatDraftRequest::marshalJson()
{

    return QJsonObject {
        { "@type", "setChatDraftMessage" },
        { "chat_id", m_chatId },
        { "draft_message", m_draftMessage->marshalJson() }
    };
}

QFuture<QxTdResponse> QxTdSetChatDraftRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::chat);
}
