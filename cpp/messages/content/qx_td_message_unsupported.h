#ifndef QX_TD_MESSAGE_UNSUPPORTED_H
#define QX_TD_MESSAGE_UNSUPPORTED_H

#include "messages/qx_td_message_content.h"

class QxTdMessageUnsupported : public QxTdMessageContent
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageUnsupported cannot be created in QML.")
public:
    explicit QxTdMessageUnsupported(QObject *parent = nullptr);

    void unmarshalJson(const QJsonObject &json) override;

private:
    Q_DISABLE_COPY(QxTdMessageUnsupported)
};

#endif // QX_TD_MESSAGE_UNSUPPORTED_H
