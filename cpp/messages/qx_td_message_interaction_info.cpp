#include "qx_td_message_interaction_info.h"

QxTdMessageInteractionInfo::QxTdMessageInteractionInfo(QObject *parent)
    : QxTdObject(parent)
    , m_viewCount(0)
    , m_forwardCount(0)
{
    setType(MESSAGE_INTERACTION_INFO);
}

qint32 QxTdMessageInteractionInfo::viewCount() const
{
    return m_viewCount.value();
}

QString QxTdMessageInteractionInfo::qmlViewCount() const
{
    return m_viewCount.toQmlValue();
}

qint32 QxTdMessageInteractionInfo::forwardCount() const
{
    return m_forwardCount.value();
}

QString QxTdMessageInteractionInfo::qmlForwardCount() const
{
    return m_forwardCount.toQmlValue();
}

void QxTdMessageInteractionInfo::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_viewCount = json["view_count"].toInt();
    m_forwardCount = json["forward_count"].toInt();
    emit interactionInfoChanged();
}
