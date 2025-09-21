#include "qx_td_input_message_location.h"

QxTdInputMessageLocation::QxTdInputMessageLocation(QObject *parent)
    : QxTdInputMessageContent(parent)
    , m_location(nullptr)
    , m_live_period(0)
{
    // Intentionally left empty.
}

void QxTdInputMessageLocation::setLocation(double latitude, double longitude)
{
    m_location.reset(new QxTdLocation());
    m_location->setLatitude(latitude);
    m_location->setLongitude(longitude);
}

void QxTdInputMessageLocation::setLivePeriod(const qint32 live_period)
{
    m_live_period = live_period;
}
QJsonObject QxTdInputMessageLocation::marshalJson()
{
    return QJsonObject{
        { "@type", "inputMessageLocation" },
        { "location", m_location->marshalJson() },
        { "live_period", m_live_period }
    };
}
