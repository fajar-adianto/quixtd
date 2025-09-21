#include "qx_td_message_pin_message.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessagePinMessage::QxTdMessagePinMessage(QObject *parent)
    : QxTdMessageContent(parent)
    , m_message_id(0)
{
    setType(MESSAGE_PIN_MESSAGE);
}

qint64 QxTdMessagePinMessage::message_id() const
{
    return m_message_id;
}

void QxTdMessagePinMessage::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageContent::unmarshalJson(json);
    m_message_id = json["message_id"].toVariant().toLongLong();
    m_typeText = qxTranslate("Pinned Message");
}
