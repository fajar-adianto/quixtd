#ifndef QX_TD_MESSAGE_POLL_H
#define QX_TD_MESSAGE_POLL_H

#include "messages/qx_td_message_content.h"
#include "qx_td_poll.h"

class QxTdMessagePoll : public QxTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QxTdPoll *poll READ poll NOTIFY dataChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessagePoll cannot be created in QML.")

public:
    explicit QxTdMessagePoll(QObject *parent = nullptr);

    QxTdPoll *poll();
    
    void unmarshalJson(const QJsonObject &json);

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QxTdMessagePoll)
    std::unique_ptr<QxTdPoll> m_poll;
};

#endif // QX_TD_MESSAGE_POLL_H
