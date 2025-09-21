#include "qx_td_message_poll.h"

QxTdMessagePoll::QxTdMessagePoll(QObject *parent)
    : QxTdMessageContent(parent)
    , m_poll(new QxTdPoll)
{
    setType(MESSAGE_POLL);
}

QxTdPoll* QxTdMessagePoll::poll() {
    return m_poll.data();
}

void QxTdMessagePoll::unmarshalJson(const QJsonObject &json)
{
    m_poll->unmarshalJson(json["poll"].toObject());
}
