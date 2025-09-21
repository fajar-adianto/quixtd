#ifndef QX_TD_CHAT_REPORT_REASON_H
#define QX_TD_CHAT_REPORT_REASON_H

#include "common/qx_td_object.h"

class QxTdChatReportReason : public QxTdObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdChatReportReason and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdChatReportReason)

public:
    explicit QxTdChatReportReason(QObject *parent = nullptr);

    enum ChatReportReasonType {
        ChatReportReasonChildAbuse,
        ChatReportReasonCopyright,
        ChatReportReasonCustom,
        ChatReportReasonFake,
        ChatReportReasonPornography,
        ChatReportReasonSpam,
        ChatReportReasonUnrelatedLocation,
        ChatReportReasonViolence
    };
    Q_ENUM(ChatReportReasonType)

    QJsonObject marshalJson();

protected:
    QString m_type;
    
};

class QxTdChatReportReasonChildAbuse : public QxTdChatReportReason
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatReportReasonChildAbuse)

public:
    explicit QxTdChatReportReasonChildAbuse(QObject *parent = nullptr);
};

class QxTdChatReportReasonCopyright : public QxTdChatReportReason
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatReportReasonCopyright)

public:
    explicit QxTdChatReportReasonCopyright(QObject *parent = nullptr);
};

class QxTdChatReportReasonCustom : public QxTdChatReportReason
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatReportReasonCustom)

public:
    explicit QxTdChatReportReasonCustom(QObject *parent = nullptr);
};

class QxTdChatReportReasonFake : public QxTdChatReportReason
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatReportReasonFake)

public:
    explicit QxTdChatReportReasonFake(QObject *parent = nullptr);
};

class QxTdChatReportReasonPornograhpy : public QxTdChatReportReason
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatReportReasonPornograhpy)

public:
    explicit QxTdChatReportReasonPornograhpy(QObject *parent = nullptr);
};

class QxTdChatReportReasonSpam : public QxTdChatReportReason
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatReportReasonSpam)

public:
    explicit QxTdChatReportReasonSpam(QObject *parent = nullptr);
};

class QxTdChatReportReasonUnrelatedLocation : public QxTdChatReportReason
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatReportReasonUnrelatedLocation)

public:
    explicit QxTdChatReportReasonUnrelatedLocation(QObject *parent = nullptr);
};

class QxTdChatReportReasonViolence : public QxTdChatReportReason
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatReportReasonViolence)

public:
    explicit QxTdChatReportReasonViolence(QObject *parent = nullptr);
};

#endif // QX_TD_CHAT_REPORT_REASON_H
