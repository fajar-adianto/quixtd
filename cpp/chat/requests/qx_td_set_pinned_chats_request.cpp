#include "qx_td_set_pinned_chats_request.h"
#include <QJsonArray>

QxTdSetPinnedChatsRequest::QxTdSetPinnedChatsRequest(QObject *parent)
    : QxTdOkRequest(parent)
{
    // Intentionally left empty.
}

void QxTdSetPinnedChatsRequest::setPinnedChats(const QList<qint64> &chatIds)
{
    m_chatIds = chatIds;
}

QJsonObject QxTdSetPinnedChatsRequest::marshalJson()
{
    QJsonArray ids;
    for (const qint64 &id : m_chatIds) {
        ids << QJsonValue(id);
    }
    return QJsonObject{
        { "@type", "setPinnedChats" },
        { "chat_ids", ids },
    };
}
