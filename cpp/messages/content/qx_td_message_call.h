#ifndef QX_TD_MESSAGE_CALL_H
#define QX_TD_MESSAGE_CALL_H

#include "messages/qx_td_message_content.h"
#include "call/qx_td_call_discard_reason.h"

/**
 * @brief The QxTdMessageCall class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_call.html
 */
class QxTdMessageCall : public QxTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QxTdCallDiscardReason *discardReason READ discardReason NOTIFY contentChanged)
    Q_PROPERTY(qint32 duration READ duration NOTIFY contentChanged)
    Q_PROPERTY(QString hours READ hours NOTIFY contentChanged)
    Q_PROPERTY(QString minutes READ minutes NOTIFY contentChanged)
    Q_PROPERTY(QString seconds READ seconds NOTIFY contentChanged)
    Q_PROPERTY(QString typeText READ typeText NOTIFY contentChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageCall cannot be created in QML.")
public:
    explicit QxTdMessageCall(QObject *parent = nullptr);

    QxTdCallDiscardReason *discardReason() const;

    qint32 duration() const;
    QString hours() const;
    QString minutes() const;
    QString seconds() const;
    QString typeText() const;

    void setOutgoing(const bool isOutgoing);
    void unmarshalJson(const QJsonObject &json) override;

signals:
    void contentChanged();

private:
    void updateTypeText();
    std::unique_ptr<QxTdCallDiscardReason> m_discardReason;
    qint32 m_duration;
    qint32 m_hours;
    qint32 m_minutes;
    qint32 m_seconds;
    QString m_reason;
    bool m_isOutgoing;
};

#endif // QX_TD_MESSAGE_CALL_H
