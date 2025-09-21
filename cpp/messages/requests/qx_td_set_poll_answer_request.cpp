#include "qx_td_set_poll_answer_request.h"

QxTdSetPollAnswerRequest::QxTdSetPollAnswerRequest(QObject *parent)
    : QxTdOkRequest(parent)
    , m_chatId(0)
    , m_messageId(0)
{
    // Intentionally left empty.
}

void QxTdSetPollAnswerRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QxTdSetPollAnswerRequest::setMessageId(const qint64 &id)
{
    m_messageId = id;
}

void QxTdSetPollAnswerRequest::setPollOptions(const QList<qint32> &optionIds)
{
    m_optionIds = optionIds;
}

QJsonObject QxTdSetPollAnswerRequest::marshalJson()
{
    QJsonArray json_polloptions;
    for (auto &m_optionId : m_optionIds) {
        json_polloptions.append(m_optionId);
    }
    return QJsonObject{
        { "@type", "setPollAnswer" },
        { "chat_id", m_chatId },
        { "message_id", m_messageId },
        { "option_ids", json_polloptions },
    };
}
