#ifndef QX_TD_MESSAGE_CHAT_SET_MESSAGE_AUTO_DELETE_TIME_H
#define QX_TD_MESSAGE_CHAT_SET_MESSAGE_AUTO_DELETE_TIME_H

#include <QList>
#include "messages/qx_td_message_content.h"

class QxTdMessageChatSetMessageAutoDeleteTime : public QxTdMessageContent {
    Q_OBJECT
    Q_PROPERTY(qint32 messageAutoDeleteTime READ messageAutoDeleteTime WRITE setMessageAutoDeleteTime NOTIFY dataChanged)
    Q_PROPERTY(qint64 fromUserId READ fromUserId WRITE setFromUserId NOTIFY dataChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageChatSetMessageAutoDeleteTime cannot be created in QML.")
public:
    explicit QxTdMessageChatSetMessageAutoDeleteTime(QObject *parent = nullptr);
    explicit QxTdMessageChatSetMessageAutoDeleteTime(QObject *parent, qint32 messageAutoDeleteTime_, qint64 fromUserId_);

    qint32 messageAutoDeleteTime() const;
    void setMessageAutoDeleteTime(qint32 value);
    qint64 fromUserId() const;
    void setFromUserId(qint64 value);

    void unmarshalJson(const QJsonObject &json) override;
    QJsonObject marshalJson() override;

private:
    Q_DISABLE_COPY(QxTdMessageChatSetMessageAutoDeleteTime)
    qint32 m_messageAutoDeleteTime;
    qint64 m_fromUserId;

signals:
    void dataChanged();

};

#endif // QX_TD_MESSAGE_CHAT_SET_MESSAGE_AUTO_DELETE_TIME_H
