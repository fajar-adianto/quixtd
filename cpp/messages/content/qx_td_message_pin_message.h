#ifndef QX_TD_MESSAGE_PIN_MESSAGE_H
#define QX_TD_MESSAGE_PIN_MESSAGE_H

#include "messages/qx_td_message_content.h"

class QxTdMessagePinMessage : public QxTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(qint64 message_id READ message_id NOTIFY dataChanged)
    QML_ELEMENT
public:
    explicit QxTdMessagePinMessage(QObject *parent = nullptr);

    qint64 message_id() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QxTdMessagePinMessage)
    qint64 m_message_id;
};

#endif // QX_TD_MESSAGE_PIN_MESSAGE_H
