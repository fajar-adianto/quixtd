#ifndef QX_TD_SET_POLL_ANSWER_REQUEST_H
#define QX_TD_SET_POLL_ANSWER_REQUEST_H

#include "common/qx_td_request.h"

/**
 * @brief The QxTdSetPollAnswerRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1set_poll_answer.html
 */
class QxTdSetPollAnswerRequest : public QxTdOkRequest
{
    Q_OBJECT
    qint64 m_chatId;
    qint64 m_messageId;
    QList<qint32> m_optionIds;

public:
    explicit QxTdSetPollAnswerRequest(QObject *parent = nullptr);
    void setMessageId(const qint64 &messageId);
    void setPollOptions(const QList<qint32> &optionIds);
    void setChatId(const qint64 &id);
    QJsonObject marshalJson() Q_DECL_FINAL;
};

#endif // QX_TD_SET_POLL_ANSWER_REQUEST_H
