#include "qx_td_message_screenshot_taken.h"

QxTdMessageScreenshotTaken::QxTdMessageScreenshotTaken(QObject *parent)
    : QxTdMessageContent(parent)
{
    setType(MESSAGE_SCREENSHOT_TAKEN);
}

void QxTdMessageScreenshotTaken::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageContent::unmarshalJson(json);
}
