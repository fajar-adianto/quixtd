#ifndef QX_TD_MESSAGE_SCREENSHOT_TAKEN_H
#define QX_TD_MESSAGE_SCREENSHOT_TAKEN_H

#include "messages/qx_td_message_content.h"

class QxTdMessageScreenshotTaken : public QxTdMessageContent
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageScreenshotTaken cannot be created in QML.")
public:
    explicit QxTdMessageScreenshotTaken(QObject *parent = nullptr);

    void unmarshalJson(const QJsonObject &json) override;

private:
    Q_DISABLE_COPY(QxTdMessageScreenshotTaken)
};

#endif // QX_TD_MESSAGE_SCREENSHOT_TAKEN_H
