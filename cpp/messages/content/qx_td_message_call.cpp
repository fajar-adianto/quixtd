#include "qx_td_message_call.h"
#include "utils/qx_td_translate_tools.h"
#include <QDebug>
#include <QtMath>

QxTdMessageCall::QxTdMessageCall(QObject *parent)
    : QxTdMessageContent(parent)
    , m_discardReason(nullptr)
    , m_duration(0)
    , m_minutes(0)
    , m_seconds(0)
{
    setType(MESSAGE_CALL);
}

QxTdCallDiscardReason *QxTdMessageCall::discardReason() const
{
    return m_discardReason.data();
}

qint32 QxTdMessageCall::duration() const
{
    return m_duration;
}

QString QxTdMessageCall::hours() const
{
    return QString("%1").arg(m_hours, 2, 10, QChar('0'));
}

QString QxTdMessageCall::minutes() const
{
    return QString("%1").arg(m_minutes, 2, 10, QChar('0'));
}

QString QxTdMessageCall::seconds() const
{
    return QString("%1").arg(m_seconds, 2, 10, QChar('0'));
}

QString QxTdMessageCall::typeText() const
{
    return m_typeText;
}

void QxTdMessageCall::setOutgoing(const bool isOutgoing)
{
    m_isOutgoing = isOutgoing;
    updateTypeText();
}

void QxTdMessageCall::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageContent::unmarshalJson(json);
    m_duration = json["duration"].toInt();
    m_hours = m_duration / 3600;
    m_minutes = m_duration / 60 - m_hours * 60;
    m_seconds = m_duration - m_hours * 3600 - m_minutes * 60;
    const QJsonObject reasonObj = json["discard_reason"].toObject();
    m_reason = reasonObj["@type"].toString();
    updateTypeText();
    emit contentChanged();
}

void QxTdMessageCall::updateTypeText()
{
    if (m_reason == QStringLiteral("callDiscardReasonDeclined")) {
        m_typeText = qxTranslate("Call Declined");
        m_discardReason.reset(new QxTdCallDiscardReasonDeclined(this));
    } else if (m_reason == QStringLiteral("callDiscardReasonDisconnected")) {
        m_typeText = qxTranslate("Call Disconnected");
        m_discardReason.reset(new QxTdCallDiscardReasonDisconnected(this));
    } else if (m_reason == QStringLiteral("callDiscardReasonEmpty")) {
        m_typeText = qxTranslate("Call Ended");
        m_discardReason.reset(new QxTdCallDiscardReasonEmpty(this));
    } else if (m_reason == QStringLiteral("callDiscardReasonHungUp")) {
        // TRANSLATORS: This is a duration in hours:minutes:seconds format - only arrange the order, do not translate!
        auto _length = QString(qxTranslate("%1:%2:%3")).arg(hours(), minutes(), seconds());
        m_typeText = m_isOutgoing ? QString(qxTranslate("Outgoing Call (%1)")).arg(_length)
                                  : QString(qxTranslate("Incoming Call (%1)")).arg(_length);
        m_discardReason.reset(new QxTdCallDiscardReasonHungUp(this));
    } else if (m_reason == QStringLiteral("callDiscardReasonMissed")) {
        m_typeText = m_isOutgoing ? qxTranslate("Cancelled Call") : qxTranslate("Missed Call");
        m_discardReason.reset(new QxTdCallDiscardReasonMissed(this));
    } else {
        m_typeText = qxTranslate("Call");
        m_discardReason.reset();
        qWarning() << "Unknown call discard reason";
    }
}

