#ifndef QX_TD_REPORT_CHAT_REQUEST_H
#define QX_TD_REPORT_CHAT_REQUEST_H

#include <QString>
#include "common/qx_td_request.h"

class QxTdChatReportReason; // Forward declaration.

class QxTdReportChatRequest : public QxTdOkRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdReportChatRequest)
public:
    explicit QxTdReportChatRequest(QObject *parent = nullptr);

    void setChatId(const QString &id);
    void setMessageIds(const QList<qint64> &messageIds);
    void setReason(QxTdChatReportReason *reason);
    void setText(const QString &text);
    QJsonObject marshalJson(); 

private:
    QString m_chatId;
    QList<qint64> m_messageIds;
    QxTdChatReportReason *m_reason;
    QString m_text;

};

#endif // QX_TD_REPORT_CHAT_REQUEST_H
