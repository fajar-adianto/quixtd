#include "qx_td_chat_report_reason.h"

QxTdChatReportReason::QxTdChatReportReason(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

QJsonObject QxTdChatReportReason::marshalJson() {
    return QJsonObject{
        { "@type", m_type }
    };
}

QxTdChatReportReasonChildAbuse::QxTdChatReportReasonChildAbuse(QObject *parent)
    : QxTdChatReportReason(parent)
{
    m_type = "chatReportReasonChildAbuse";
}

QxTdChatReportReasonCopyright::QxTdChatReportReasonCopyright(QObject *parent)
    : QxTdChatReportReason(parent)
{
    m_type = "chatReportReasonCopyright";
}

QxTdChatReportReasonCustom::QxTdChatReportReasonCustom(QObject *parent)
    : QxTdChatReportReason(parent)
{
    m_type = "chatReportReasonCustom";
}

QxTdChatReportReasonFake::QxTdChatReportReasonFake(QObject *parent)
    : QxTdChatReportReason(parent)
{
    m_type = "chatReportReasonFake";
}

QxTdChatReportReasonPornograhpy::QxTdChatReportReasonPornograhpy(QObject *parent)
    : QxTdChatReportReason(parent)
{
    m_type = "chatReportReasonPornography";
}

QxTdChatReportReasonSpam::QxTdChatReportReasonSpam(QObject *parent)
    : QxTdChatReportReason(parent)
{
    m_type = "chatReportReasonSpam";
}

QxTdChatReportReasonViolence::QxTdChatReportReasonViolence(QObject *parent)
    : QxTdChatReportReason(parent)
{
    m_type = "chatReportReasonViolence";
}

QxTdChatReportReasonUnrelatedLocation::QxTdChatReportReasonUnrelatedLocation(QObject *parent)
    : QxTdChatReportReason(parent)
{
    m_type = "chatReportReasonUnrelatedLocation";
}


