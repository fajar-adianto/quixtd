#ifndef QX_TD_CALL_DISCARD_REASON_H
#define QX_TD_CALL_DISCARD_REASON_H

#include <QObject>
#include "common/qx_td_object.h"

/**
 * @brief The QxTdCallDiscardReason class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_call_discard_reason.html
 */
class QxTdCallDiscardReason : public QxTdObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdCallDiscardReason cannot be created in QML.")
    Q_DISABLE_COPY(QxTdCallDiscardReason)
public:
    explicit QxTdCallDiscardReason(QObject *parent = nullptr);
};

/**
 * @brief The QxTdCallDiscardReasonDeclined class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1call_discard_reason_declined.html
 */
class QxTdCallDiscardReasonDeclined : public QxTdCallDiscardReason
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdCallDiscardReason and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdCallDiscardReasonDeclined)
public:
    explicit QxTdCallDiscardReasonDeclined(QObject *parent = nullptr);
    QJsonObject marshalJson();
};

/**
 * @brief The QxTdCallDiscardReasonDisconnected class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1call_discard_reason_disconnected.html
 */
class QxTdCallDiscardReasonDisconnected : public QxTdCallDiscardReason
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdCallDiscardReason and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdCallDiscardReasonDisconnected)
public:
    explicit QxTdCallDiscardReasonDisconnected(QObject *parent = nullptr);
    QJsonObject marshalJson();
};

/**
 * @brief The QxTdCallDiscardReasonEmpty class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1call_discard_reason_empty.html
 */
class QxTdCallDiscardReasonEmpty : public QxTdCallDiscardReason
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdCallDiscardReason and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdCallDiscardReasonEmpty)
public:
    explicit QxTdCallDiscardReasonEmpty(QObject *parent = nullptr);
    QJsonObject marshalJson();
};

/**
 * @brief The QxTdCallDiscardReasonHungUp class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1call_discard_reason_hung_up.html
 */
class QxTdCallDiscardReasonHungUp : public QxTdCallDiscardReason
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdCallDiscardReason and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdCallDiscardReasonHungUp)
public:
    explicit QxTdCallDiscardReasonHungUp(QObject *parent = nullptr);
    QJsonObject marshalJson();
};

/**
 * @brief The QxTdCallDiscardReasonMissed class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1call_discard_reason_missed.html
 */
class QxTdCallDiscardReasonMissed : public QxTdCallDiscardReason
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdCallDiscardReason and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdCallDiscardReasonMissed)
public:
    explicit QxTdCallDiscardReasonMissed(QObject *parent = nullptr);
    QJsonObject marshalJson();
};
#endif // QX_TD_CALL_DISCARD_REASON_H
