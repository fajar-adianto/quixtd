#include "qx_td_message_location.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageLocation::QxTdMessageLocation(QObject *parent)
    : QxTdMessageContent(parent)
    , m_location(new QxTdLocation)
{
    setType(MESSAGE_LOCATION);
}

QxTdLocation *QxTdMessageLocation::location() const
{
    return m_location.data();
}

void QxTdMessageLocation::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageContent::unmarshalJson(json);
    m_location->unmarshalJson(json["location"].toObject());
    m_typeText = qxTranslate("Location");
}
