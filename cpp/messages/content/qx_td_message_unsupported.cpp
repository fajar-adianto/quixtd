#include "qx_td_message_unsupported.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageUnsupported::QxTdMessageUnsupported(QObject *parent)
    : QxTdMessageContent(parent)
{
    setType(MESSAGE_UNSUPPORTED);
}

void QxTdMessageUnsupported::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageContent::unmarshalJson(json);
    m_typeText = qxTranslate("Unsupported message");
}
